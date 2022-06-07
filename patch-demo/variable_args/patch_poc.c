#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	uint64_t a3;
	uint64_t a4;
	uint64_t a5;
	uint64_t a6;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

uint64_t patch_dispatcher(stack_frame *frame);
void patch_handler();

#define offsetof(type, member) ((size_t) &((type *)0)->member)

// 48 b8 ff ff ff ff ff ff ff ff    movabs $0xffffffffffffffff,%rax
// ff e0                            jmpq   *%rax
void DSU(void *old, void *new) {
	#define ROUNDDOWN(ptr) ((void *)(((uintptr_t)ptr) & ~0xfff))
	size_t pg_size = sysconf(_SC_PAGESIZE);
	char *pg_boundary = ROUNDDOWN(old);
	int flags = PROT_WRITE | PROT_READ | PROT_EXEC;

	printf("Dynamically updating... "); fflush(stdout);

	mprotect(pg_boundary, 2 * pg_size, flags);
	memcpy(old +  0, "\x48\xb8", 2);
	memcpy(old +  2,       &new, 8);
	memcpy(old + 10, "\xff\xe0", 2);
	mprotect(pg_boundary, 2 * pg_size, flags & ~PROT_WRITE);

	printf("Done\n"); fflush(stdout);
}

void old_func() {
	printf("This is Old Function\n");
}

void new_func() {
	printf("This is New Function\n");
}

struct ptr {
	int *p;
};

/*
前6个参数用寄存器传参：
*/
int func_to_patch(int a1, int *a2, struct ptr *p3, int a4, int *a5, struct ptr *p6) {
	register uint64_t rbp asm("rbp"); // mov rbp = rsp
	register uint64_t rsp asm("rsp");
	register uint64_t rdi asm("rdi");
	register uint64_t rsi asm("rsi");
	register uint64_t rdx asm("rdx");
	register uint64_t rcx asm("rcx");
	register uint64_t r8 asm("r8");
	register uint64_t r9 asm("r9");
	uint64_t bp = rbp;
	uint64_t s1 = rdi, s2 = rsi, s3 = rdx, s4 = rcx, s5 = r8, s6 = r9;
	printf("rbp: %p\n", rbp);
	printf("[func_to_patch]\n a1:%d a2:%d a3:%d a4:%d a5:%d a6:%d\n", a1, *a2, *p3->p, a4, *a5, *p6->p);

	// 从寄存器再次获取参数
	int a1_ = s1;
	int a2_ = *(int *)s2;
	int a3_ = *((struct ptr *)s3)->p;
	int a4_ = s4;
	int a5_ = *(int *)s5;
	int a6_ = *((struct ptr *)s6)->p;
	printf("[from_register]\n a1:%d a2:%d a3:%d a4:%d a5:%d a6:%d\n", a1_, a2_, a3_, a4_, a5_, a6_);

	return a1 + *a2 + *p3->p + a4 + *a5 + *p6->p;
}


static void basic_test() {
	old_func();
	DSU(old_func, new_func);
	old_func();
	
	printf("stack_frame size:%d off1:%d off2:%d\n", sizeof(stack_frame), offsetof(stack_frame, a1), offsetof(stack_frame, a2));

	// patch_handler();
}


void patch_test() {
	int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6;
	struct ptr p3 = {&a3}, p6 = {&a6};

	int ret1 = func_to_patch(a1, &a2, &p3, a4, &a5, &p6);
	printf("before patch ret:%d\n", ret1);
	DSU(func_to_patch, patch_handler);
	int ret2 = func_to_patch(a1, &a2, &p3, a4, &a5, &p6);
	printf("after patch ret:%d\n", ret2);
	assert(ret1 == ret2);
}

int main() {
	printf("test variable number args\n");
	
	// basic_test();

	patch_test();

	return 0;
}

// https://git.musl-libc.org/cgit/musl/tree/src/setjmp/x86_64/setjmp.s
/*
GCC内嵌汇编：
https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
Store all registers to stack
1. arguments: 参数传递相关的寄存器
arg1-arg6: rdi, rsi, rdx, rcx, r8, r9

2. callee saved registers：避免被后面的函数修改状态
callee saved: rbx, rbp, r12, r13, r14, r15

*/
__attribute__((naked))
void patch_handler() {
	__asm__ __volatile__ (
		"push %rbp \n\t"

		// save arguments to stack
		"sub $0x30,%rsp \n\t"
		"mov %rsp,%rbp \n\t"
		"mov %rdi,0x00(%rbp) \n\t"
		"mov %rsi,0x08(%rbp) \n\t"
		"mov %rdx,0x10(%rbp) \n\t"
		"mov %rcx,0x18(%rbp) \n\t"
		"mov %r8,0x20(%rbp) \n\t"
		"mov %r9,0x28(%rbp) \n\t"

		// save context
		"sub $0x30,%rsp \n\t"
		"mov %rsp,%rbp \n\t"
		"mov %rbx, 0x00(%rbp) \n\t"
		"mov %r12, 0x08(%rbp) \n\t"
		"mov %r13, 0x10(%rbp) \n\t"
		"mov %r14, 0x18(%rbp) \n\t"
		"mov %r15, 0x20(%rbp) \n\t"
		"mov %rbp, 0x28(%rbp) \n\t"

		// patch_dispatcher(stack_pointer)
		"mov %rbp, %rdi \n\t" // arg1 = sp
		"add $0x30,%rdi \n\t" // arg1 = sp + 0x48
		"callq patch_dispatcher \n\t"

		// restore context
		"mov 0x00(%rbp), %rbx \n\t"
		"mov 0x08(%rbp), %r12 \n\t"
		"mov 0x10(%rbp), %r13 \n\t"
		"mov 0x18(%rbp), %r14 \n\t"
		"mov 0x20(%rbp), %r15 \n\t"
		"mov 0x28(%rbp), %rbp \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x30,%rsp \n\t" // 16 byte aligned
		"add $0x30,%rsp \n\t"
		"pop %rbp \n\t"
		"retq \n\t");
}

uint64_t patch_dispatcher(stack_frame *frame) {
	printf("patch_dispatcher: %p\n", (uint64_t)frame- 0x48);
	printf("Register: a1:%lx a2:%lx a3:%lx a4:%lx a5:%lx a6:%lx\n", frame->a1, frame->a2, frame->a3, frame->a4, frame->a5, frame->a6);
	printf("Address: a1:%lx a2:%lx a3:%lx a4:%lx a5:%lx a6:%lx\n", &frame->a1, &frame->a2, &frame->a3, &frame->a4, &frame->a5, &frame->a6);
	assert((uintptr_t)&frame->a2 - (uintptr_t)&frame->a1 == 8);
	
	// int a1, int *a2, struct ptr *p3, int a4, int *a5, struct ptr *p6
	int a1, a2, a3, a4, a5, a6;
	
	a1 = frame->a1;
	a2 = *(int *)(uintptr_t)(frame->a2);
	a3 = *((struct ptr*)(uintptr_t)frame->a3)->p;
	a4 = frame->a4;
	a5 = *(int *)(uintptr_t)(frame->a5);
	a6 = *((struct ptr*)(uintptr_t)frame->a6)->p;
	// int a2 = frame->a2, a3 = frame->a3, a4 = frame->a4, a5 = frame->a5, a6 = frame->a6;
	printf("Argument: a1:%d a2:%d a3:%d a4:%d a5:%d a6:%d\n", a1, a2, a3, a4, a5, a6);
	return a1 + a2 + a3 + a4 + a5 + a6;
}
