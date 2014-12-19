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
#include <functional>
#include <queue>
#include <vector>
#include <condition_variable>
#include <mutex>

namespace framework
{
	class ThreadPool : public cocos2d::Ref, public Uninheritable<ThreadPool>, private Uncopyable
	{
	public:
		typedef std::function<void()> Task;

		explicit ThreadPool(unsigned int capacity = 16);
		virtual ~ThreadPool();

		void run();
		void stop();

		inline unsigned int getCapacity() const
		{
			return _capacity;
		}

		// run new task managed by the pool.
		void queueWorkItem(const Task &task);		// use std::bind if you have to pass params to the task

	private:
		unsigned int _capacity;		// the max concurrent threads count
		bool _running;

		std::queue<Task> _taskQueue;		// task container
		std::vector<Thread*> _runningQueue;		// running tasks

		std::mutex _m;
		std::condition_variable _notEmpty;
		std::condition_variable _notFull;

		void threadFunc();
		
		bool isFull() const;
	};
}

#endif