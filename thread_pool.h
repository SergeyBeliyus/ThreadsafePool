#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include "safe_queue.h"

using namespace std::chrono_literals;

class thread_pool
{
public:
	thread_pool(int cores);
	void work();
	void doJoin();
	void submit(std::vector<std::function<void()>> fun, int countSubmits);
private:
	std::mutex tpm;
	std::vector<std::thread> vecThread;
	safe_queue<std::function<void()>> safe_queue;
	bool submitFlag = false;
};