#include "Mutex.h"

namespace framework
{
	/* Mutex */
	Mutex::Mutex()
		: _lock()
	{
	}

	Mutex::~Mutex()
	{
	}

	void Mutex::lock()
	{
		_lock.lock();
	}

	void Mutex::unlock()
	{
		_lock.unlock();
	}

	/* RecursiveMutex */
	RecursiveMutex::RecursiveMutex()
		: _lock()
	{
	}

	RecursiveMutex::~RecursiveMutex()
	{
	}

	void RecursiveMutex::lock()
	{
		_lock.lock();
	}

	void RecursiveMutex::unlock()
	{
		_lock.unlock();
	}
}
