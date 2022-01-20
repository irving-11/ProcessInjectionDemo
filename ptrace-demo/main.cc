#include <cstdio>

int vulnerable_func(int v) {
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
	printf("ptrace demo: %d %d\n", vulnerable_func(3000), fix_func(3000));
	return 0;
}