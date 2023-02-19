#include "queue_wrapper.h"

//constructor
QueueWrapper::QueueWrapper()
{
}

//destructor
QueueWrapper::~QueueWrapper()
{
}

//pushes a TLP to the queue
void QueueWrapper::push(TLP tlp)
{
	std::unique_lock<std::mutex> mlock(mutex);
	queue.push(tlp);
	mlock.unlock();
	condition.notify_one();
}

//pops a TLP from the queue
TLP QueueWrapper::pop()
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

//returns the size of the queue
int QueueWrapper::size()
{
	std::unique_lock<std::mutex> mlock(mutex);
	return queue.size();
}
