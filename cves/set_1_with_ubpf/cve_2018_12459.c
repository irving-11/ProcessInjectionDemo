/*
note: "An inconsistent bits-per-sample value may trigger an assertion violation while converting a crafted AVI file to MPEG4, leading to a denial of service."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2018_12459
commit link: https://github.com/FFmpeg/FFmpeg/commit/2fc108f60f98cd00813418a8754a46476b404a3c
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
"\x61\x12\x00\x00\x00\x00\x00\x00\x61\x11\x04\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\x4f"
"\x21\x00\x00\x00\x00\x00\x00\x61\x12\x08\x00\x00\x00\x00\x00\x55\x02\x05\x00\x00\x00\x00\x00\x79\x11"
"\x00\x00\x00\x00\x00\x00\x61\x12\x00\x00\x00\x00\x00\x00\x15\x02\x02\x00\x08\x00\x00\x00\xb7\x02\x00"
"\x00\x00\x00\x00\x00\x63\x21\x00\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00"
"\x00\x00\x00\x00"
"";

struct ptr {
	int *p;
};

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	//uint64_t a3;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

typedef struct AVCodecContext
{
    int bits_per_raw_sample;
} AVCodecContext;

typedef struct MpegEncContext {
    struct AVCodecContext *avctx;
    int studio_profile;
} MpegEncContext;

typedef struct Mpeg4DecContext {
    MpegEncContext m;
    int rgb;
} Mpeg4DecContext;

uint64_t patch_dispatcher(stack_frame *frame);
void patch_handler();

int orig_c0(Mpeg4DecContext *ctx, void *gb) {
    //MpegEncContext *s = &ctx->m;//unused

    // patch
    //if (!s->studio_profile && s->avctx->bits_per_raw_sample != 8)
        //s->avctx->bits_per_raw_sample = 0;

    return 0;
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
	//printf("???\n");
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
	//printf("Argument: a1:%ld a2:%ld a3:%ld\n", frame->a1, frame->a2, frame->a3);
	/*int a1, a2, a3;
	a1 = frame->a1;
	a2 = *(int *)(uintptr_t)(frame->a2);
	a3 = *((struct ptr*)(uintptr_t)frame->a3)->p;
	printf("Argument: a1:%d a2:%d a3:%d\n", a1, a2, a3);*/
	//printf("Argument: a1:%ld a2:%ld a3:%ld\n", frame->a1, frame->a2, frame->a3);
	int ret = run_ebpf(frame);
	return ret;
	//return 11;
}

int main() 
{	
	Mpeg4DecContext *ctx;
    ctx = (Mpeg4DecContext *)malloc(sizeof(Mpeg4DecContext));
    MpegEncContext m;
    
    struct AVCodecContext *avctx;
    avctx = (struct AVCodecContext *)malloc(sizeof(struct AVCodecContext));
    avctx->bits_per_raw_sample = 1;
    m.studio_profile = 0;
    m.avctx = avctx;
    ctx->m = m;
	
	int i = 0;
	while(1){
		printf("tick: %d\n", i);
		printf("Demo! [pid:%d]\n", getpid());
		orig_c0(ctx, (void *)0);
		if (ctx->m.avctx->bits_per_raw_sample == 0) {
        	printf("This is New Function\n");
    	} else if (ctx->m.avctx->bits_per_raw_sample == 1) {
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
    Mpeg4DecContext *ctx;
    ctx = (Mpeg4DecContext *)malloc(sizeof(Mpeg4DecContext));
    MpegEncContext m;
    
    struct AVCodecContext *avctx;
    avctx = (struct AVCodecContext *)malloc(sizeof(struct AVCodecContext));
    avctx->bits_per_raw_sample = 1;
    m.studio_profile = 0;
    // OR
    // avctx->bits_per_raw_sample = 8;
    // m.studio_profile = 0;
    // OR
    // avctx->bits_per_raw_sample = 1;
    // m.studio_profile = 1;
    m.avctx = avctx;
    ctx->m = m;

    // ctx->m.studio_profile = 0;
    // ctx->m.avctx->bits_per_raw_sample = 1;
    
    dummy_cve_2018_12459_ff_mpeg4_decode_picture_header(ctx, (void *)0);
    if (ctx->m.avctx->bits_per_raw_sample == 0) {
        printf("after patch\n");
    } else if (ctx->m.avctx->bits_per_raw_sample == 1) {
        printf("before patch\n");
    }

    return 0;
}*/
