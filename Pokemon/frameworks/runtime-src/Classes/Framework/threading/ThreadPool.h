/******************************
Description: Thread pool for managing threads
Author: M.Wan
Date: 12/18/2014
******************************/

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "base/CCRef.h"
#include "../base/Uninheritable.h"
#include "../base/Uncopyable.h"
#include "Thread.h"
#include "Mutex.h"

namespace framework
{
	class Queue;

	class ThreadPool : public cocos2d::Ref, public Uninheritable<ThreadPool>, private Uncopyable
	{
	public:
		explicit ThreadPool(unsigned int capcity = 128);
		virtual ~ThreadPool();

		// run new task managed by the pool.
		template<typename ThreadFunc>
		void queueWorkItem(const ThreadFunc &threadFunc);
		template<typename ThreadFunc, typename ...Args>
		void queueWorkItem(const ThreadFunc &threadFunc, Args... args);

	private:
		unsigned int _capacity;		// the max concurrent threads count

		Queue *_taskQueue;		// task container
	};
}

#endif