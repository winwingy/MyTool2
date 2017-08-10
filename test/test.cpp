// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <functional>
#include <tchar.h>
#include <string>

#ifdef UNICODE
#define tString 
#endif

void foo(int& a) {
	++a;
}

void test_function(std::function<void(void)> fun) {
	fun();
}

int main() {
	int a = 1;

	std::cout << "a = " << a << "\n";
	std::function<void (void)> FooFun1 = std::bind(foo, a);
	FooFun1();
	std::cout << "a = " << a << "\n";
	test_function(std::bind(foo, a));
	std::cout << "a = " << a << "\n";
	test_function(std::bind(foo, std::ref(a)));
	std::cout << "a = " << a << "\n";

	system("pause");
	return 0;
}
