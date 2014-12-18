#include "Thread.h"
#include "CCLuaEngine.h"
#include <chrono>

using namespace std;
using namespace cocos2d;

namespace framework
{
	Thread::Thread()
		: _hThread()
		, _running(false)
	{
	}

	Thread::~Thread()
	{
	}

	bool Thread::join()
	{
		CCASSERT(_running, "The thread should be running");
		if (_hThread.joinable())
		{
			_hThread.join();
			return true;
		}
		return false;
	}

	void Thread::detach()
	{
		CCASSERT(_running, "The thread should be running");
		_hThread.detach();
	}

	void Thread::sleep(unsigned int ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}
}