// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <functional>

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

	return 0;
}
