/******************************
Description: Thread class, multi-thread
Author: M.Wan
Date: 12/7/2014
******************************/

#ifndef __THREAD_THREAD__
#define __THREAD_THREAD__

#include "cocos2d.h"
#include "../base/Uncopyable.h"
#include "../base/Uninheritable.h"
#include <thread>
#include <functional>

namespace framework
{
	class Thread : public cocos2d::Ref, public Uninheritable<Thread>, private Uncopyable
	{
	public:
		static Thread *create();

		explicit Thread();
		virtual ~Thread();

		void start(const std::function<void()> &threadFunc);
		bool join();		// Equal to the WaitForSingleObject in win32.
		void detach();	// detach the thread, then the main thread will lose the control to this thread, the thread will be disposed when running over.

	protected:
		std::thread _thread;
		bool _running;
	};
}

#endif