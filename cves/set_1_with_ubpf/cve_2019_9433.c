/*
note: "possible information disclosure due to improper input validation."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2019_9433
commit link: https://github.com/webmproject/libvpx/commit/52add5896661d186dec284ed646a4b33b607d2c7
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
"\x61\x12\x04\x00\x00\x00\x00\x00\x67\x02\x00\x00\x20\x00\x00\x00\x61\x13\x00\x00\x00\x00\x00\x00\x4f"
"\x32\x00\x00\x00\x00\x00\x00\x79\x22\x08\x00\x00\x00\x00\x00\x61\x13\x0c\x00\x00\x00\x00\x00\x67\x03"
"\x00\x00\x20\x00\x00\x00\x61\x14\x08\x00\x00\x00\x00\x00\x4f\x43\x00\x00\x00\x00\x00\x00\x61\x22\x04"
"\x00\x00\x00\x00\x00\x63\x23\x00\x00\x00\x00\x00\x00\xbf\xa2\x00\x00\x00\x00\x00\x00\x07\x02\x00\x00"
"\xfc\xff\xff\xff\xbf\x23\x00\x00\x00\x00\x00\x00\x77\x03\x00\x00\x20\x00\x00\x00\x63\x31\x0c\x00\x00"
"\x00\x00\x00\x63\x21\x08\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
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

typedef struct {
  unsigned char mode, uv_mode;
  unsigned char ref_frame;
} MB_MODE_INFO;

typedef struct {
  short row;
  short col;
} MV;
typedef union int_mv {
  unsigned int as_int;
  MV as_mv;
} int_mv; /* facilitates faster equality tests and copies */

typedef enum {
  B_DC_PRED, /* average of above and left pixels */
  B_MODE_COUNT
} B_PREDICTION_MODE;

union b_mode_info {
  B_PREDICTION_MODE as_mode;
  int_mv mv;
};

typedef struct modeinfo {
  MB_MODE_INFO mbmi;
  union b_mode_info bmi[16];
} MODE_INFO;

typedef struct VP8Common {
  int Width;

  MODE_INFO *mi;  /* Corresponds to upper left visible macroblock */
  MODE_INFO *show_frame_mi;
} VP8_COMMON;


uint64_t patch_dispatcher(stack_frame *frame);
void patch_handler();

void orig_c0(VP8_COMMON *cm, int *source, int *post, int q, int low_var_thresh) {//, int flag) {
    const MODE_INFO *mode_info_context = cm->show_frame_mi;
    // patch
    // const MODE_INFO *mode_info_context = cm->mi;
    int i = mode_info_context->bmi[0].mv.as_int;
    // printf("i: %d\n", i);
    
    *source = i;
    source = &i;
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
	int b = 0;
    VP8_COMMON *cm; int *source = &b;
    cm = (VP8_COMMON *)malloc(sizeof(VP8_COMMON));
    MODE_INFO *show_frame_mi;
    show_frame_mi = (MODE_INFO *)malloc(sizeof(MODE_INFO));
    MODE_INFO *mi;
    mi = (MODE_INFO *)malloc(sizeof(MODE_INFO));
    // MB_MODE_INFO mbmi;
    union b_mode_info bmi_1[16], bmi_2[16];
    int_mv mv_1, mv_2;
    mv_1.as_int = 1;
    mv_2.as_int = 2;
    bmi_1[0].mv = mv_1;
    bmi_2[0].mv = mv_2;
    memcpy(show_frame_mi->bmi, bmi_1, sizeof(bmi_1));
    memcpy(mi->bmi, bmi_2, sizeof(bmi_2));
    
    cm->show_frame_mi = show_frame_mi;
    cm->mi = mi;
	
	int i = 0;
	while(1){
		printf("tick: %d\n", i);
		printf("Demo! [pid:%d]\n", getpid());
		orig_c0(cm, source, (int *)0, 0, 0);
		if (*source == 2) {
			printf("This is New Function\n");}
		else if (*source == 1){
			printf("This is Old Function\n");}
        
        i++;
        sleep(2);
	}
    
    return 0;
}

// cc -Wall -Werror -Iinc -O2 -g -Wunused-parameter -fPIC   -c -o test.o test.c

// cc   test.o libubpf.a  -lm -o test

/*int main() {
	int b = 0;
    VP8_COMMON *cm; int *source = &b;
    cm = (VP8_COMMON *)malloc(sizeof(VP8_COMMON));
    MODE_INFO *show_frame_mi;
    show_frame_mi = (MODE_INFO *)malloc(sizeof(MODE_INFO));
    MODE_INFO *mi;
    mi = (MODE_INFO *)malloc(sizeof(MODE_INFO));
    // MB_MODE_INFO mbmi;
    union b_mode_info bmi_1[16], bmi_2[16];
    int_mv mv_1, mv_2;
    mv_1.as_int = 1;
    mv_2.as_int = 2;
    bmi_1[0].mv = mv_1;
    bmi_2[0].mv = mv_2;
    memcpy(show_frame_mi->bmi, bmi_1, sizeof(bmi_1));
    memcpy(mi->bmi, bmi_2, sizeof(bmi_2));
    
    cm->show_frame_mi = show_frame_mi;
    cm->mi = mi;

    // cm->show_frame_mi->bmi->mv.as_int = 1;
    // cm->mi->bmi->mv.as_int = 2;

    dummy_cve_2019_9433_vp8_deblock(cm, source, (int *)0, 0, 0, 0);

    if (*source == 2) {
		printf("after patch\n");}
	else if (*source == 1){
		printf("before patch\n");}
    return 0;
}*/
// what's wrong???
