#include <stdio.h>
#include <unistd.h>

int vul_func(int v) {
	if (v > 2000) {
		return 1;
	}
	return 0;
}

int fix_func(int v) {
	if (v > 5000) {
		return 1;
	}
	return 0;
}

int main() {
	while(1) {
		printf("ptrace demo! pid: %d\n", getpid());
		printf("vul_func(3000): %d\tfix_func(3000): %d\n", vul_func(3000),fix_func(3000));
        sleep(2);
    }
	return 0;
}
