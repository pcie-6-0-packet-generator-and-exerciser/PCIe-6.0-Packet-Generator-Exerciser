#include "queue_wrapper.h"

template <class T>
//constructor
QueueWrapper<T>::QueueWrapper()
{
}

template <class T>
//destructor
QueueWrapper<T>::~QueueWrapper()
{
}

template <class T>
//pushes a TLP to the queue
void QueueWrapper<T>::push(T t)
{
	std::unique_lock<std::mutex> mlock(mutex);
	queue.push(t);
	mlock.unlock();
	condition.notify_one();
}

template <class T>
//pops a TLP from the queue
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
//returns the size of the queue
int QueueWrapper<T>::size()
{
	std::unique_lock<std::mutex> mlock(mutex);
	return queue.size();
}
