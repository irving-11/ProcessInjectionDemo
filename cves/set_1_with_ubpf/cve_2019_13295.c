/*
note: "a heap-based buffer over-read, because a width of zero is mishandled."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2019_13295
commit link: https://github.com/ImageMagick/ImageMagick/commit/a7759f410b773a1dd57b0e1fb28112e1cd8b97bc
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

static int8_t code1[] = ""
"\x61\x18\x08\x00\x00\x00\x00\x00\x61\x17\x0c\x00\x00\x00\x00\x00\xb7\x01\x00\x00\x01\x00\x00\x00\x85"
"\x10\x00\x00\xff\xff\xff\xff\xbf\x06\x00\x00\x00\x00\x00\x00\xb7\x01\x00\x00\x0b\x00\x00\x00\x73\x16"
"\x00\x00\x00\x00\x00\x00\xb7\x01\x00\x00\x01\x00\x00\x00\x85\x10\x00\x00\xff\xff\xff\xff\xb7\x01\x00"
"\x00\x16\x00\x00\x00\x73\x10\x00\x00\x00\x00\x00\x00\x67\x07\x00\x00\x20\x00\x00\x00\x4f\x87\x00\x00"
"\x00\x00\x00\x00\x15\x07\x01\x00\x00\x00\x00\x00\xbf\x06\x00\x00\x00\x00\x00\x00\xbf\x60\x00\x00\x00"
"\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

struct ptr {
	int *p;
};

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	uint64_t a3;
	uint64_t a4;
	uint64_t a5;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

uint8_t *patch_dispatcher(stack_frame *frame);
void patch_handler();

uint8_t *orig_c0(uint8_t *image, const size_t width, const size_t height, const double bias, uint8_t *exception) {
    uint8_t *threshold_image;
    uint8_t *value_1 = malloc(sizeof(uint8_t));
    *value_1 = 11;
    uint8_t *value_2 = malloc(sizeof(uint8_t));
    *value_2 = 22;

    threshold_image = value_1;

    if (threshold_image == (uint8_t *)NULL)
        return ((uint8_t *)NULL);
    // patch
    // if (width == 0)
        // return threshold_image;
    threshold_image = value_2;
    return threshold_image;
    // 通过指针指向的值来区分threshold_image
}

// IMPORTANT!!! change run_ebpf here!!!
uint8_t *run_ebpf(stack_frame *frame)
{
    struct ubpf_vm *vm = ubpf_create();
    if (!vm) {
        fprintf(stderr, "Failed to create VM\n");
        return NULL;
    }

    vm->insts = malloc(sizeof(code1));
    if (vm->insts == NULL) {
        return NULL;
    }
    memcpy(vm->insts, code1, sizeof(code1));
    vm->num_insts = sizeof(code1)/sizeof(vm->insts[0]);

    uint8_t *ret = NULL;
    if (ubpf_exec(vm, frame, sizeof(*frame), (uint64_t *)ret) < 0)
        ret = NULL;

    ubpf_destroy(vm);
	return ret;
}

__attribute__((naked))
void patch_handler() {
	__asm__ __volatile__ (
		"push %rbp \n\t"

		// save arguments to stack
		"sub $0x28,%rsp \n\t"
		"mov %rsp,%rbp \n\t"
		"mov %rdi,0x00(%rbp) \n\t"
		"mov %rsi,0x08(%rbp) \n\t"
		"mov %rdx,0x10(%rbp) \n\t"
		"mov %rcx,0x18(%rbp) \n\t"
		"mov %r8,0x20(%rbp) \n\t"
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
		"add $0x28,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

uint8_t *patch_dispatcher(stack_frame *frame) {
	//printf("Argument: a1:%ld a2:%ld a3:%ld\n", frame->a1, frame->a2, frame->a3);
	/*int a1, a2, a3;
	a1 = frame->a1;
	a2 = *(int *)(uintptr_t)(frame->a2);
	a3 = *((struct ptr*)(uintptr_t)frame->a3)->p;
	printf("Argument: a1:%d a2:%d a3:%d\n", a1, a2, a3);*/
	
	uint8_t *ret = run_ebpf(frame);
	return ret;
	//return 11;
}

int main() {
	uint8_t *ptr;
	int i = 0;
	while(1){
		printf("tick: %d\n", i);
		printf("Demo! [pid:%d]\n", getpid());
		ptr = orig_c0((void *)0, 0, 0, 0, (void *)0);
		if (*ptr == 11) {
			printf("This is New Function\n");}
		else if (*ptr == 22){
			printf("This is Old Function\n");}
        
        i++;
        sleep(2);
	}
    
    return 0;
}

// cc -Wall -Werror -Iinc -O2 -g -Wunused-parameter -fPIC   -c -o test.o test.c

// cc   test.o libubpf.a  -lm -o test

/*int main() {
	uint8_t *ptr;
	ptr = dummy_cve_2019_13295_AdaptiveThresholdImage((void *)0, 0, 0, 0, (void *)0);
	// ptr = dummy_cve_2019_13295_AdaptiveThresholdImage((void *)0, 1, 0, 0, (void *)0);
	
	if (*ptr == 11) {
		printf("after patch\n");}
	else if (*ptr == 22){
		printf("before patch\n");}
	return 0;
}*/

