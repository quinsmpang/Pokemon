/******************************
Description: Recursive mutex, which supports multiple locks.
Author: M.Wan
Date: 12/10/2014
******************************/

#ifndef __THREAD_MUTEX__
#define __THREAD_MUTEX__

#include "cocos2d.h"
#include "../base/Uncopyable.h"
#include "../base/Uninheritable.h"
#include <mutex>

namespace framework
{
	class Mutex : public cocos2d::Ref, public Uninheritable<Mutex>, private Uncopyable
	{
	public:
		static Mutex *create();

		explicit Mutex();

		void lock();
		void unlock();

	private:
		std::recursive_mutex _mutex;
	};
}

#endif