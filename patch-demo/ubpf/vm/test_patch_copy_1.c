#define _GNU_SOURCE

#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <elf.h>
#include <math.h>
#include "ubpf_int.h"



// static uint8_t code0[] = ""
// "\x61\x11\x00\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\xc7\x01\x00\x00\x20\x00\x00\x00\xb7"
// "\x00\x00\x00\x0a\x00\x00\x00\x65\x01\x01\x00\x88\x13\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00"
// "\x00\x00\x00\x00\x00\x00"
// "";

//ubuntu18
// "\xbf\x12\x00\x00\x00\x00\x00\x00\x61\x26\x04\x00\x00\x00\x00\x00\x07\x02\x00\x00\x08\x00\x00\x00\xbf"
// "\xa1\x00\x00\x00\x00\x00\x00\x07\x01\x00\x00\xf0\xff\xff\xff\x85\x10\x00\x00\xff\xff\xff\xff\x67\x06"
// "\x00\x00\x20\x00\x00\x00\xc7\x06\x00\x00\x20\x00\x00\x00\xb7\x01\x00\x00\x89\x13\x00\x00\x6d\x61\x0a"
// "\x00\x00\x00\x00\x00\xbf\xa1\x00\x00\x00\x00\x00\x00\x07\x01\x00\x00\xf0\xff\xff\xff\x18\x02\x00\x00"
// "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x85\x10\x00\x00\xff\xff\xff\xff\xbf\x01\x00\x00\x00"
// "\x00\x00\x00\xb7\x00\x00\x00\x0a\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\x77\x01\x00\x00\x20\x00"
// "\x00\x00\x15\x01\x01\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00"
// "\x00"

static int8_t code1[] = ""
"\xbf\x12\x00\x00\x00\x00\x00\x00\x61\x26\x04\x00\x00\x00\x00\x00\x07\x02\x00\x00\x08\x00\x00\x00\xbf"
"\xa1\x00\x00\x00\x00\x00\x00\x07\x01\x00\x00\xf0\xff\xff\xff\x85\x10\x00\x00\xff\xff\xff\xff\x67\x06"
"\x00\x00\x20\x00\x00\x00\xc7\x06\x00\x00\x20\x00\x00\x00\xb7\x01\x00\x00\x89\x13\x00\x00\x6d\x61\x05"
"\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x0a\x00\x00\x00\x18\x01\x00\x00\x67\x6f\x6f\x6f\x00\x00\x00\x00"
"\x6f\x6f\x64\x00\x79\xa2\xf0\xff\x00\x00\x00\x00\x1d\x12\x01\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00"
"\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

struct Mem
{
    uint32_t a;
    const char b[16];
};

typedef struct Mem2
{
    uint32_t c;
    struct Mem d;
}Mem2;

int run_ebpf(Mem2);

int orig_c0(Mem2 mem2) {
	if (mem2.d.a > 2000) { // fixed: v > 5000 && ... return 10
		return 10;
	}
	return 0;
}

int fix_func(Mem2 mem2){
	return run_ebpf(mem2);
}

int sum(int a, int b)
{
    /*int ret;
    asm volatile (
        "mov %1, %0\n\t"
        "add %2, %0\n\t"
        : "=&r"(ret)
        : "r"(a), "r"(b)
    );*/
    // 这样写会报a，b声明但未使用的错误
    asm("addl %edi, %esi\n\t");
    asm("movl %esi, %eax\n\t");
    //return ret;
}

int patch_handler() {
    asm("movl $1, %esi\n\t");
    asm("movl $2, %edi\n\t");
    asm("call sum\n\t");
}

// __attribute__((naked)) 
/*int patch_handler(Mem2 mem2) {
    asm("movl 12(%rbp), %eax\n\t");
    // asm("movl $2, %eax\n\t");//for test
}*/

int run_ebpf(Mem2 mem2)
{
    //这样传参只能说明ebpf patch是有效的？??
 	Mem2 bpf;// = malloc(sizeof(struct bpf*));// = (struct Mem *)mem;
    bpf.d.a = mem2.d.a;
    strcpy((char *)bpf.d.b, mem2.d.b);

    struct ubpf_vm *vm = ubpf_create();
    if (!vm) {
        fprintf(stderr, "Failed to create VM\n");
        return 1;
    }

    vm->insts = malloc(sizeof(code1));
    if (vm->insts == NULL) {
        return -1;
    }
    memcpy(vm->insts, code1, sizeof(code1));
    vm->num_insts = sizeof(code1)/sizeof(vm->insts[0]);

    uint64_t ret;
    if (ubpf_exec(vm, &bpf, sizeof(bpf), &ret) < 0)
        ret = UINT64_MAX;

    ubpf_destroy(vm);
	return ret;
}

int main() {
    int i=0;
    Mem2 mem2 = {0, {2500, "goooood"}};

    while(1){
        printf("%d\n",i++);
        printf("ptrace demo! [pid:%d]\n", getpid());
        printf("orig_c0(mem): %d\nfix_func(mem):%d\n", orig_c0(mem2), fix_func(mem2));
        //printf("orig_c0: %d\n", orig_c0(mem2));
        sleep(2);
    }
    
    return 0;
}

// cc -Wall -Werror -Iinc -O2 -g -Wunused-parameter -fPIC   -c -o test.o test.c

// cc   test.o libubpf.a  -lm -o test