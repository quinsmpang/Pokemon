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
        /**
         * Create queue structure.
         *
         * @return Return Queue instance, or return nullptr when encounter an error.
         */
		static Queue *create();

        /**
         * Queue constructor.
         */
		explicit Queue();
        /**
         * Queue destructor.
         */
		~Queue();
        /**
         * Add Ref object to the queue.
         *
         * @param pObj The cocos2dx object.
         */
		void enqueue(cocos2d::Ref *pObj);
        /**
         * Remove the head of the queue.
         */
		void dequeue();
        /**
         * Get the head object of the queue.
         *
         * @return Return the head of the queue, or nullptr if the queue is empty.
         */
		cocos2d::Ref *front();
        /**
         * Clear all items of the queue.
         */
		void clear();
        /**
         * Check whether the queue is empty.
         *
         * @return Return boolean.
         */
		bool isEmpty();
        /**
         * Return the size of the queue.
         */
		int getLength();
	private:
		std::queue<cocos2d::Ref*> *_container;
	};

}

#endif