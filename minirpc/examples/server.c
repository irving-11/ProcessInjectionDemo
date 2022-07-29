#include "../minirpc.h"
#include "../minirpc-service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <elf.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/ptrace.h>

#include <inttypes.h>

#include <stdbool.h>

//函数声明
void getElfPath(char **path, int pid);
void getStartAddr(char **addr, int pid);
uint64_t findFuncAddress(const char *pbuff, const char *name);
void putdata(pid_t child, long addr, char *str, int len);

static int8_t code0[] = ""
                        "\x61\x11\x00\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\xc7\x01\x00\x00\x20\x00\x00\x00\xb7"
                        "\x00\x00\x00\x01\x00\x00\x00\x65\x01\x01\x00\x88\x13\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00"
                        "\x00\x00\x00\x00\x00\x00"
                        "";
static int8_t code1[] = ""
                        "\x61\x11\x00\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\xc7\x01\x00\x00\x20\x00\x00\x00\xb7"
                        "\x00\x00\x00\x01\x00\x00\x00\x65\x01\x01\x00\x88\x13\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00"
                        "\x00\x00\x00\x00\x00\x00"
                        "";
static int8_t code2[] = ""
                        "\x61\x12\x00\x00\x00\x00\x00\x00\x61\x11\x04\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\x4f"
                        "\x21\x00\x00\x00\x00\x00\x00\x61\x13\x04\x00\x00\x00\x00\x00\x79\x12\x10\x00\x00\x00\x00\x00\x61\x24"
                        "\x00\x00\x00\x00\x00\x00\x5d\x34\x04\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x61\x11\x08"
                        "\x00\x00\x00\x00\x00\x61\x22\x04\x00\x00\x00\x00\x00\x1d\x12\x02\x00\x00\x00\x00\x00\x18\x00\x00\x00"
                        "\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
                        "";

// int8_t *array[2] = {code0, code1};

//获取进程pid的elf文件路径
void getElfPath(char **path, int pid)
{
    FILE *fp;
    char cmd[128];
    *path = (char *)malloc(128);
    sprintf(cmd, "cat /proc/%d/maps | awk 'NR==1' | awk -F ' ' '{print $6}'", pid);
    fp = popen(cmd, "r");
    fread(*path, sizeof(char), 128, fp);
    (*path)[strlen(*path) - 1] = '\0';
    // printf("path: %s\n", *path);
    pclose(fp);
}

//获取进程pid的虚拟起始地址
void getStartAddr(char **addr, int pid)
{
    FILE *fp;
    char cmd[128];
    *addr = (char *)malloc(64);
    sprintf(cmd, "cat /proc/%d/maps | awk 'NR==1' | awk -F '-' '{print $1}'", pid);
    fp = popen(cmd, "r");
    fread(*addr, sizeof(char), 64, fp);
    // printf("addr: %s\n", *addr);
    pclose(fp);
}

//获取指定函数的地址
uint64_t findFuncAddress(const char *pbuff, const char *name)
{
    //从节区里面定位到偏移
    Elf64_Ehdr *pfilehead = (Elf64_Ehdr *)pbuff;
    Elf64_Half eshstrndx = pfilehead->e_shstrndx;
    Elf64_Shdr *psecheader = (Elf64_Shdr *)(pbuff + pfilehead->e_shoff);
    Elf64_Shdr *pshstr = (Elf64_Shdr *)(psecheader + eshstrndx);
    char *pshstrbuff = (char *)(pbuff + pshstr->sh_offset);

    for (int i = 0; i < pfilehead->e_shnum; ++i)
    {
        if (!strcmp(psecheader[i].sh_name + pshstrbuff, ".symtab"))
        {
            Elf64_Sym *psym = (Elf64_Sym *)(pbuff + psecheader[i].sh_offset);
            int ncount = psecheader[i].sh_size / psecheader[i].sh_entsize;
            char *pbuffstr = (char *)((psecheader + psecheader[i].sh_link)->sh_offset + pbuff);
            // printf("Symbol table '%s' contains %d entries:\r\n", psecheader[i].sh_name + pshstrbuff, ncount);
            // outputsyminfo(psym, pbuffstr, ncount, "fix_func");
            for (int i = 0; i < ncount; ++i)
            {
                if (!strcmp(psym[i].st_name + pbuffstr, name))
                {
                    // printf("%016lx\n", psym[i].st_value);
                    return psym[i].st_value;
                }
            }
            continue;
        }
    }
    return 0;
}

//向进程pid写入数据
void putdata(pid_t child, long addr, char *str, int len)
{
    char *laddr;
    int i, j;
    union u
    {
        long val;
        char chars[8];
    } data;
    i = 0;
    j = len / 8;
    laddr = str;
    while (i < j)
    {
        memcpy(data.chars, laddr, 8);
        ptrace(PTRACE_POKEDATA, child, addr + i * 8, data.val);
        ++i;
        laddr += 8;
    }
    j = len % 8;
    if (j != 0)
    {
        memcpy(data.chars, laddr, j);
        ptrace(PTRACE_POKEDATA, child, addr + i * 8, data.val);
    }
}

int ptrace_hook(int pid, const char *name_1, const char *name_2)
{
    int fd; //, pid;
    char *path = NULL, *startAddr = NULL;
    /*if (argc != 2) {
        perror("wrong usage: ./attack pid\n");
        return 0;
    }
    pid = atoi(argv[1]);*/
    getElfPath(&path, pid);
    // printf("path: %s\n", path);
    getStartAddr(&startAddr, pid);

    //打开指定文件
    fd = open(path, O_RDONLY, 0);
    if (fd == -1)
    {
        perror("open error\n");
        return 0;
    }
    //分配文件大小
    long int end = lseek(fd, 0, SEEK_END);
    long int begin = lseek(fd, 0, SEEK_SET);
    char *pbuff = malloc(end);
    if (!pbuff)
    {
        printf("malloc error\n");
        return 0;
    }
    //初始化
    memset(pbuff, 0, end);
    if (read(fd, pbuff, end) == -1)
    {
        perror("read error\n");
        return 0;
    }

    //获取相关函数地址
    uint64_t addr1 = findFuncAddress(pbuff, name_1);
    uint64_t addr2 = findFuncAddress(pbuff, name_2);

    //构造jmp指令
    unsigned char jmp[] = {0xe9, 0x00, 0x00, 0x00, 0x00};
    uint64_t offset = addr2 - (addr1 + 5);
    char tmp[8] = {0};
    sprintf(tmp, "%x", (unsigned char)(offset & 0xff));
    jmp[1] = (unsigned char)strtoul(tmp, NULL, 16);
    sprintf(tmp, "%x", (unsigned char)((offset & 0xff00) >> 8));
    jmp[2] = (unsigned char)strtoul(tmp, NULL, 16);
    sprintf(tmp, "%x", (unsigned char)((offset & 0xff0000) >> 8));
    jmp[3] = (unsigned char)strtoul(tmp, NULL, 16);
    sprintf(tmp, "%x", (unsigned char)((offset & 0xff000000) >> 8));
    jmp[4] = (unsigned char)strtoul(tmp, NULL, 16);

    // attach到进程pid
    int status;
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    wait(&status);
    if (WIFEXITED(status))
    {
        printf("already exit\n");
        return 0;
    }

    //计算指令写入位置
    offset = addr1 + (uint64_t)strtoul(startAddr, NULL, 16);
    printf("find: 0x%08lx\t0x%08lx\t0x%08lx\n", addr1, addr2, offset);

    putdata(pid, offset, jmp, 8);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);

    if (path != NULL)
    {
        free(path);
    }
    if (startAddr != NULL)
    {
        free(startAddr);
    }
    return 0;
}

/*
 * Using MiniRPC Service module to help us handle the business
 * logic in backend thread.
 */

static void do_patch_cb(struct mrpc_service *service,
                        const struct mrpc_request *req,
                        void *udata,
                        int *error_code,
                        struct mrpc_val *val)
{
    if (req->par_size != 2)
    {
        *error_code = MRPC_EC_FUNCTION_INVALID_PARAMETER_SIZE;
        return;
    }
    /* get the 1 unsigned integer value */
    if (req->par[0].type != MRPC_UINT || req->par[1].type != MRPC_UINT)
    {
        *error_code = MRPC_EC_FUNCTION_INVALID_PARAMETER_TYPE;
        return;
    }
    // do hook
    char name_1[32], name_2[32];
    sprintf(name_1, "dummy_cve_%u", req->par[1].value.uinteger);
    sprintf(name_2, "patch_handler_%u", req->par[1].value.uinteger);
    assert(ptrace_hook(req->par[0].value.uinteger, name_1, name_2) == 0);
    switch (req->par[1].value.uinteger)
    {
    case 0:
        printf("send bytecode len:%ld\n", sizeof(code0));
        mrpc_val_varchar(val, (const char *)code0, 1, sizeof(code0)); //把长度作为参数
        break;
    case 1:
        printf("send bytecode len:%ld\n", sizeof(code1));
        mrpc_val_varchar(val, (const char *)code1, 1, sizeof(code1)); //把长度作为参数
        break;
    case 2:
        printf("send bytecode len:%ld\n", sizeof(code2));
        mrpc_val_varchar(val, (const char *)code2, 1, sizeof(code2)); //把长度作为参数
        break;
    default:
        printf("wrong cve num\n");
        // return -1;
    }

    /* setting the correct error code */
    *error_code = MRPC_EC_OK;
}

static void hello_world_cb(struct mrpc_service *service,
                           const struct mrpc_request *req,
                           void *udata,
                           int *error_code,
                           struct mrpc_val *val)
{
    assert(strcmp(req->method_name, "Hello World") == 0);
    /* checking the parameter size */
    if (req->par_size != 0)
    {
        *error_code = MRPC_EC_FUNCTION_INVALID_PARAMETER_SIZE;
        return;
    }
    /* formating the return value */
    mrpc_val_varchar(val, "Hello World", 0, strlen("Hello World"));
    /* setting the correct error code */
    *error_code = MRPC_EC_OK;
}

/* This function will calculate the addition of 2 unsigned integer */
static void addition_cb(struct mrpc_service *service,
                        const struct mrpc_request *req,
                        void *udata,
                        int *error_code,
                        struct mrpc_val *val)
{
    if (req->par_size != 2)
    {
        *error_code = MRPC_EC_FUNCTION_INVALID_PARAMETER_SIZE;
        return;
    }
    /* get the 2 unsigned integer value */
    if (req->par[0].type != MRPC_UINT || req->par[1].type != MRPC_UINT)
    {
        *error_code = MRPC_EC_FUNCTION_INVALID_PARAMETER_TYPE;
        return;
    }
    /* do the calculation here */
    mrpc_val_uint(val, req->par[0].value.uinteger + req->par[1].value.uinteger);
    /* setting the correct error code */
    *error_code = MRPC_EC_OK;
}

int main()
{
    struct mrpc_service *service;
    int ret;

    if (mrpc_init("log.txt", "127.0.0.1:12345", 0) != 0)
    {
        fprintf(stderr, "Cannot initialize MRPC!");
        return -1;
    }

    service = mrpc_service_create(128, 0, 50, NULL);

    /* register the service entry */
    mrpc_service_add(service, hello_world_cb, "Hello World", NULL);
    mrpc_service_add(service, addition_cb, "Add", NULL);
    mrpc_service_add(service, do_patch_cb, "do_patch", NULL);

    /* start the service in backend thread */
    mrpc_service_run_remote(service, 1);

    /* start working now */
    ret = mrpc_run();

    if (ret < 0)
    {
        /* Handle error */
        fprintf(stderr, "MRPC Error!");
    }
    else
    {
        /* User interruption */
        fprintf(stderr, "User interruption!");
    }

    /* (1) Quit the service (2) Stop the MRPC */
    mrpc_service_quit(service);
    mrpc_clean();

    return 0;
}
