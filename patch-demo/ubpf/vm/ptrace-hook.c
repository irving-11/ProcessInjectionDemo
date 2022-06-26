#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/ptrace.h>

//函数声明
void getElfPath(char** path, int pid);
void getStartAddr(char** addr, int pid);
uint64_t findFuncAddress(const char *pbuff, const char *name);
void putdata(pid_t child, long addr, char *str, int len);

//获取进程pid的elf文件路径
void getElfPath(char** path, int pid) {
    FILE *fp;
    char cmd[128];
    *path = (char *)malloc(128);
    sprintf(cmd, "cat /proc/%d/maps | awk 'NR==1' | awk -F ' ' '{print $6}'", pid);
    fp = popen(cmd, "r");
    fread(*path, sizeof(char),128, fp);
    (*path)[strlen(*path)-1] = '\0';
    //printf("path: %s\n", *path);
    pclose(fp);
}

//获取进程pid的虚拟起始地址
void getStartAddr(char** addr, int pid) {
    FILE *fp;
    char cmd[128];
    *addr = (char *)malloc(64);
    sprintf(cmd, "cat /proc/%d/maps | awk 'NR==1' | awk -F '-' '{print $1}'", pid);
    fp = popen(cmd, "r");
    fread(*addr, sizeof(char), 64, fp);
	//printf("addr: %s\n", *addr);
    pclose(fp);
}

//获取指定函数的地址
uint64_t findFuncAddress(const char *pbuff, const char *name) {
    //从节区里面定位到偏移
    Elf64_Ehdr* pfilehead = (Elf64_Ehdr*)pbuff;
    Elf64_Half eshstrndx = pfilehead->e_shstrndx;
    Elf64_Shdr* psecheader = (Elf64_Shdr*)(pbuff + pfilehead->e_shoff);
    Elf64_Shdr* pshstr = (Elf64_Shdr*)(psecheader + eshstrndx);
    char* pshstrbuff = (char *)(pbuff + pshstr->sh_offset);

    for(int i = 0;i<pfilehead->e_shnum;++i) {
        if(!strcmp(psecheader[i].sh_name + pshstrbuff, ".symtab")) {
            Elf64_Sym* psym = (Elf64_Sym*)(pbuff + psecheader[i].sh_offset);
            int ncount = psecheader[i].sh_size / psecheader[i].sh_entsize;
            char* pbuffstr = (char*)((psecheader + psecheader[i].sh_link)->sh_offset + pbuff);
            //printf("Symbol table '%s' contains %d entries:\r\n", psecheader[i].sh_name + pshstrbuff, ncount);
            //outputsyminfo(psym, pbuffstr, ncount, "fix_func");
			for(int i = 0;i<ncount;++i) {
        		if(!strcmp(psym[i].st_name + pbuffstr, name)) {
            		//printf("%016lx\n", psym[i].st_value);
					return psym[i].st_value;
        		}
    		}
            continue;
        }
    }
	return 0;
}

//向进程pid写入数据
void putdata(pid_t child, long addr, char *str, int len) {   
    char *laddr;
    int i, j;
    union u {
            long val;
            char chars[8];
    }data;
    i = 0;
    j = len / 8;
    laddr = str;
    while(i < j) {
        memcpy(data.chars, laddr, 8);
        ptrace(PTRACE_POKEDATA, child, addr + i * 8, data.val);
        ++i;
        laddr += 8;
    }
    j = len % 8;
    if(j != 0) {
        memcpy(data.chars, laddr, j);
        ptrace(PTRACE_POKEDATA, child, addr + i * 8, data.val);
    }
}

int main(int argc, char *argv[]) {
    int fd, pid;
    char *path=NULL, *startAddr = NULL;
    if (argc != 2) {
        perror("wrong usage: ./attack pid\n");
        return 0;
    }
    pid = atoi(argv[1]);
    getElfPath(&path, pid);    
    //printf("path: %s\n", path);
    getStartAddr(&startAddr, pid);

    //打开指定文件
    fd = open(path, O_RDONLY, 0);
    if(fd == -1) {
        perror("open error\n");
        return 0;
    }
    //分配文件大小
    long int end = lseek(fd, 0, SEEK_END);
	long int begin = lseek(fd, 0, SEEK_SET);
    char* pbuff = malloc(end);
    if(!pbuff) {
        printf("malloc error\n");
        return 0;
    }
    //初始化
    memset(pbuff, 0, end);
    if(read(fd, pbuff, end) == -1) {
        perror("read error\n");
        return 0;
    }
    
    //获取相关函数地址
    uint64_t addr1 = findFuncAddress(pbuff, "vul_func");
    uint64_t addr2 = findFuncAddress(pbuff, "patch_handler");
	
	//构造jmp指令
    unsigned char jmp[] = {0xe9, 0x00, 0x00, 0x00, 0x00};
    uint64_t offset = addr2 - (addr1 + 5);
    char tmp[8] = {0};
    sprintf(tmp, "%x", (unsigned char)(offset & 0xff));
    jmp[1] = (unsigned char)strtoul(tmp,NULL, 16);
    sprintf(tmp, "%x", (unsigned char)((offset & 0xff00)>>8));
    jmp[2] = (unsigned char)strtoul(tmp,NULL, 16);
    sprintf(tmp, "%x", (unsigned char)((offset & 0xff0000)>>8));
    jmp[3] = (unsigned char)strtoul(tmp,NULL, 16);
    sprintf(tmp, "%x", (unsigned char)((offset & 0xff000000)>>8));
    jmp[4] = (unsigned char)strtoul(tmp,NULL, 16);

    //attach到进程pid
    int status;
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    wait(&status);
    if(WIFEXITED(status)) {
        printf("already exit\n");
        return 0;
    }

    //计算指令写入位置
    offset = addr1 + (uint64_t)strtoul(startAddr, NULL, 16);
    printf("jmp: 0x%08x 0x%08x\n", *(int *) jmp, (int) jmp[4]);

    putdata(pid, offset, jmp, 8);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);

    if(path!=NULL) {
        free(path);
    }
	if(startAddr!=NULL) {
        free(startAddr);
    }
    return 0;
}

