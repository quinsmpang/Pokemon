#include "Mutex.h"
#include <new>

using namespace std;

namespace framework
{
	Mutex *Mutex::create()
	{
		auto pMutex = new (nothrow) Mutex();
		if (pMutex)
		{
			return pMutex;
		}
		CC_SAFE_RELEASE(pMutex);
		return nullptr;
	}

	Mutex::Mutex()
		: _mutex()
	{
	}

	void Mutex::lock()
	{
		_mutex.lock();
	}

	void Mutex::unlock()
	{
		_mutex.unlock();
	}
}