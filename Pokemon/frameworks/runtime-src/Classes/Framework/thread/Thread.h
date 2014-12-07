/******************************
Description: Thread class, multi-thread
Author: M.Wan
Date: 12/7/2014
******************************/

#ifndef __THREAD_THREAD__
#define __THREAD_THREAD__

#include "cocos2d.h"
#include <thread>
#include <functional>

class Thread : public cocos2d::Ref
{
public:
	explicit Thread(const std::function<void()> &threadFunc);
	virtual ~Thread();

	void start();
	void abort();

protected:
	std::thread _thread;
};

#endif