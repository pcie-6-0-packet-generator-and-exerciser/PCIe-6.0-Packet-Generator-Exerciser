#include "queue_wrapper.h"

template <class T>
QueueWrapper<T>::QueueWrapper()
{
}

template <class T>
QueueWrapper<T>::~QueueWrapper()
{
}

template <class T>
void QueueWrapper<T>::push(T t)
{
	std::unique_lock<std::mutex> mlock(mutex);
	queue.push(t);
	mlock.unlock();
	condition.notify_one();
}

template <class T>
T QueueWrapper<T>::pop()
{
	std::unique_lock<std::mutex> mlock(mutex);
	while (queue.empty())
	{
		condition.wait(mlock);
	}
	auto item = queue.front();
	queue.pop();
	return item;
}

template <class T>
int QueueWrapper<T>::size()
{
	std::unique_lock<std::mutex> mlock(mutex);
	return queue.size();
}
