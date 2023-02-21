#pragma once
#include <queue>
#include <mutex>

// class QueueWrapper that wraps a queue and implements producer consumer model
template <class T>
class QueueWrapper
{
	//queue
	std::queue<T> queue;

	//mutex
	std::mutex mutex;

	//condition variable
	std::condition_variable condition;

	public:
		//constructor
		QueueWrapper();

		//destructor
		~QueueWrapper();

		//pushes a TLP to the queue
		void push(T t);

		//pops a TLP from the queue
		T pop();

		//returns the size of the queue
		int size();
};