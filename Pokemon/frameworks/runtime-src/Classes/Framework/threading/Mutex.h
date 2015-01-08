/******************************
Description: Mutex in threading
Author: M.Wan
Date: 12/18/2014
******************************/

#ifndef __THREADING_MUTEX__
#define __THREADING_MUTEX__

#include "base/CCRef.h"
#include "../base/Uninheritable.h"
#include "../base/Uncopyable.h"
#include <mutex>

namespace framework
{
	class Mutex : public cocos2d::Ref, public Uninheritable<Mutex>, private Uncopyable
	{
	public:
        /**
         * Mutex constructor.
         */
		explicit Mutex();
        /**
         * Mutex destructor.
         */
		~Mutex();

        /**
         * Lock the current environment.
         */
		void lock();
        /**
         * Unock the current environment.
         */
		void unlock();

	private:
		std::mutex _lock;
	};

	class RecursiveMutex : public cocos2d::Ref, public Uninheritable<RecursiveMutex>, private Uncopyable
	{
	public:
        /**
         * RecursiveMutex constructor.
         */
		explicit RecursiveMutex();
        /**
         * RecursiveMutex destructor.
         */
		~RecursiveMutex();

        /**
         * Lock the current environment.
         */
		void lock();
        /**
         * Unlock the current environment.
         */
		void unlock();

	private:
		std::recursive_mutex _lock;
	};
}

#endif