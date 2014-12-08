#include "Thread.h"

using namespace std;

Thread::Thread()
: _thread()
, _running(false)
{
}

Thread::~Thread()
{
}

void Thread::start(const std::function<void()> &threadFunc)
{
	CCASSERT(!_running, "The thread is already started, you can't start again, please create another thread to run your task.");

	_running = true;
	_thread = thread(threadFunc);
}

bool Thread::join()
{
	if (_thread.joinable()) {
		_thread.join();
		return true;
	}
	return false;
}

void Thread::detach()
{
	_thread.detach();
}