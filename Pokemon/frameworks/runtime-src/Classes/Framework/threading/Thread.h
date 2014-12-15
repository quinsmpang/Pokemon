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

		void run(const std::function<void()> &threadFunc);

		bool join();
		void detach();		// detach thread, then the main thread will lose the control of this thread.

#if CC_ENABLE_SCRIPT_BINDING
	public:
		// don't call this method by yourself
		void attachLuaState(lua_State *L);
		inline lua_State *getAttachedLuaState() const
		{
			return _L;
		}
	private:
		lua_State *_L;
		bool _attached;
#endif

	private:
		std::thread _hThread;
		bool _running;
	};
}

#endif