#include "../hooker/HookerFactory.h"
#include <iostream>
#include <cstring>
#include <future>
#include <cstdio>
#include <random>
#include <memory>

void print(const char *s) {
    std::cout << s << std::endl;
}

//用自己实现的函数替换strcmp进行测试，目前没有成功，不知道该程序对被hook函数是否有要求
/*
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

int (*original_func)(int);
*/


int (*old_strcmp)(const char *, const char *);

int my_strcmp(const char *s1, const char *s2) {
    std::cout << s1 << " " << s2 << ",haha, it's been hooked" << std::endl;

	//if (old_strcmp) {
	//	std::cout << "old result is: " << old_strcmp(s1, s2) << std::endl;
	//}
	/*
	 * 此处3行，若进行注释，则可以在Ubuntu21运行，但仍无法在Ubuntu18运行；不注释，则两种环境均无法运行
	 * Ubuntu18环境：g++ 7.5.0、ninja 1.8.2、cmake 3.21.4、make 4.1
	 * Ubuntu21环境：g++ 11.2.0、ninja 1.10.1、cmake 3.18.4、make 4.3
	 */
    return 0;
}

int main() {
    const char *s1 = "hello";
    const char *s2 = "world";

    using namespace hooker;
    std::unique_ptr<HookerFactory> factory = HookerFactory::getInstance();
    const Hooker& hooker = factory->getHooker();
    hooker.hook(reinterpret_cast<void*>(strcmp), reinterpret_cast<void*>(my_strcmp), reinterpret_cast<void**>(&old_strcmp));

    if (strcmp(s1,s2) == 0) {
        print("equal");
    } else {
        print("not equal");
    }

    hooker.unhook(reinterpret_cast<void*>(strcmp), reinterpret_cast<void*>(old_strcmp));

    if (strcmp(s1,s2) == 0) {
        print("equal");
    } else {
        print("not equal");
    }

    return 0;
}
