/*
note: "Fixes use of freed memory." BY adding memset().
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2015-3417
commit link: https://github.com/FFmpeg/FFmpeg/commit/e8714f6f93d1a32f4e4655209960afcf4c185214
*/

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
#include <sys/mman.h>

#define JMP(off) ((struct jmp) { 0xe9, off - sizeof(struct jmp) })
#define PG_SIZE sysconf(_SC_PAGESIZE)

struct jmp {
	uint32_t opcode: 8;
	int32_t  offset: 32;
} __attribute__((packed));

static int8_t code1[] = ""
"\x61\x13\x04\x00\x00\x00\x00\x00\x67\x03\x00\x00\x20\x00\x00\x00\x61\x12\x00\x00\x00\x00\x00\x00\x4f"
"\x23\x00\x00\x00\x00\x00\x00\x79\x32\x00\x00\x00\x00\x00\x00\x61\x11\x08\x00\x00\x00\x00\x00\x15\x01"
"\x15\x00\x00\x00\x00\x00\x15\x02\x3a\x00\x00\x00\x00\x00\xb7\x01\x00\x00\x00\x00\x00\x00\x7b\x13\x90"
"\x00\x00\x00\x00\x00\x7b\x13\x88\x00\x00\x00\x00\x00\x7b\x13\x80\x00\x00\x00\x00\x00\x7b\x13\x78\x00"
"\x00\x00\x00\x00\x7b\x13\x70\x00\x00\x00\x00\x00\x7b\x13\x68\x00\x00\x00\x00\x00\x7b\x13\x60\x00\x00"
"\x00\x00\x00\x7b\x13\x58\x00\x00\x00\x00\x00\x7b\x13\x50\x00\x00\x00\x00\x00\x7b\x13\x48\x00\x00\x00"
"\x00\x00\x7b\x13\x40\x00\x00\x00\x00\x00\x7b\x13\x38\x00\x00\x00\x00\x00\x7b\x13\x30\x00\x00\x00\x00"
"\x00\x7b\x13\x28\x00\x00\x00\x00\x00\x7b\x13\x20\x00\x00\x00\x00\x00\x7b\x13\x18\x00\x00\x00\x00\x00"
"\x7b\x13\x10\x00\x00\x00\x00\x00\x7b\x13\x08\x00\x00\x00\x00\x00\x05\x00\x26\x00\x00\x00\x00\x00\x15"
"\x02\x25\x00\x00\x00\x00\x00\xb7\x01\x00\x00\x01\x00\x00\x00\x63\x12\x8c\x00\x00\x00\x00\x00\x63\x12"
"\x88\x00\x00\x00\x00\x00\x63\x12\x84\x00\x00\x00\x00\x00\x63\x12\x80\x00\x00\x00\x00\x00\x63\x12\x7c"
"\x00\x00\x00\x00\x00\x63\x12\x78\x00\x00\x00\x00\x00\x63\x12\x74\x00\x00\x00\x00\x00\x63\x12\x70\x00"
"\x00\x00\x00\x00\x63\x12\x6c\x00\x00\x00\x00\x00\x63\x12\x68\x00\x00\x00\x00\x00\x63\x12\x64\x00\x00"
"\x00\x00\x00\x63\x12\x60\x00\x00\x00\x00\x00\x63\x12\x5c\x00\x00\x00\x00\x00\x63\x12\x58\x00\x00\x00"
"\x00\x00\x63\x12\x54\x00\x00\x00\x00\x00\x63\x12\x50\x00\x00\x00\x00\x00\x63\x12\x4c\x00\x00\x00\x00"
"\x00\x63\x12\x48\x00\x00\x00\x00\x00\x63\x12\x44\x00\x00\x00\x00\x00\x63\x12\x40\x00\x00\x00\x00\x00"
"\x63\x12\x3c\x00\x00\x00\x00\x00\x63\x12\x38\x00\x00\x00\x00\x00\x63\x12\x34\x00\x00\x00\x00\x00\x63"
"\x12\x30\x00\x00\x00\x00\x00\x63\x12\x2c\x00\x00\x00\x00\x00\x63\x12\x28\x00\x00\x00\x00\x00\x63\x12"
"\x24\x00\x00\x00\x00\x00\x63\x12\x20\x00\x00\x00\x00\x00\x63\x12\x1c\x00\x00\x00\x00\x00\x63\x12\x18"
"\x00\x00\x00\x00\x00\x63\x12\x14\x00\x00\x00\x00\x00\x63\x12\x10\x00\x00\x00\x00\x00\x63\x12\x0c\x00"
"\x00\x00\x00\x00\x63\x12\x08\x00\x00\x00\x00\x00\x63\x12\x04\x00\x00\x00\x00\x00\x63\x12\x00\x00\x00"
"\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

typedef struct H264Picture{
    int needs_realloc;
}H264Picture;

typedef struct H264Context
{
    H264Picture *DPB;
    H264Picture *delayed_pic[18];
}H264Context;

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	//uint64_t a3;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

uint64_t patch_dispatcher(stack_frame *frame);
void patch_handler();

void orig_c0(H264Context *h, int free_rbsp) {
    int i;
    if (free_rbsp && h->DPB) {
        /*for (i = 0; i < 36; i++)            
            printf("1");*/
        // patch 
        // memset(h->delayed_pic, 0, sizeof(h->delayed_pic));
    } else if (h->DPB) {
        for (i = 0; i < 36; i++)
            h->DPB[i].needs_realloc = 1;
    }
}

int run_ebpf(stack_frame *frame)
{
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
    if (ubpf_exec(vm, frame, sizeof(*frame), &ret) < 0)
        ret = UINT64_MAX;

    ubpf_destroy(vm);
	return ret;
}

__attribute__((naked))
void patch_handler() {
	__asm__ __volatile__ (
		"push %rbp \n\t"

		// save arguments to stack
		"sub $0x10,%rsp \n\t"
		"mov %rsp,%rbp \n\t"
		"mov %rdi,0x00(%rbp) \n\t"
		"mov %rsi,0x08(%rbp) \n\t"
		//"mov %rdx,0x10(%rbp) \n\t"
		//"mov %rcx,0x18(%rbp) \n\t"
		//"mov %r8,0x20(%rbp) \n\t"
		//"mov %r9,0x28(%rbp) \n\t"

		// patch_dispatcher(stack_pointer)
		"mov %rbp, %rdi \n\t" // arg1 = sp
		"callq patch_dispatcher \n\t"

		// // restore context
		// "mov 0x00(%rbp), %rbx \n\t"
		// "mov 0x08(%rbp), %r12 \n\t"
		// "mov 0x10(%rbp), %r13 \n\t"
		// "mov 0x18(%rbp), %r14 \n\t"
		// "mov 0x20(%rbp), %r15 \n\t"
		// "mov 0x28(%rbp), %rbp \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x10,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

uint64_t patch_dispatcher(stack_frame *frame) {
	int ret = run_ebpf(frame);
	return ret;
}

static inline bool within_page(void *addr) {
	return (uintptr_t)addr % PG_SIZE + sizeof(struct jmp) <= PG_SIZE;
}

void hook(void *old, void *new) {
	void *base = (void *)((uintptr_t)old & ~(PG_SIZE - 1));
	size_t len = PG_SIZE * (within_page(old) ? 1 : 2);
	
	int flags = PROT_WRITE | PROT_READ | PROT_EXEC;
	if (mprotect(base, len, flags) == 0) {
		*(struct jmp *)old = JMP((char *)new - (char *)old); // **PATCH**
		mprotect(base, len, flags & ~PROT_WRITE);
	} else {
		perror("DSU fail\n");
	}
}

int main() {
	int free_rbsp = 1;    
	H264Context *h; H264Picture *dpb; 
    dpb = (H264Picture *)malloc(sizeof(H264Picture));
    dpb->needs_realloc = 1;

	h = (H264Context *)malloc(sizeof(H264Context));
    h->DPB = dpb;
    h->delayed_pic[0] = dpb;
    h->delayed_pic[1] = dpb;
	
	int i = 0;
	while(1){
		printf("tick: %d\n", i);
		printf("Demo! [pid:%d]\n", getpid());
		
		//hook(orig_c0, patch_handler);
		orig_c0(h, free_rbsp);
		
		if(h->delayed_pic[0] == (H264Picture *)0){
			printf("This is New Function\n");
		}else if (h->delayed_pic[0]->needs_realloc == 1){
			printf("This is Old Function\n");
		}
        
        i++;
        sleep(2);
	}
    
    return 0;
}

// cc -Wall -Werror -Iinc -O2 -g -Wunused-parameter -fPIC   -c -o test.o test.c

// cc   test.o libubpf.a  -lm -o test

/*int main() {
	int free_rbsp = 1;    
	H264Context *h; H264Picture *dpb; 
    dpb = (H264Picture *)malloc(sizeof(H264Picture));
    dpb->needs_realloc = 1;
    
	h = (H264Context *)malloc(sizeof(H264Context));
    h->DPB = dpb;
    h->delayed_pic[0] = dpb;
    h->delayed_pic[1] = dpb;
	dummy_cve_2015_3417_ff_h264_free_tables(h, free_rbsp);
	if (h->delayed_pic[0] == (H264Picture *)0){
		printf("after patch\n");}
	else if (h->delayed_pic[0]->needs_realloc == 1){
		printf("before patch\n");}
		
    return 0;
}*/
