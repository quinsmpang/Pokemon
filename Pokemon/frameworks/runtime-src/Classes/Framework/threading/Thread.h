/******************************
Description: Add thread lib for lua
Author: M.Wan
Date: 12/16/2014
******************************/

#ifndef __THREAD_H__
#define __THREAD_H__

#include "base/CCRef.h"
#include "../base/Uninheritable.h"
#include "../base/Uncopyable.h"
#include <thread>
#include <functional>
#include <future>
extern "C" {
#include "lua.h"
}

namespace framework
{
	class Thread : public cocos2d::Ref, public Uninheritable<Thread>, private Uncopyable
	{
		friend class ThreadPool;
	public:
		explicit Thread();
		~Thread();

		// run thread without arguments, Thread_Func should be std::function
		template<typename Thread_Func>
		void run(const Thread_Func &threadFunc);
		// run thread with arguments, Thread_Func should be std::function
		template<typename Thread_Func, typename ...Args>
		void run(const Thread_Func &threadFunc, Args... args);
		// run async task with no argument
		template<typename Thread_Func>
		typename std::result_of<Thread_Func()>::type runAsync(const Thread_Func &threadFunc);
		// run async task with arguments
		template<typename Thread_Func, typename ...Args>
		typename std::result_of<Thread_Func(Args...)>::type runAsync(const Thread_Func &threadFunc, Args... args);

		bool join();
		void detach();		// detach thread, then the main thread will lose the control of this thread.

	private:
		std::thread _hThread;
		bool _running;
	};

	/* Template implementation */
	template<typename Thread_Func>
	void Thread::run(const Thread_Func &threadFunc)
	{
		CCASSERT(!_running, "The thread should not be running");
		_running = true;
		_hThread = std::thread(threadFunc);
	}

	template<typename Thread_Func, typename ...Args>
	void Thread::run(const Thread_Func &threadFunc, Args... args)
	{
		CCASSERT(!_running, "The thread should not be running");
		_running = true;
		_hThread = std::thread(threadFunc, args);
	}

	template<typename Thread_Func>
	typename std::result_of<Thread_Func()>::type Thread::runAsync(const Thread_Func &threadFunc)
	{
		CCASSERT(!_running, "The thread should not be running");
		_running = true;
		auto future = std::async(std::launch::async, threadFunc);
		auto returnVal = future.get();
		return returnVal;
	}

	template<typename Thread_Func, typename ...Args>
	typename std::result_of<Thread_Func(Args...)>::type runAsync(const Thread_Func &threadFunc, Args... args)
	{
		CCASSERT(!_running, "The thread should not be running");
		_running = true;
		auto future = std::async(std::launch::async, threadFunc, args);
		auto returnVal = future.get();
		return returnVal;
	}
}

#endif