#include "thread_pool.h"

thread_pool::thread_pool(int cores)
{
	for (int i = 0; i < cores; ++i)
	{
		vecThread.push_back(std::thread(&thread_pool::work, this));
	}
}

void thread_pool::submit(std::vector<std::function<void()>> vFun, int countSubmits)
{
	for (int i = 0; i < countSubmits; ++i)
	{
		for (int j = 0; j < vFun.size(); ++j)
		{
			safe_queue.push(vFun.at(j));
		}
		std::this_thread::sleep_for(1s);
	}
	submitFlag = true;
}

void thread_pool::work()
{
	while (!submitFlag)
	{	
		std::unique_lock<std::mutex> ul(tpm);
		if (!safe_queue.empty())
		{
			std::cout << "work id: " << std::this_thread::get_id() << std::endl;
			safe_queue.front();
			safe_queue.pop();
		}
		else
		{
			std::this_thread::yield();
		}
		ul.unlock();
	}
}

void thread_pool::doJoin()
{
	for (auto& el : vecThread)
	{
		el.join();
	}
}
