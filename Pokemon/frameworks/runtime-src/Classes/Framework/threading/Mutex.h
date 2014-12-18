/******************************
Description: Mutex in threading
Author: M.Wan
Date: 12/18/2014
******************************/

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "base/CCRef.h"
#include "../base/Uninheritable.h"
#include "../base/Uncopyable.h"
#include <mutex>

namespace framework
{
	class Mutex : public cocos2d::Ref, public Uninheritable<Mutex>, private Uncopyable
	{
	public:
		explicit Mutex();
		~Mutex();

		void lock();
		void unlock();

	private:
		std::mutex _lock;
	};

	class RecursiveMutex : public cocos2d::Ref, public Uninheritable<RecursiveMutex>, private Uncopyable
	{
	public:
		explicit RecursiveMutex();
		~RecursiveMutex();

		void lock();
		void unlock();

	private:
		std::recursive_mutex _lock;
	};
}

#endif