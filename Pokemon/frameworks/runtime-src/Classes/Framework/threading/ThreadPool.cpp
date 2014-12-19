#include "ThreadPool.h"

namespace framework
{
	// Thread pool func
	void poolThreadFunc()
	{

	}

	ThreadPool::ThreadPool(unsigned int capacity)
		: _capacity(capacity)
		, _running(false)
		, _taskQueue()
		, _runningQueue()
		, _m()
		, _notEmpty()
		, _notFull()
	{
	}

	ThreadPool::~ThreadPool()
	{
	}

	void ThreadPool::run()
	{
		CCASSERT(!_running, "Already running");
		_running = true;
		Thread *pTh = nullptr;
		for (size_t i = 0; i < _capacity; i++)
		{
			pTh = new Thread();
			_runningQueue.push_back(pTh);
			pTh->run(std::bind(&ThreadPool::threadFunc, this));
		}
	}

	void ThreadPool::stop()
	{
	}

	bool ThreadPool::isFull() const
	{
		return _runningQueue.size() >= _capacity;
	}

	void ThreadPool::threadFunc()
	{
		while (_running)
		{

		}
	}
}