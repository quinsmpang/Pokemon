#include "Thread.h"
#include "CCLuaEngine.h"
#include <mutex>

using namespace std;
using namespace cocos2d;

namespace framework
{
	Thread::Thread()
		: _hThread()
	{
	}

	void Thread::run(const function<void()> &threadFunc)
	{
		_hThread = thread(threadFunc);
	}

	bool Thread::join()
	{
		if (_hThread.joinable())
		{
			_hThread.join();
			return true;
		}
		return false;
	}

	void Thread::detach()
	{
		_hThread.detach();
	}
}