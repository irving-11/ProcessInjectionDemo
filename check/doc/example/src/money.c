/*
 * Check: a unit test framework for C
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
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

#include "money.h"

/*struct Money
{
    int amount;
    char *currency;
};

Money *money_create(int amount, char *currency)
{
    Money *m;

    if (amount < 0)
    {
        return NULL;
    }

    m = malloc(sizeof(Money));

    if (m == NULL)
    {
        return NULL;
    }

    m->amount = amount;
    m->currency = currency;
    return m;
}

int money_amount(Money * m)
{
    return m->amount;
}

char *money_currency(Money * m)
{
    return m->currency;
}

void money_free(Money * m)
{
    free(m);
    return;
}*/

// PATCH code
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

static int8_t code2[] = ""
"\x61\x12\x00\x00\x00\x00\x00\x00\x61\x11\x04\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\x4f"
"\x21\x00\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x01\x00\x00\x00\x55\x01\x01\x00\x00\x00\x00\x00\xb7\x00"
"\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

static int8_t code3[] = ""
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

static int8_t code4[] = ""
"\x61\x12\x00\x00\x00\x00\x00\x00\x61\x11\x04\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\x4f"
"\x21\x00\x00\x00\x00\x00\x00\x61\x13\x04\x00\x00\x00\x00\x00\x79\x12\x10\x00\x00\x00\x00\x00\x61\x24"
"\x00\x00\x00\x00\x00\x00\x5d\x34\x04\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x61\x11\x08"
"\x00\x00\x00\x00\x00\x61\x22\x04\x00\x00\x00\x00\x00\x1d\x12\x02\x00\x00\x00\x00\x00\x18\x00\x00\x00"
"\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

static int8_t code5[] = ""
"\x61\x12\x00\x00\x00\x00\x00\x00\x61\x11\x04\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\x4f"
"\x21\x00\x00\x00\x00\x00\x00\x61\x12\x08\x00\x00\x00\x00\x00\x55\x02\x05\x00\x00\x00\x00\x00\x79\x11"
"\x00\x00\x00\x00\x00\x00\x61\x12\x00\x00\x00\x00\x00\x00\x15\x02\x02\x00\x08\x00\x00\x00\xb7\x02\x00"
"\x00\x00\x00\x00\x00\x63\x21\x00\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00"
"\x00\x00\x00\x00"
"";

static int8_t code6[] = ""
"\x61\x12\x18\x00\x00\x00\x00\x00\x61\x11\x1c\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\x4f"
"\x21\x00\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x61\x12\x00\x00\x00\x00\x00\x00\x55\x02"
"\x0a\x00\x02\x00\x00\x00\xb7\x00\x00\x00\x02\x00\x00\x00\x61\x12\x0c\x00\x00\x00\x00\x00\x25\x02\x07"
"\x00\xff\x7f\x00\x00\x79\x12\x10\x00\x00\x00\x00\x00\x61\x22\x04\x00\x00\x00\x00\x00\x15\x02\x04\x00"
"\x00\x00\x00\x00\x61\x11\x08\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x01\x00\x00\x00\x55\x01\x01\x00\x00"
"\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

static int8_t code7[] = ""
"\x61\x12\x04\x00\x00\x00\x00\x00\x67\x02\x00\x00\x20\x00\x00\x00\x61\x13\x00\x00\x00\x00\x00\x00\x4f"
"\x32\x00\x00\x00\x00\x00\x00\x79\x22\x08\x00\x00\x00\x00\x00\x61\x13\x0c\x00\x00\x00\x00\x00\x67\x03"
"\x00\x00\x20\x00\x00\x00\x61\x14\x08\x00\x00\x00\x00\x00\x4f\x43\x00\x00\x00\x00\x00\x00\x61\x22\x04"
"\x00\x00\x00\x00\x00\x63\x23\x00\x00\x00\x00\x00\x00\xbf\xa2\x00\x00\x00\x00\x00\x00\x07\x02\x00\x00"
"\xfc\xff\xff\xff\xbf\x23\x00\x00\x00\x00\x00\x00\x77\x03\x00\x00\x20\x00\x00\x00\x63\x31\x0c\x00\x00"
"\x00\x00\x00\x63\x21\x08\x00\x00\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

#define JMP(off) ((struct jmp) { 0xe9, off - sizeof(struct jmp) })
#define PG_SIZE sysconf(_SC_PAGESIZE)

struct jmp {
	uint32_t opcode: 8;
	int32_t  offset: 32;
} __attribute__((packed));

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	uint64_t a3;
    uint64_t a4;
	uint64_t a5;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

int run_ebpf(stack_frame *frame, const char *bytecode, unsigned long len)
{
    struct ubpf_vm *vm = ubpf_create();
    if (!vm) {
        fprintf(stderr, "Failed to create VM\n");
        return 1;
    }

    vm->insts = malloc(len);
    if (vm->insts == NULL) {
        return -1;
    }
    memcpy(vm->insts, bytecode, len);
    vm->num_insts = len/sizeof(vm->insts[0]);

    uint64_t ret;
    if (ubpf_exec(vm, frame, sizeof(*frame), &ret) < 0)
        ret = UINT64_MAX;

    ubpf_destroy(vm);
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

// cve_2015_3417
typedef struct H264Picture{
    int needs_realloc;
}H264Picture;

typedef struct H264Context
{
    H264Picture *DPB;
    H264Picture *delayed_pic[18];
}H264Context;

void orig_c1(H264Context *h, int free_rbsp) {
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

__attribute__((naked)) void patch_handler1() {
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
		"callq patch_dispatcher1 \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x10,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

uint64_t patch_dispatcher1(stack_frame *frame) {
	int ret = run_ebpf(frame, (const char *)code1, sizeof(code1));
	return ret;
}

int test_cve_2015_3417() 
{
	int free_rbsp = 1;    
	H264Context *h; H264Picture *dpb; 
    dpb = (H264Picture *)malloc(sizeof(H264Picture));
    dpb->needs_realloc = 1;

	h = (H264Context *)malloc(sizeof(H264Context));
    h->DPB = dpb;
    h->delayed_pic[0] = dpb;
    h->delayed_pic[1] = dpb;
	
	hook(orig_c1, patch_handler1);
	orig_c1(h, free_rbsp);

	if(h->delayed_pic[0] == (H264Picture *)0){
		return 1;
	}else if (h->delayed_pic[0]->needs_realloc == 1){
		return 0;
	}
    
    return 0;
}

// cve_2015_0205
#define EVP_PKT_SIGN    0x0010
int orig_c2(int *s) 
{
    int type = 1;
    int *peer;//, value = 11;
    peer = s;

    if ((peer != NULL) && (type & EVP_PKT_SIGN))
        return 1;

    return 0;
}

__attribute__((naked)) void patch_handler2() {
	__asm__ __volatile__ (
		"push %rbp \n\t"

		// save arguments to stack
		"sub $0x8,%rsp \n\t"
		"mov %rsp,%rbp \n\t"
		"mov %rdi,0x00(%rbp) \n\t"
		//"mov %rsi,0x08(%rbp) \n\t"
		//"mov %rdx,0x10(%rbp) \n\t"

		// patch_dispatcher(stack_pointer)
		"mov %rbp, %rdi \n\t" // arg1 = sp
		"callq patch_dispatcher2 \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x8,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

uint64_t patch_dispatcher2(stack_frame *frame) {
	int ret = run_ebpf(frame, (const char *)code2, sizeof(code2));
	return ret;
}

int test_cve_2015_0205(int *input) 
{
    hook(orig_c2, patch_handler2);

	int result = orig_c2(input);
	if(result == 1){
		// printf("This is New Function\n");
        return 1;
	}else if (result == 0){
		// printf("This is Old Function\n");
        return 0;
	}
    
    return 0;
}

// cve_2017_12613
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

int orig_c3(long *t, apr_time_exp_t *xt) {
    unsigned long year = xt->tm_year;
    unsigned long days;
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
    *t = days * (unsigned long)1000000 + xt->tm_usec;

    return 0;
}

__attribute__((naked)) void patch_handler3() {
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
		"callq patch_dispatcher3 \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x10,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

uint64_t patch_dispatcher3(stack_frame *frame) {
	int ret = run_ebpf(frame, (const char *)code3, sizeof(code3));
	return ret;
}

int test_cve_2017_12613(int input) {
	long *t = NULL; apr_time_exp_t *xt;
	xt = (apr_time_exp_t *)malloc(sizeof(apr_time_exp_t));
	xt->tm_year = 1998;
    xt->tm_mon = input;
    xt->tm_mday = 1;
    xt->tm_hour = 1;
    xt->tm_min = 1;
    xt->tm_sec = 1;
    xt->tm_usec = 1;
	
	hook(orig_c3, patch_handler3);
	
	int result = orig_c3(t, xt);
	if(result == 20004){
		return 1;
	}else if (result == 20000){
		return 0;
	}else if (result == 0){
		return 0;
	}
    
    return 0;
}

// cve_2017_7862
typedef struct AVCodecContext
{
    int bits_per_raw_sample;
    int width, height;
    void *priv_data;
} AVCodecContext;
typedef struct PicContext {
    int width, height;
    int nb_planes;
    // GetByteContext g;
} PicContext;
typedef struct AVPacket {
    int   size;
} AVPacket;

int orig_c4(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt) {
    int ret = 0;
    PicContext *s = avctx->priv_data;

    if (s->width != avctx->width && s->height != avctx->height)
    // patch
    //if (s->width != avctx->width || s->height != avctx->height) 
        ret = -1;
    
    return ret;
}

__attribute__((naked)) void patch_handler4() {
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
		"callq patch_dispatcher4 \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x20,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

uint64_t patch_dispatcher4(stack_frame *frame) {
	int ret = run_ebpf(frame, (const char *)code4, sizeof(code4));
	return ret;
}

int test_cve_2017_7862(int height, int width) {
	AVCodecContext *avctx; PicContext *pictx;
    avctx = (AVCodecContext *)malloc(sizeof(AVCodecContext));
    avctx->height = 1; avctx->width = 1;

    pictx = (PicContext *)malloc(sizeof(PicContext));
    pictx->height = height; pictx->width = width;
    // OR
    // pictx->height = 2; pictx->width = 1;
    // OR
    // pictx->height = 1; pictx->width = 1;
    avctx->priv_data = (void *)pictx;
	
    hook(orig_c4, patch_handler4);
	int result = orig_c4(avctx, (void *)0, (int *)0, (AVPacket *)0);;
	if(result == -1){
		// printf("This is New Function\n");
        return 1;
	}else if (result == 0){
		// printf("This is Old Function\n");
        return 0;
	}

    return 0;
}

// cve_2018_12459
typedef struct AVCodecContext_1
{
    int bits_per_raw_sample;
} AVCodecContext_1;

typedef struct MpegEncContext {
    struct AVCodecContext_1 *avctx;
    int studio_profile;
} MpegEncContext;

typedef struct Mpeg4DecContext {
    MpegEncContext m;
    int rgb;
} Mpeg4DecContext;

int orig_c5(Mpeg4DecContext *ctx, void *gb) {
    //MpegEncContext *s = &ctx->m;//unused

    // patch
    //if (!s->studio_profile && s->avctx->bits_per_raw_sample != 8)
        //s->avctx->bits_per_raw_sample = 0;

    return 0;
}

__attribute__((naked)) void patch_handler5() {
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
		"callq patch_dispatcher5 \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x10,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

uint64_t patch_dispatcher5(stack_frame *frame) {
	int ret = run_ebpf(frame, (const char *)code5, sizeof(code5));
	return ret;
}

int test_cve_2018_12459(int bits_per_raw_sample, int studio_profile) 
{	
	Mpeg4DecContext *ctx;
    ctx = (Mpeg4DecContext *)malloc(sizeof(Mpeg4DecContext));
    MpegEncContext m;
    
    struct AVCodecContext_1 *avctx;
    avctx = (struct AVCodecContext_1 *)malloc(sizeof(struct AVCodecContext_1));
    avctx->bits_per_raw_sample = bits_per_raw_sample;
    m.studio_profile = studio_profile;
    m.avctx = avctx;
    ctx->m = m;
	
    hook(orig_c5, patch_handler5);
	orig_c5(ctx, (void *)0);
	if (ctx->m.avctx->bits_per_raw_sample == 0) {
    	// printf("This is New Function\n");
        return 1;
    } else if (ctx->m.avctx->bits_per_raw_sample == 1) {
    	// printf("This is Old Function\n");
        return 0;
    }
    
    return 0;
}

// cve_2018_14395
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

int orig_c6(void *s, void *pb, void *mov, MOVTrack *track) {
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

__attribute__((naked)) void patch_handler6() {
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
		"callq patch_dispatcher6 \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x20,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

uint64_t patch_dispatcher6(stack_frame *frame) {
	int ret = run_ebpf(frame, (const char *)code6, sizeof(code6));
	return ret;
}

int test_cve_2018_14395(int channels) {
	MOVTrack *track; 
    track = (MOVTrack *)malloc(sizeof(MOVTrack));
    track->tag = 0; track->mode = 2; track->timescale = 1; track->audio_vbr = 0;
    AVCodecParameters *par;
    par = (AVCodecParameters *)malloc(sizeof(AVCodecParameters));
    par->channels = channels;
    // OR
    // par->channels = 1;
    track->par = par;
	
    hook(orig_c6, patch_handler6);
	int result = orig_c6((void *)0, (void *)0, (void *)0, track);
	if (result == 2) {
		// printf("This is New Function\n");}
        return 1;
	} else if (result == 0){
		// printf("This is Old Function\n");}
        return 0;
    }

    return 0;
}

// cve_2019_9433
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

void orig_c7(VP8_COMMON *cm, int *source, int *post, int q, int low_var_thresh) {//, int flag) {
    const MODE_INFO *mode_info_context = cm->show_frame_mi;
    // patch
    // const MODE_INFO *mode_info_context = cm->mi;
    int i = mode_info_context->bmi[0].mv.as_int;
    // printf("i: %d\n", i);
    
    *source = i;
    source = &i;
}

__attribute__((naked)) void patch_handler7() {
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
		"callq patch_dispatcher7 \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x28,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

uint64_t patch_dispatcher7(stack_frame *frame) {
	int ret = run_ebpf(frame, (const char *)code7, sizeof(code7));
	return ret;
}

int test_cve_2019_9433() {
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
	
    hook(orig_c7, patch_handler7);
	orig_c7(cm, source, (int *)0, 0, 0);
	if (*source == 2) {
		// printf("This is New Function\n");}
        return 1;
	} else if (*source == 1){
		// printf("This is Old Function\n");}
        return 0;
    }
    
    return 0;
}