#include "Thread.h"

using namespace std;

Thread::Thread(const std::function<void()> &threadFunc)
{
	_thread = thread(threadFunc);
}

Thread::~Thread()
{
	this->abort();
}

void Thread::start()
{
	_thread.join();
}

void Thread::abort()
{
	_thread.detach();
}