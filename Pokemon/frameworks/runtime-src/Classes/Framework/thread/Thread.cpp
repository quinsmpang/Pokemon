#include "Thread.h"
#include <new>

using namespace std;

namespace framework
{
	Thread *Thread::create()
	{
		auto pThread = new (nothrow) Thread();
		if (pThread)
		{
			// no autorelease here, do the release operation when neccessary.
			return pThread;
		}
		CC_SAFE_RELEASE(pThread);
		return nullptr;
	}

	Thread::Thread()
		: _thread()
		, _running(false)
	{
	}

	Thread::~Thread()
	{
		this->detach();
	}

	void Thread::start(const std::function<void()> &threadFunc)
	{
		CCASSERT(!_running, "The thread is already started, you can't start again, please create another thread to run your task.");

		_running = true;
		_thread = thread(threadFunc);
	}

	bool Thread::join()
	{
		if (_thread.joinable())
		{
			_thread.join();
			return true;
		}
		return false;
	}

	void Thread::detach()
	{
		_thread.detach();
	}
}