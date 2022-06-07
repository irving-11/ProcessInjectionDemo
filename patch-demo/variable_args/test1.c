#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>

#define TEST_DEL(TAG) printf("\n---------------" TAG "---------------\n");

/* 1. 可变参数的实现
*/
// aligin by int
#define MY_INTSIZEOF(n) ((sizeof(n)+sizeof(uintptr_t)-1)&~(sizeof(uintptr_t) - 1))
/*
https://stackoverflow.com/questions/12371450/how-are-variable-arguments-implemented-in-gcc
*/
typedef unsigned char *my_valist;
#define myva_start(ap,v) ( ap = (my_valist)&v + MY_INTSIZEOF(v) )
#define myva_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define myva_end(ap) (ap= (my_valist) nullptr)

void test_variable_args() {
	// my_valist ap;
	// myva_start(ap, n);
	// int i = myva_arg(ap, int);
	// printf("%d\n", i);
	// myva_end(ap);
}


/* 2. 值类型和指针类型的参数
*/
typedef void (*BPF_CALL2)(void *, void *);
typedef void (*BPF_CALL3)(void *, void *, void *);
typedef void (*BPF_CALL4)(void *, void *, void *, void *);
typedef void (*BPF_CALL5)(void *, void *, void *, void *, void *);
typedef void (*BPF_CALL6)(void *, void *, void *, void *, void *, void *);
typedef void (*BPF_CALL7)(void *, void *, void *, void *, void *, void *, void *);
typedef void (*BPF_CALL8)(void *, void *, void *, void *, void *, void *, void *, void *);
typedef void (*BPF_CALL9)(void *, void *, void *, void *, void *, void *, void *, void *, void *);
typedef void (*BPF_CALL10)(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);

struct ptr {
	int *p;
};

void dump_4args(int a1, int *a2, int a3, int *a4, int a5, int *a6) {
	// register int64_t rax asm("rax"); return
	register uint64_t rdi asm("rdi");
	register uint64_t rsi asm("rsi");
	register uint64_t rdx asm("rdx");
	register uint64_t rcx asm("rcx");
	register uint64_t r8 asm("r8");
	register uint64_t r9 asm("r9");
	uint64_t s1 = rdi, s2 = rsi, s3 = rdx, s4 = rcx, s5 = r8, s6 = r9;
	printf("Register: rdi:%lx rsi:%lx rdx:%lx rcx:%lx r8:%lx r9:%lx\n", s1, s2, s3, s4, s5, s6);
	printf("Argument: s1:%lx s2:%lx s3:%lx s4:%lx\n", s1, *(int *)s2, s3, *(int *)s4);
	int v = *(int *)s2;
	// rsi会变化
	assert(s2 == (uint64_t) a2);
	printf("(s2:%lx %s rsi:%lx) v=%d a2:%lx a2=%d\n", s2, s2 == rsi ? "==" : "!=", rsi, v, a2, *(int *)a2);
}

// int, int*, struct*
void dump_6args(int a1, int *a2, struct ptr *p3, int a4, int *a5, struct ptr *p6) {
	// register int64_t rax asm("rax"); return
	register uint64_t rdi asm("rdi");
	register uint64_t rsi asm("rsi");
	register uint64_t rdx asm("rdx");
	register uint64_t rcx asm("rcx");
	register uint64_t r8 asm("r8");
	register uint64_t r9 asm("r9");
	uint64_t s1 = rdi, s2 = rsi, s3 = rdx, s4 = rcx, s5 = r8, s6 = r9;
	printf("Register: rdi:%lx rsi:%lx rdx:%lx rcx:%lx r8:%lx r9:%lx\n", s1, s2, s3, s4, s5, s6);
	printf("Argument: s1:%lx s2:%lx s3:%lx s4:%lx s5:%lx s6:%lx\n", s1, *(int *)s2, *((struct ptr *)s3)->p, s4, *(int *)s5, *((struct ptr *)s6)->p);
}

void dump_9args(int a1, int *a2, struct ptr *p3, int a4, int *a5, struct ptr *p6, int a7, int *a8, struct ptr *p9) {
	// register int64_t rax asm("rax"); return
	register uint64_t rbp asm("rbp"); // mov rbp = rsp
	register uint64_t rsp asm("rsp");
	register uint64_t rdi asm("rdi");
	register uint64_t rsi asm("rsi");
	register uint64_t rdx asm("rdx");
	register uint64_t rcx asm("rcx");
	register uint64_t r8 asm("r8");
	register uint64_t r9 asm("r9");
	uint64_t bp = rbp, sp = rsp, s1 = rdi, s2 = rsi, s3 = rdx, s4 = rcx, s5 = r8, s6 = r9;
	// args(s9, s8, s7) rbp rsp(mov rsp, rbp), s7-s8均为栈变量
	uint64_t s7 = *(uintptr_t *)(bp + 16), s8 = *(uintptr_t *)(bp + 24), s9 = *(uintptr_t *)(bp + 32);
	// bp ->  -0x58(%rbp),%rax -> %rsi
	// sp ->  -0x50(%rbp),%rdx 
	printf("bp: %lx sp: %lx s7: %lx\n", bp, sp, sp - 8);
	printf("Register: rdi:%lx rsi:%lx rdx:%lx rcx:%lx r8:%lx r9:%lx\n", s1, s2, s3, s4, s5, s6);
	printf("Argument: s1:%lx s2:%lx s3:%lx s4:%lx s5:%lx s6:%lx s7:%lx s8:%lx s9:%lx\n", s1, *(int *)s2, *((struct ptr *)s3)->p, s4, *(int *)s5, *((struct ptr *)s6)->p, s7, *(int*)s8, *((struct ptr *)s9)->p);
}

void dump_N_args(int N, int a1, struct ptr *p2, int *a3, int a4, struct ptr *p5, int *a6, int a7, struct ptr *p8, int *a9, int a10, struct ptr *p11) {
	// register int64_t rax asm("rax"); return
	register uint64_t rdi asm("rdi");
	register uint64_t rsi asm("rsi");
	register uint64_t rdx asm("rdx");
	register uint64_t rcx asm("rcx");
	register uint64_t r8 asm("r8");
	register uint64_t r9 asm("r9");
	uint64_t s1 = rdi, s2 = rsi, s3 = rdx, s4 = rcx, s5 = r8, s6 = r9;
	printf("Register: rdi:%lx rsi:%lx rdx:%lx rcx:%lx r8:%lx r9:%lx\n", s1, s2, s3, s4, s5, s6);
	printf("Argument: s1:%lx s2:%lx s3:%lx s4:%lx s5:%lx s6:%lx\n", s1, *(int *)s2, s3, *(int *)s4, s5, *(int *)s6);
	int v = *(int *)s2;
	// rsi会变化
	assert(s2 == (uint64_t) p2);
	printf("(s2:%lx %s rsi:%lx) v=%d p2:%lx p2=%d\n", s2, s2 == rsi ? "==" : "!=", rsi, v, p2, *(int *)p2);
}

int test_normal_3args(int a1, int *a2, struct ptr *p3) {
	TEST_DEL("test_normal_3args");
	// 8 30
	printf("A1->0x%lx A2->0x%lx A3->0x%lx d12:%ld d23:%ld\n", (uintptr_t)&a1, (uintptr_t)a2, (uintptr_t)p3, (uintptr_t)a2 - (uintptr_t)(&a1), (uintptr_t)p3 - (uintptr_t)a2);
	// uintpr arg2 = 
	printf("A1=%d A2=%d A3=%d\n", a1, *a2, *p3->p);
}

int test_normal_4args(int a1, int *a2, int a3, int *a4) {
	TEST_DEL("test_normal_4args");
	BPF_CALL4 func4 = dump_4args;
	func4(a1, a2, a3, a4);

	BPF_CALL5 func5 = dump_4args;
	func5(a1, a2, a3, a4, a1);
}

int test_normal_5args() {
}

int test_normal_6args(int a1, int *a2, struct ptr *p3, int a4, int *a5, struct ptr *p6) {
	TEST_DEL("test_normal_6args");
	dump_6args(a1, a2, p3, a4, a5, p6);
	BPF_CALL6 func6 = dump_6args;
	func6(a1, a2, p3, a4, a5, p6);
	BPF_CALL7 func7 = dump_6args;
	func7(a1, a2, p3, a4, a5, p6, a1);
	BPF_CALL8 func8 = dump_6args;
	func8(a1, a2, p3, a4, a5, p6, a1, a2);
}

// obtain extra arguments from stack
int test_normal_8args() {
	
}

int test_normal_9args(int a1, int *a2, struct ptr *p3, int a4, int *a5, struct ptr *p6, int a7, int *a8, struct ptr *p9) {
	TEST_DEL("test_normal_9args");
	dump_9args(a1, a2, p3, a4, a5, p6, a7, a8, p9);
}

int test_normal_12args() {
	
}

void test_normal_args() {
	int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9;
	struct ptr p1 = {&a1}, p2 = {&a2}, p3 = {&a3}, p4 = {&a4}, p5 = {&a5}, p6 = {&a6}, p7 = {&a7}, p8 = {&a8}, p9 = {&a9};

	test_normal_3args(a1, &a2, &p3);
	test_normal_4args(a1, &a2, a3, &a4);
	test_normal_6args(a1, &a2, &p3, a4, &a5, &p6);

	// test_normal_9args(a1, &a2, &p3, a4, &a5, &p6, a7, &a8, &p9);
}


/* 3. 复杂参数的传递
	func(struct st s); // 复制struct
*/
struct small { char a1, a2; };
struct medium { long a1, a2; };
struct large { long a, b, c, d, e, f, g; };
void standard_args(int n, ...) {
	//BPF_CALL2 func = (BPF_CALL2) test_3args;
	//func(n, &n);
}

void test_complex_args() {

}

int main() {
	printf("test variable number args\n");
	// test_args(1, 1);
	// test_variable_args();
	test_normal_args();
	// test_complex_args();
	return 0;
}
