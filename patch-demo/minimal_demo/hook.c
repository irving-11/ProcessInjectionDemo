#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>

void buggy_function() { printf("Calling %s\n", __func__); }
void fix_function() { printf("Calling %s\n", __func__); }

struct jmp {
	uint32_t opcode: 8;
	int32_t  offset: 32;
} __attribute__((packed));

#define JMP(off) ((struct jmp) { 0xe9, off - sizeof(struct jmp) })
#define PG_SIZE sysconf(_SC_PAGESIZE)

static inline bool within_page(void *addr) {
	return (uintptr_t)addr % PG_SIZE + sizeof(struct jmp) <= PG_SIZE;
}

/*
*  48 b8 ff ff ff ff ff ff ff ff    movabs $0xffffffffffffffff,%rax
*  ff e0                            jmpq   *%rax
*/
void hook_64(void *old, void *new) {
	#define ROUNDDOWN(ptr) ((void *)(((uintptr_t)ptr) & ~0xfff))
	size_t    pg_size = sysconf(_SC_PAGESIZE);
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

void hook2(void *old, void *new) {
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

/*
TODO，Hook 32
*/
int main() {
	buggy_function();
	hook2(buggy_function, fix_function);
	buggy_function();
	return 0;
}