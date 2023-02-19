#pragma once
#include <queue>
#include <mutex>

// class QueueWrapper that wraps a queue and implements producer consumer model
class QueueWrapper
{
	//queue
	std::queue<TLP> queue;

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
		void push(TLP tlp);

		//pops a TLP from the queue
		TLP pop();

		//returns the size of the queue
		int size();
};