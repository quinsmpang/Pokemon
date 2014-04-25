/******************************
Description: Data structure: Queue
Author: M.Wan
Date: 4/16/2014
******************************/

#ifndef __CONTAINERS_QUEUE__
#define __CONTAINERS_QUEUE__

#include <queue>
#include "cocos2d.h"

namespace framework
{

	class Queue : public cocos2d::Ref
	{
	public:
		explicit Queue();
		~Queue();
		void enqueue(cocos2d::Ref *pObj);
		void dequeue();
		cocos2d::Ref *front();
		void clear();
		bool isEmpty();
		int getLength();
	private:
		std::queue<cocos2d::Ref*> *_container;
	};

}

#endif