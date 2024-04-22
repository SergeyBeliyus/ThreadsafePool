#pragma once
#include <queue>
#include <mutex>
#include <functional>

template <typename T>
class safe_queue
{
public:
	void push(T fun);
	void pop();
	void front();
	bool empty();

private:
	std::queue<T> work_queue;
	std::mutex sqm;
};

template <typename T>
void safe_queue<T>::push(T fun)
{
	std::unique_lock<std::mutex> ul(sqm);
	work_queue.push(fun);
}

template <typename T>
void safe_queue<T>::pop()
{
	std::unique_lock<std::mutex> ul(sqm);
	work_queue.pop();
}

template <typename T>
void safe_queue<T>::front()
{
	std::unique_lock<std::mutex> ul(sqm);
	work_queue.front()();
}

template <typename T>
bool safe_queue<T>::empty()
{
	std::unique_lock<std::mutex> ul(sqm);
	return work_queue.empty();
}