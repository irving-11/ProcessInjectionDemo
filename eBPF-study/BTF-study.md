### BTF-study

**BTF**：BPF类型格式，提供结构信息以避免需要Clang和内核头文件。

**CO-RE**：BPF Compile-Once Run-Everywhere，允许编译的BPF字节码可重定位，避免了需要LLVM重新编译。

编译仍然需要Clang和LLVM，但结果是一个可以在任何地方运行的轻量级ELF二进制文件，其中包括预编译的BPF字节码。



这不仅仅是将 BPF 字节码保存在 ELF 文件中然后将其发送到任何其他内核的问题。 许多 BPF 程序会遍历内核结构，这些结构在不同内核版本之间可能有所不同。 一些BPF 字节码或许可以在不同的内核上执行，但它可能会读取错误的结构偏移量、打印垃圾输出！ 

这是一个重定位问题，BTF 和 CO-RE 应运而生。BTF 提供类型信息，以便可以根据需要查询结构偏移量和其他详细信息，CO-RE 记录 BPF 程序的哪些部分需要重写，以及如何重写。这些新的 BPF 二进制文件只有在设置了**CONFIG_DEBUG_INFO_BTF=y**内核配置选项时才有正常运行。 该内核配置为内核映像增加了大约 1.5 MB（而DWARF debuginfo 可能是数百 MB）。Ubuntu 20.10 已经将此配置选项设为默认值。需要 pahole >= 1.16。



#### BTF

BTF（BPF类型格式）是对与BPF program/map有关的调试信息进行编码的元数据格式。BTF最初用来描述数据类型，后来进行了扩展，以包括用于定义的子例程的函数信息，以及用于source/line的行信息。

调试信息用于map优雅打印，函数签名等。函数签名可实现更好的bpf program/function内核符号。行信息有助于生成带源码注释的翻译后的字节码，jit后的代码和验证者日志。

BTF规范包含两部分:

- BTF内核API：内核API是用户空间和内核之间的约定。内核在使用前会验证BTF信息；
- BTF ELF文件格式： ELF文件格式是ELF文件和libbpf加载程序之间的用户空间协定。

类型和字符串部分是BTF内核API的一部分，描述了bpf程序引用的调试信息（主要是类型相关的）。



**include/uapi/linux/btf.h**提供了关于类型/字符串如何编码的更高层次的定义。

数据块blob开头必须是：

```c
struct btf_header {
    __u16 magic;
    __u8 version;
    __u8 flags;
    __u32 hdr_len; //sizeof(struct btf_header)

    /* 所有的偏移量都是相对于这个头的末尾的字节 */
    __u32 type_off; /* 类型部分的偏移量 */
    __u32 type_len; /* 类型部分的长度 */
    __u32 str_off;  /* 字符串部分的偏移量 */
    __u32 str_len;  /* 字符串部分的长度 */
};
```

##### 字符串编码

字符串部分的第一个字符串必须以 null 结尾字符串。字符串表的其他部分有其他非 null 结尾的字符串连接而成。

##### 类型编码

类型标识 `0` 是为 `void` 类型保留的。类型部分（section）是按顺序解析，每个类型以 ID 从 `1` 开始的进行编码。目前，支持以下类型：

```c
#define BTF_KIND_INT 1          /* 整数 */
#define BTF_KIND_PTR 2          /* 指针 */
#define BTF_KIND_ARRAY 3        /* 数组 */
#define BTF_KIND_STRUCT 4       /* 结构体 */
#define BTF_KIND_UNION 5        /* 联合体 */
#define BTF_KIND_ENUM 6         /* 枚举 */
#define BTF_KIND_FWD 7          /* 前向引用 */
#define BTF_KIND_TYPEDEF 8      /* 类型定义 */
#define BTF_KIND_VOLATILE 9     /* VOLATILE 变量 */
#define BTF_KIND_CONST 10       /* 常量 */
#define BTF_KIND_RESTRICT 11    /* 限制性 */
#define BTF_KIND_FUNC 12        /* 函数 */
#define BTF_KIND_FUNC_PROTO 13  /* 函数原型 */
#define BTF_KIND_VAR 14         /* 变量 */
#define BTF_KIND_DATASEC 15     /* 数据部分 */
```

注意，类型部分是对调试信息进行编码的，而不是类型自身。`BTF_KIND_FUNC` 不是一个类型, 它代表一个已定义的子程序。

每个类型都包含以下常见的数据：

```c
struct btf_type {
    __u32 name_off;
    /* "info" 位值设置如下：
     * bits 0-15: vlen（例如结构的数量）
     * bits 16-23: unused
     * bits 24-27: kind (e.g. int, ptr, array...etc)
     * bits 28-30 位：未使用
     * bits 31: kind_flag, 目前被 struct, union 和 fwd 使用
     */
    __u32 info;
    /* "size" 被 INT、ENUM、STRUCT  和 UNION 使用
     * "size" 用于描述类型的大小
     * "type" 被 PTR, TYPEDEF, VOLATILE, CONST, RESTRICT, FUNC 和 FUNC_PROTO 使用。
     * "type" 是引用另一个类型的 type_id
     */
    union {
            __u32 size;
            __u32 type;
    };
};
```

对于某些类别来讲，通用数据之后是特定类型的数据。在 `struct btf_type` 中的 `name_off` 字段指定了字符串表中的偏移。

#### BTF内核API

以下 bpf 系统调用命令涉及 BTF：

- BPF_BTF_LOAD：将 BTF 数据的 blob 数据加载到内核中
- BPF_MAP_CREATE：用 btf 键和值类型信息创建 map
- BPF_PROG_LOAD：用 btf 函数和行信息加载程序
- BPF_BTF_GET_FD_BY_ID：获得一个 btf fd
- BPF_OBJ_GET_INFO_BY_FD：返回 btf、func_info、line_info 和其它与 btf 有关的信息

#### ELF文件格式接口

.BTF section包含类型和字符串数据；

.BTF.ext section包含func_info和line_info，在被加载到内核之前会由loader处理；



#### BTF测试

**/usr/src/linux-5.4/tools/testing/selftests/bpf/test_btf.c**

```c
{
	.descr = "global data test #1",
	.raw_types = {
		/* int */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* unsigned long long */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* char */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* int[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* struct A { */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* unsigned long long m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* int n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* char o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* int p[8]		*/
		/* } */
		BTF_END_RAW,
	},
	.str_sec = "\0A\0m\0n\0o\0p",
	.str_sec_size = sizeof("\0A\0m\0n\0o\0p"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_test1_map",
	.key_size = sizeof(int),
	.value_size = 48,
	.key_type_id = 1,
	.value_type_id = 5,
	.max_entries = 4,
},
```

结果：

```
➜  bpf sudo ./test_btf
[sudo] password for ubuntu: 
BTF raw test[1] (struct test #1): OK
BTF raw test[2] (struct test #2): OK
BTF raw test[3] (struct test #3 Invalid member offset): OK
BTF raw test[4] (global data test #1): OK
BTF raw test[5] (global data test #2): OK
BTF raw test[6] (global data test #3): OK
BTF raw test[7] (global data test #4, unsupported linkage): OK
BTF raw test[8] (global data test #5, invalid var type): OK
BTF raw test[9] (global data test #6, invalid var type (fwd type)): OK
BTF raw test[10] (global data test #7, invalid var type (fwd type)): OK
BTF raw test[11] (global data test #8, invalid var size): OK
BTF raw test[12] (global data test #9, invalid var size): OK
BTF raw test[13] (global data test #10, invalid var size): OK
BTF raw test[14] (global data test #11, multiple section members): OK
BTF raw test[15] (global data test #12, invalid offset): OK
BTF raw test[16] (global data test #13, invalid offset): OK
BTF raw test[17] (global data test #14, invalid offset): OK
```



#### BTF生成

```
$ cat t2.c
typedef int __int32;
struct t2 {
  int a2;
  int (*f2)(char q1, __int32 q2, ...);
  int (*f3)();
} g2;
int main() { return 0; }
int test() { return 0; }
$ clang -c -g -O2 -target bpf t2.c
$ readelf -S t2.o
  ......
  [ 8] .BTF              PROGBITS         0000000000000000  00000247
       000000000000016e  0000000000000000           0     0     1
  [ 9] .BTF.ext          PROGBITS         0000000000000000  000003b5
       0000000000000060  0000000000000000           0     0     1
  [10] .rel.BTF.ext      REL              0000000000000000  000007e0
       0000000000000040  0000000000000010          16     9     8
  ......
$ clang -S -g -O2 -target bpf t2.c
$ cat t2.s
  ......
        .section        .BTF,"",@progbits
        .short  60319                   # 0xeb9f
        .byte   1
        .byte   0
        .long   24
        .long   0
        .long   220
        .long   220
        .long   122
        .long   0                       # BTF_KIND_FUNC_PROTO(id = 1)
        .long   218103808               # 0xd000000
        .long   2
        .long   83                      # BTF_KIND_INT(id = 2)
        .long   16777216                # 0x1000000
        .long   4
        .long   16777248                # 0x1000020
  ......
        .byte   0                       # string offset=0
        .ascii  ".text"                 # string offset=1
        .byte   0
        .ascii  "/home/yhs/tmp-pahole/t2.c" # string offset=7
        .byte   0
        .ascii  "int main() { return 0; }" # string offset=33
        .byte   0
        .ascii  "int test() { return 0; }" # string offset=58
        .byte   0
        .ascii  "int"                   # string offset=83
  ......
        .section        .BTF.ext,"",@progbits
        .short  60319                   # 0xeb9f
        .byte   1
        .byte   0
        .long   24
        .long   0
        .long   28
        .long   28
        .long   44
        .long   8                       # FuncInfo
        .long   1                       # FuncInfo section string offset=1
        .long   2
        .long   .Lfunc_begin0
        .long   3
        .long   .Lfunc_begin1
        .long   5
        .long   16                      # LineInfo
        .long   1                       # LineInfo section string offset=1
        .long   2
        .long   .Ltmp0
        .long   7
        .long   33
        .long   7182                    # Line 7 Col 14
        .long   .Ltmp3
        .long   7
        .long   58
        .long   8206                    # Line 8 Col 14
```



#### CO-RE

为了启用CO-RE，并且让BPF loader（libbpf）来为正在运行的（目标）内核调整BPF程序，Clang被扩展，增加了一些built-ins。这些built-ins会发出（emit）BTF relocations，BTF relocations是BPF程序需要读取什么信息的高层描述。假设程序需要访问task_struct->pid，Clang会将其记录：需要访问pid_t类型的、名为pid、位于task_struct结构中的字段。这样，即使字段顺序调整，甚至pid字段被放入一个内嵌的匿名结构体/联合体中，BPF程序仍然能够正确访问到pid字段。能够捕获（进而重定位）的信息不单单是字段偏移量，还包括字段是否存在、字段的size。甚至对于位域（bitfield）字段，也能够捕获足够多的信息，让对它的访问能够被重定位。



参考：

1. BPF Type Format (BTF)—— https://www.kernel.org/doc/html/latest/bpf/btf.html
2. BPF and XDP Reference Guide—— https://docs.cilium.io/en/v1.10/bpf/
3. BPF CO-RE (Compile Once – Run Everywhere)—— https://nakryiko.com/posts/bpf-portability-and-co-re/
4. eBPF学习笔记—— https://blog.gmem.cc/ebpf
