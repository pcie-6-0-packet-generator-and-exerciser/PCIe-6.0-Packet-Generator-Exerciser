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
	std::unique_lock<std::mutex> mlock(mutex_);
	queue_.push(t);
	mlock.unlock();
	condition_.notify_one();
}

template <class T>
void QueueWrapper<T>::push(std::queue<T> q)
{
	std::unique_lock<std::mutex> mlock(mutex_);
	while (!q.empty())
	{
		queue_.push(q.front());
		q.pop();
	}
	mlock.unlock();
	condition_.notify_one();
}

template <class T>
T QueueWrapper<T>::pop()
{
	std::unique_lock<std::mutex> mlock(mutex_);
	while (queue_.empty())
	{
		condition_.wait(mlock);
	}
	auto item = queue_.front();
	queue_.pop();
	return item;
}

template <class T>
std::queue<T> QueueWrapper<T>::popAll()
{
	std::unique_lock<std::mutex> mlock(mutex_);
	std::queue<T> q;
	while (!queue_.empty())
	{
		q.push(queue_.front());
		queue_.pop();
	}
	return q;
}

template <class T>
int QueueWrapper<T>::size()
{
	std::unique_lock<std::mutex> mlock(mutex_);
	return queue_.size();
}
