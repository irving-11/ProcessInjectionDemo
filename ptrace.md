### Ptrace

`ptrace`(Process Trace)系统调用提供了一种机制用来观察和控制其他进程的执行, 并且可以检查和修改其核心映像和寄存器。通常用来作为调试器(如gdb)和跟踪各种其他系统调用。常见的两种追踪模式为PTRACE_TRACEME（指示此进程被追踪） 和 PTRACE_ATTACH（用于主动追踪）。

ptrace函数通过四个参数来调用, 其原型为:

```c
long ptrace(enum __ptrace_request request, pid_t pid, void *addr, void *data);
```

其中第一个参数决定了ptrace的行为和其他参数的含义，request可取值有

```c
PTRACE_TRACEME：表示本进程将被其父进程跟踪
PTRACE_PEEKTEXT, PTRACE_PEEKDATA：从内存地址中读取一个WORD，内存地址为addr
PTRACE_PEEKUSER：从USER区域中读取一个WORD，内存地址为addr，值将作为结果返回，其中偏移地址addr通常是是字对齐的
PTRACE_POKETEXT, PTRACE_POKEDATA：向内存地址中写入一个WORD，内存地址为addr
PTRACE_POKEUSER：向USER区域中写入一个WORD，内存地址为addr
PTRACE_GETREGS, PTRACE_GETFPREGS：读取寄存器/浮点寄存器
PTRACE_SETREGS, PTRACE_SETFPREGS：设置寄存器/浮点寄存器
PTRACE_CONT：继续运行之前停止的子进程，如果data是非空的，它被解释为要发送给Tracee 的信号
PTRACE_SYSCALL，PTRACE_SINGLESTEP：使被追踪进程继续运行，但会在下一个系统调用之前或结束系统调用之后停止/在执行单步指令后停止
PTRACE_ATTACH：attach到一个指定的进程，使其成为当前进程跟踪的子进。程子进程的行为等同于它进行了一次PTRACE_TRACEME操作
PTRACE_DETACH：detach指定的进程，重新运行被追踪的进程
```


#### 1.拦截系统调用并修改参数

操作系统通过一系列称为系统调用的方法来提供各种服务。他们提供了标准的API来访问硬件设备和底层服务，比如文件系统。

64位系统，用户层应用程序用整数寄存器`%rdi, %rsi, %rdx, %rcx, %r8 以及 %r9`来传参，而**内核接口**用`%rdi, %rsi, %rdx, %r10, %r8 以及 %r9`来传参。64位下用`syscall`指令来进行系统调用。

**ptrace作用点：在执行系统调用之前，内核会先检查进程是否正在被追踪，如果是，内核会停止进程并将控制权转移给追踪进程，跟踪进程就可以查看和修改被追踪进程的寄存器。**

##### 追踪进程

```c
// track the child process
int main()
{   
    pid_t child;
    long orig_rax;
    child = fork();
    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/ls", "ls", NULL);
    }
    else { 
        wait(NULL);
        orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
        printf("The child made a system call %ld\n", orig_rax);
        ptrace(PTRACE_CONT, child, NULL, NULL);
    }
    return 0;
}
```

程序运行输出：

```shell
$ gcc -o test_1 test_1.c
$ ./test_1
The child made a system call 59
$ attacker  attacker.c  test_1  test_1.c   test_2.c  victim  victim.c
$
```

此例中，fork()产生的子进程执行系统调用，执行之前，调用ptrace，并设置第一个参数为PTRACE_TRACEME，表示当前进程正在被追踪。于是当子进程运行至execl时，控制权转移到父进程，父进程用**wait**函数等待内核通知，随后即可执行查看系统调用信息等（使用PTRACE_PEEKUSER等参数）操作，完成操作后，调用ptrace并设置PTRACE_CONT参数让子进程继续运行。

##### 寄存器读写

应用程序用整数寄存器`%rdi, %rsi, %rdx, %rcx, %r8 以及 %r9`来传参，可通过PTRACE_PEEKUSER获取系统调用参数，也可通过PTRACE_GETREGS获取，第二种方式更简单。

```c
// read and write the registers
int main()
{
   pid_t child;
   child = fork();
   // struct user_regs_struct regs;
   if(child == 0) {
      ptrace(PTRACE_TRACEME, 0, NULL, NULL);
      execl("/bin/ls", "ls", NULL);
   }
   else {
      long orig_rax;
      long params[3];
      int status;
      char *str, *laddr;
      int toggle = 0;
      while(1) {
         wait(&status);
         if(WIFEXITED(status))
             break;
         orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
         if(orig_rax == SYS_write) {
            if(toggle == 0) {
               toggle = 1;
               //ptrace(PTRACE_GETREGS, child, NULL, &regs);
               //str = (char *)malloc((regs.rdx+1) * sizeof(char));
               //getdata(child, regs.rsi, str, regs.rdx);
               //reverse(str);
               //putdata(child, regs.rsi, str, regs.rdx);
               params[0] = ptrace(PTRACE_PEEKUSER, child, 8 * RDI, NULL);
               params[1] = ptrace(PTRACE_PEEKUSER, child, 8 * RSI, NULL);
               params[2] = ptrace(PTRACE_PEEKUSER, child, 8 * RDX, NULL);
               str = (char *)malloc((params[2]+1) * sizeof(char));
               getdata(child, params[1], str, params[2]);
               reverse(str);
               putdata(child, params[1], str, params[2]);
            }
            else {
               toggle = 0;
            }
         }
      ptrace(PTRACE_SYSCALL, child, NULL, NULL);
      }
   }
   return 0;
}
```

程序运行输出：

```shell
$ ls
attacker  attacker.c  test_1  test_1.c  test_2.c  test_3  test_3.c  victim  victim.c
$ ./test_3
c.mitciv  mitciv  c.3_tset  3_tset  c.2_tset    c.1_tset  1_tset  c.rekcatta  rekcatta
$
```

使用**val = ptrace(PTRACE_PEEKDATA, child, addr, NULL)**获取addr处字符串内容，

使用**ptrace(PTRACE_POKEDATA, child, addr, data)**更新系统调用参数。

由于ptrace的返回值是long型的，因此一次最多只能读取sizeof(long)个字节的数据，可以多次读取`addr + i*sizeof(long)`然后合并得到最终的字符串内容。在64bit系统下一次可以读取64/8=8字节的数据。更新字符串内容类似。

#### 2.注入代码到运行中的进程（PTRACE_ATTACH）

使用**ptrace(PTRACE_ATTACH, pid, NULL, NULL)**追踪正在运行的程序，pid为欲追踪进程id。当前进程会给被追踪进程发送**SIGSTOP**信号，但不要求立即停止， 一般会等待子进程完成当前调用。ATTACH之后就和操作fork出来的TRACEME子进程一样进行操作。如果要结束追踪,则再使用参数`PTRACE_DETACH`即可.

动态注入指令：attach并追踪正在运行的进程，读取其指令寄存器IR（%rip）的内容，备份后替换成目标指令，再使其返回运行，此时被追踪进程就会执行目标指令，执行完毕后，再恢复原进程的IR，从而改变了原进程的执行逻辑。

```c
// simple inject
int main(int argc, char *argv[]) {
    if(argc!=2) {
        printf("Usage: %s pid\n", argv[0]);
        return 1;
    }
    pid_t victim = atoi(argv[1]);
    struct user_regs_struct regs;
	int len = 41;
    unsigned char insertcode[] = 
	"\xeb\x13\x5e\xb8\x01\x00\x00\x00"
	"\xbf\x01\x00\x00\x00\xba\x0d\x00"
	"\x00\x00\x0f\x05\xcc\xe8\xe8\xff"
	"\xff\xff\x48\x65\x6c\x6c\x6f\x2c"
	"\x20\x57\x6f\x72\x6c\x64\x21\x0a\x00";
    char backup[len];
    if(ptrace(PTRACE_ATTACH, victim, NULL, NULL)<0){printf("cannot attach\n");return 0;}

    wait(NULL);
    ptrace(PTRACE_GETREGS, victim, NULL, &regs);
    getdata(victim, regs.rip, backup, len);

    putdata(victim, regs.rip, insertcode, len);
    /* Let the process continue and execute the int 3 instruction */
	ptrace(PTRACE_SETREGS, victim, NULL, &regs);
    ptrace(PTRACE_CONT, victim, NULL, NULL);

    wait(NULL);
    printf("the process stopped, putting back the original instructions.press Enter to continue ptraced process.\n");
	getchar();
    putdata(victim, regs.rip, backup, len);
    ptrace(PTRACE_SETREGS, victim, NULL, &regs);
	printf("executing the original flow.\n");
    ptrace(PTRACE_CONT, victim, NULL, NULL);
    ptrace(PTRACE_DETACH, victim, NULL, NULL);
    return 0;
}
```

```shell
$ ./victim                                  │$ sudo ./test_4 9071
Hello, ptrace! [pid:9071]                   │the process stopped, putting back the original instructions.press Enter to
Hello, ptrace! [pid:9071]                   │ continue ptraced process.
Hello, ptrace! [pid:9071]                   │              
Hello, World!Hello, ptrace! [pid:9071]      │executing the original flow.
Hello, ptrace! [pid:9071]                   │$ 
Hello, ptrace! [pid:9071]                   │
^C                                          │
$
```

注入进程后，victim程序会打印**Hello， World！**。具体做法是将%rip的内容修改为shellcode，使得victim打印字符串并暂停，随后使用PTRACE_SETREGS恢复寄存器状态。

也可将代码注入到空闲空间中，需要用到/proc/pid/maps文件的内容。



参考文章：

Playing with ptrace, Part I	https://www.linuxjournal.com/article/6100

Playing with ptrace, Part II	https://www.linuxjournal.com/article/6210

ptrace(2) — Linux manual page	https://man7.org/linux/man-pages/man2/ptrace.2.html
