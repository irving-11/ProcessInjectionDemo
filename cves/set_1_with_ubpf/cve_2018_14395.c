/*
note: "allows attackers to cause a denial of service (application crash caused by a divide-by-zero error) with a user crafted audio file when converting to the MOV audio format."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2018_14395
commit link: https://github.com/FFmpeg/FFmpeg/commit/2c0e98a0b478284bdff6d7a4062522605a8beae5
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
"\x61\x12\x18\x00\x00\x00\x00\x00\x61\x11\x1c\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\x4f"
"\x21\x00\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x61\x12\x00\x00\x00\x00\x00\x00\x55\x02"
"\x0a\x00\x02\x00\x00\x00\xb7\x00\x00\x00\x02\x00\x00\x00\x61\x12\x0c\x00\x00\x00\x00\x00\x25\x02\x07"
"\x00\xff\x7f\x00\x00\x79\x12\x10\x00\x00\x00\x00\x00\x61\x22\x04\x00\x00\x00\x00\x00\x15\x02\x04\x00"
"\x00\x00\x00\x00\x61\x11\x08\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x01\x00\x00\x00\x55\x01\x01\x00\x00"
"\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

struct ptr {
	int *p;
};

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	uint64_t a3;
	uint64_t a4;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

typedef struct AVCodecParameters {
    unsigned int         codec_tag;
    // enum AVCodecID   codec_id;
    int channels;
}AVCodecParameters;

typedef struct MOVTrack {
    int         mode;
    int         tag;
    int         audio_vbr;
    unsigned    timescale;
    AVCodecParameters *par;
} MOVTrack;

#define MODE_MOV  0x02

uint64_t patch_dispatcher(stack_frame *frame);
void patch_handler();

int orig_c0(void *s, void *pb, void *mov, MOVTrack *track) {
    //unsigned int tag = track->tag;
    int version = 0;
    if (track->mode == MODE_MOV) {
    	if (track->timescale > 0x7fff) {
    	// patch
        // if (track->timescale > 0x7fff || !track->par->channels) {
            
            //tag = 11;
            //track->tag = 11;
            version = 2;
        } else if (track->audio_vbr) {
            version = 1;
        }
    }
    return version;
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
		"sub $0x20,%rsp \n\t"
		"mov %rsp,%rbp \n\t"
		"mov %rdi,0x00(%rbp) \n\t"
		"mov %rsi,0x08(%rbp) \n\t"
		"mov %rdx,0x10(%rbp) \n\t"
		"mov %rcx,0x18(%rbp) \n\t"
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
		"add $0x20,%rsp \n\t" // 16 byte aligned
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

int main() {
	MOVTrack *track; 
    track = (MOVTrack *)malloc(sizeof(MOVTrack));
    track->tag = 0; track->mode = 2; track->timescale = 1; track->audio_vbr = 0;
    AVCodecParameters *par;
    par = (AVCodecParameters *)malloc(sizeof(AVCodecParameters));
    par->channels = 0;
    // OR
    // par->channels = 1;
    track->par = par;
	
	int i = 0; int result = 0;
	while(1){
		printf("tick: %d\n", i);
		printf("Demo! [pid:%d]\n", getpid());
		result = orig_c0((void *)0, (void *)0, (void *)0, track);
		if (result == 2) {
			printf("This is New Function\n");}
		else if (result == 0){
			printf("This is Old Function\n");}
        
        i++;
        sleep(2);
	}
    
    return 0;
}

// cc -Wall -Werror -Iinc -O2 -g -Wunused-parameter -fPIC   -c -o test.o test.c

// cc   test.o libubpf.a  -lm -o test

/*int main() {
    MOVTrack *track; int ret = 0;
    track = (MOVTrack *)malloc(sizeof(MOVTrack));
    track->tag = 0; track->mode = 2; track->timescale = 1; 
    AVCodecParameters *par;
    par = (AVCodecParameters *)malloc(sizeof(AVCodecParameters));
    par->channels = 0;
    // OR
    // par->channels = 1;
    track->par = par;

    ret = dummy_cve_2018_14395_mov_write_audio_tag((void *)0, (void *)0, (void *)0, track);
    if (track->tag == 11) {
		printf("after patch\n");}
	else if (ret == 0){
		printf("before patch\n");}

    return 0;
}*/

