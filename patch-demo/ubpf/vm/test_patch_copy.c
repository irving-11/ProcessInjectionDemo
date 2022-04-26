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

// disassemble: 
// ldxw r1, [r1]
// lsh r1, 0x20
// arsh r1, 0x20
// mov r0, 0xffffffff
// jsgt r1, 0x1388, +1
// mov r0, 0x0
// exit

static uint8_t code0[] = ""
"\x61\x11\x00\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\xc7\x01\x00\x00\x20\x00\x00\x00\xb7"
"\x00\x00\x00\xff\xff\xff\xff\x65\x01\x01\x00\x88\x13\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x95\x00"
"\x00\x00\x00\x00\x00\x00"
"";

struct Mem
{
    uint32_t a;
    //uint32_t b;
};

int orig_c0(int v) {
	if (v > 2000) { // fixed: v > 5000 return -1
		//DEBUG_LOG("test_dynamic_bug-112: %d\n", v);
		return -1;
	}
	//DEBUG_LOG("test_dynamic_bug-: %d\n", v);
	return 0;
}

int fix_func(int v){
    if (v > 5000){
        return -1;
    }
    return 0;
}



int main() {
    //这样传参只能说明ebpf patch是有效的？??
	struct Mem *bpf = malloc(sizeof(struct bpf*));// = (struct Mem *)mem;
    bpf->a = 3000;
    //bpf->b = 1;

    struct ubpf_vm *vm = ubpf_create();
    if (!vm) {
        fprintf(stderr, "Failed to create VM\n");
        return 1;
    }

    vm->insts = malloc(sizeof(code0));
    if (vm->insts == NULL) {
        return -1;
    }
    memcpy(vm->insts, code0, sizeof(code0));
    vm->num_insts = sizeof(code0)/sizeof(vm->insts[0]);

    uint64_t ret;
    if (ubpf_exec(vm, &bpf, sizeof(bpf), &ret) < 0)
        ret = UINT64_MAX;

    printf("0x%"PRIx64"\n", ret);
    ubpf_destroy(vm);

    printf("orig_c0(2500): %d\n", orig_c0(2500));
    return 0;
}

// cc -Wall -Werror -Iinc -O2 -g -Wunused-parameter -fPIC   -c -o test.o test.c

// cc   test.o libubpf.a  -lm -o test
