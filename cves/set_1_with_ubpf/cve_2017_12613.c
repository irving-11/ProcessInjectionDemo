/*
note: "out of bounds memory may be accessed in converting this value to an apr_time_exp_t value."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2017_12613
commit link: https://github.com/apache/apr/commit/da388844b8c48acc5f6e80f2689de6887b03745b
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
"\x61\x13\x08\x00\x00\x00\x00\x00\x61\x12\x0c\x00\x00\x00\x00\x00\x67\x02\x00\x00\x20\x00\x00\x00\x4f"
"\x32\x00\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x24\x4e\x00\x00\x61\x24\x14\x00\x00\x00\x00\x00\x25\x04"
"\x3c\x00\x0b\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\xb7\x03\x00\x00\x01\x00\x00\x00\xb7\x05\x00"
"\x00\x02\x00\x00\x00\x2d\x45\x01\x00\x00\x00\x00\x00\xb7\x03\x00\x00\x00\x00\x00\x00\x61\x25\x18\x00"
"\x00\x00\x00\x00\x67\x05\x00\x00\x20\x00\x00\x00\xc7\x05\x00\x00\x20\x00\x00\x00\x1f\x35\x00\x00\x00"
"\x00\x00\x00\xbf\x56\x00\x00\x00\x00\x00\x00\x77\x06\x00\x00\x02\x00\x00\x00\xbf\x53\x00\x00\x00\x00"
"\x00\x00\x27\x03\x00\x00\x6d\x01\x00\x00\x0f\x63\x00\x00\x00\x00\x00\x00\x67\x04\x00\x00\x02\x00\x00"
"\x00\x18\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0f\x46\x00\x00\x00\x00\x00\x00"
"\x37\x05\x00\x00\x64\x00\x00\x00\x1f\x53\x00\x00\x00\x00\x00\x00\x07\x05\x00\x00\x03\x00\x00\x00\x77"
"\x05\x00\x00\x02\x00\x00\x00\x0f\x53\x00\x00\x00\x00\x00\x00\x61\x64\x00\x00\x00\x00\x00\x00\x61\x25"
"\x10\x00\x00\x00\x00\x00\x0f\x54\x00\x00\x00\x00\x00\x00\x67\x04\x00\x00\x20\x00\x00\x00\x18\x05\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff\x0f\x54\x00\x00\x00\x00\x00\x00\xc7\x04\x00\x00"
"\x20\x00\x00\x00\x0f\x43\x00\x00\x00\x00\x00\x00\x61\x14\x00\x00\x00\x00\x00\x00\x61\x11\x04\x00\x00"
"\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\x4f\x41\x00\x00\x00\x00\x00\x00\x61\x24\x0c\x00\x00\x00"
"\x00\x00\x67\x04\x00\x00\x20\x00\x00\x00\xc7\x04\x00\x00\x20\x00\x00\x00\x27\x03\x00\x00\x18\x00\x00"
"\x00\x0f\x34\x00\x00\x00\x00\x00\x00\x61\x23\x08\x00\x00\x00\x00\x00\x67\x03\x00\x00\x20\x00\x00\x00"
"\xc7\x03\x00\x00\x20\x00\x00\x00\x27\x04\x00\x00\x3c\x00\x00\x00\x0f\x34\x00\x00\x00\x00\x00\x00\x61"
"\x23\x04\x00\x00\x00\x00\x00\x67\x03\x00\x00\x20\x00\x00\x00\xc7\x03\x00\x00\x20\x00\x00\x00\x27\x04"
"\x00\x00\x3c\x00\x00\x00\x0f\x34\x00\x00\x00\x00\x00\x00\x61\x22\x00\x00\x00\x00\x00\x00\x67\x02\x00"
"\x00\x20\x00\x00\x00\xc7\x02\x00\x00\x20\x00\x00\x00\x27\x04\x00\x00\x40\x42\x0f\x00\x0f\x24\x00\x00"
"\x00\x00\x00\x00\x18\x02\x00\x00\x00\x80\xe6\x97\x00\x00\x00\x00\x92\x2b\xf8\xff\x0f\x24\x00\x00\x00"
"\x00\x00\x00\x7b\x41\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

struct ptr {
	int *p;
};

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	//uint64_t a3;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

typedef struct apr_time_exp_t {
    /** microseconds past tm_sec */
    int tm_usec;
    /** (0-61) seconds past tm_min */
    int tm_sec;
    /** (0-59) minutes past tm_hour */
    int tm_min;
    /** (0-23) hours past midnight */
    int tm_hour;
    /** (1-31) day of the month */
    int tm_mday;
    /** (0-11) month of the year */
    int tm_mon;
    /** year since 1900 */
    int tm_year;
    /** (0-6) days since Sunday */
    int tm_wday;
    /** (0-365) days since January 1 */
    int tm_yday;
    /** daylight saving time */
    int tm_isdst;
    /** seconds east of UTC */
    int tm_gmtoff;
} apr_time_exp_t;

uint64_t patch_dispatcher(stack_frame *frame);
void patch_handler();

int orig_c0(long *t, apr_time_exp_t *xt) {
    long year = xt->tm_year;
    long days;
    static const int dayoffset[12] = {306, 337, 0, 31, 61, 92, 122, 153, 184, 214, 245, 275};
    // patch
    // if (xt->tm_mon < 0 || xt->tm_mon >= 12)
        // return 20004;
    if (xt->tm_mon < 2)
        year--;
    days = year * 365 + year / 4 - year / 100 + (year / 100 + 3) / 4;

    days = year * 365 + year / 4 - year / 100 + (year / 100 + 3) / 4;
    days += dayoffset[xt->tm_mon] + xt->tm_mday - 1;
    days -= 25508;              /* 1 jan 1970 is 25508 days since 1 mar 1900 */
    days = ((days * 24 + xt->tm_hour) * 60 + xt->tm_min) * 60 + xt->tm_sec;

    if (days < 0) {
        return 20000;
    }
    *t = days * (long)1000000 + xt->tm_usec;

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

int main() {
	long *t = NULL; apr_time_exp_t *xt;
	xt = (apr_time_exp_t *)malloc(sizeof(apr_time_exp_t));
    xt->tm_mon = -1;
	
	int i = 0; int result = 0;
	while(1){
		printf("tick: %d\n", i);
		printf("Demo! [pid:%d]\n", getpid());
		result = orig_c0(t, xt);
		if(result == 20004){
			printf("This is New Function\n");
		}else if (result == 20000){
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
	long *t; apr_time_exp_t *xt; int result;
	xt = (apr_time_exp_t *)malloc(sizeof(apr_time_exp_t));
    xt->tm_mon = -1;
    // OR
    // xt->tm_mon = 1;
    // OR
    // xt->tm_mon = 13;

    result = dummy_cve_2017_12763_apr_time_exp_get(t, xt);
    if (result == 20004) {
		printf("after patch\n");}
	else if (result == 20000){
		printf("before patch\n");}
    return 0;
}*/
