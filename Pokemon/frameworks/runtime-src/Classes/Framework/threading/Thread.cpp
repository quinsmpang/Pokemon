#include "Thread.h"
#include "CCLuaEngine.h"
#include <mutex>

using namespace std;
using namespace cocos2d;

namespace framework
{
	Thread::Thread()
		: _hThread()
		, _running(false)
#if CC_ENABLE_SCRIPT_BINDING
		, _L(nullptr)
		, _attached(false)
#endif
	{
	}

	void Thread::run(const function<void()> &threadFunc)
	{
		CCASSERT(!_running, "The thread should not be running");
		_running = true;
		_hThread = thread(threadFunc);
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

#if CC_ENABLE_SCRIPT_BINDING
	void Thread::attachLuaState(lua_State *L)
	{
		if (_attached)
		{
			return;
		}
		_L = L;
		_attached = true;
	}
#endif
}