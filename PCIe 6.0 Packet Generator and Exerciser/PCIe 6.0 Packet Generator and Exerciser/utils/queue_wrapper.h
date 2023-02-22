#pragma once
#include <queue>
#include <mutex>

/**
 * @brief This class implements a thread-safe queue
 * @tparam T The datatype for the queue contents
*/
template <class T>
class QueueWrapper
{
	std::queue<T> queue_;

	std::mutex mutex_;

	std::condition_variable condition_;

	public:
		QueueWrapper();

		~QueueWrapper();

		void push(T t);

		T pop();

		int size();
};
