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
		QueueWrapper()
		{
		}

		~QueueWrapper()
		{
		}

		void push(T t)
		{
			std::unique_lock<std::mutex> mlock(mutex_);
			queue_.push(t);
			mlock.unlock();
			condition_.notify_one();
		}

		void push(std::queue<T> q)
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

		T pop()
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

		std::queue<T> popAll()
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

		int size()
		{
			std::unique_lock<std::mutex> mlock(mutex_);
			return queue_.size();
		}
};
