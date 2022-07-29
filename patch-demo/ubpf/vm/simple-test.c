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

typedef struct stack_frame {
	int a1;
	// int a2;
} __attribute__ ((__packed__, aligned(4))) stack_frame;


int patch_dispatcher(stack_frame *frame);
void patch_handler();
static void register_functions(struct ubpf_vm *vm);

static int8_t bytecode[] = ""
"\xb7\x00\x00\x00\x01\x00\x00\x00\x61\x11\x00\x00\x00\x00\x00\x00\x67\x01\x00\x00\x20\x00\x00\x00\xc7"
"\x01\x00\x00\x20\x00\x00\x00\x65\x01\x02\x00\x88\x13\x00\x00\xb7\x01\x00\x00\x64\x00\x00\x00\x85\x00"
"\x00\x00\x01\x00\x00\x00\x95\x00\x00\x00\x00\x00\x00\x00"
"";

int vul_func(int v) {
    if (v > 2000) {
		return 1;
	}
	return 0;
}

int run_ebpf(stack_frame *frame)
{
    struct ubpf_vm *vm = ubpf_create();
    if (!vm) {
        fprintf(stderr, "Failed to create VM\n");
        return 1;
    }

	register_functions(vm);	

    vm->insts = malloc(sizeof(bytecode));
    if (vm->insts == NULL) {
        return -1;
    }
    memcpy(vm->insts, bytecode, sizeof(bytecode));
    vm->num_insts = sizeof(bytecode)/sizeof(vm->insts[0]);

    uint64_t ret;
    char *errmsg;
    // jit
    ubpf_jit_fn fn = ubpf_compile(vm, &errmsg);
    if(fn == NULL){
    	fprintf(stderr, "Failed to compile: %s\n", errmsg);
    	free(errmsg);
    	ret = UINT64_MAX;
    	return ret;
    }
    ret = fn(frame, sizeof(*frame));
    
    // no jit
    //if (ubpf_exec(vm, frame, sizeof(*frame), &ret) < 0)
        //ret = UINT64_MAX;

    ubpf_destroy(vm);
	return ret;
}

__attribute__((naked))
void patch_handler() {
	__asm__ __volatile__ (
		"push %rbp \n\t"

		// save arguments to stack
		"sub $0x8,%rsp \n\t"
		"mov %rsp,%rbp \n\t"
		"mov %rdi,0x00(%rbp) \n\t"
		//"mov %rsi,0x08(%rbp) \n\t"
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
		"add $0x8,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}

int patch_dispatcher(stack_frame *frame) {
	int ret = run_ebpf(frame);
	return ret;
}

int main() {
	int i = 0; int result = 0;
	while(1){
		printf("tick: %d\n", i);
		printf("Demo! [pid:%d]\n", getpid());
		
        result = vul_func(3000);
		if(result == 10){
			printf("This is New Function\n");
		}else if (result == 1){
			printf("This is Old Function\n");
		}
        
        i++;
        sleep(2);
	}
    return 0;
}

static uint32_t
new_sqrt(uint32_t x)
{
    return sqrt(x);
}

static uint64_t
unwind(uint64_t i)
{
    return i;
}

static void
register_functions(struct ubpf_vm *vm)
{
    ubpf_register(vm, 1, "new_sqrt", new_sqrt);
    ubpf_register(vm, 2, "strcmp_ext", strcmp);
    ubpf_register(vm, 3, "unwind", unwind);
    //ubpf_set_unwind_function_index(vm, 5);
}

