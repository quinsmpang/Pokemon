/******************************
Description: Add thread lib for lua
Author: M.Wan
Date: 12/16/2014
******************************/

#ifndef __THREADING_THREAD__
#define __THREADING_THREAD__

#include "base/CCRef.h"
#include "2d/ccMacros.h"
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

        /**
         * Run thread without arguments, Thread_Func should be std::function.
         *
         * @param threadFunc Thread execution function.
         */
		template<typename Thread_Func>
		void run(const Thread_Func &threadFunc);
        /**
         * Run thread with arguments, Thread_Func should be std::function.
         *
         * @param threadFunc Thread execution function.
         * @param args Varadic parameters of the function.
         */
		template<typename Thread_Func, typename ...Args>
		void run(const Thread_Func &threadFunc, Args... args);
        /**
         * Run an async task with no argument until the target thread runs over.
         *
         * @param threadFunc Thread execution function.
         */
		template<typename Thread_Func>
		typename std::result_of<Thread_Func()>::type runAsync(const Thread_Func &threadFunc);
		/**
         * Run an async task with arguments until the target thread runs over.
         *
         * @param threadFunc Thread execution function.
         * @param args Varadic parameters of the function.
         */
		template<typename Thread_Func, typename ...Args>
		typename std::result_of<Thread_Func(Args...)>::type runAsync(const Thread_Func &threadFunc, Args... args);

        /**
         * Make current thread sleep for specified miliseconds.
         */
		static void sleep(unsigned int ms);

        /**
         * Wait other threads to run over.
         *
         * @return Join result, when the thread is detached, it can't join.
         */
		bool join();
        /**
         * Detach thread, the main thread will lose the control of this thread.
         */
		void detach();

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
		_hThread = std::thread(threadFunc, std::forward<Args>(args)...);
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
	typename std::result_of<Thread_Func(Args...)>::type Thread::runAsync(const Thread_Func &threadFunc, Args... args)
	{
		CCASSERT(!_running, "The thread should not be running");
		_running = true;
		auto future = std::async(std::launch::async, threadFunc, std::forward<Args>(args)...);
		auto returnVal = future.get();
		return returnVal;
	}
}

#endif