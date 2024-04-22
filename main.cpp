#include <iostream>
#include "safe_queue.h"
#include "thread_pool.h"

void fun1();
void fun2();

void main()
{
	int cores = std::thread::hardware_concurrency();
	std::vector<std::function<void()>> vFun {fun1, fun2};
	int countSubmits = 10;
	thread_pool thread_pool(cores - 2);
	std::thread t1(&thread_pool::submit, &thread_pool, vFun, countSubmits);
	thread_pool.doJoin();
	t1.join();
}

void fun1()
{
	std::cout << "Working " << __FUNCTION__ << std::endl;
}

void fun2()
{
	std::cout << "Working " << __FUNCTION__ << std::endl;
}