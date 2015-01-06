/******************************
Description: Data structure: Stack
Author: M.Wan
Date: 4/16/2014
******************************/

#ifndef __CONTAINERS_STACK__
#define __CONTAINERS_STACK__

#include <stack>
#include "cocos2d.h"

using namespace cocos2d;

namespace framework
{

	class Stack : public cocos2d::Ref
	{
	public:
        /**
         * Create stack structure.
         *
         * @return Return Stack instance, or return nullptr when encounter an error.
         */
		static Stack *create();

        /**
         * Stack constructor.
         */
		explicit Stack();
        /**
         * Stack destructor.
         */
		~Stack();
        /**
         * Push new object to the stack.
         *
         * @param pObj The cocos2dx object you want to push.
         */
		void push(cocos2d::Ref *pObj);
        /**
         * Pop out the top item of the stack.
         */
		void pop();
        /**
         * Get the top item of the stack.
         *
         * @return Return the top item of the stack, or nullptr if the stack is empty
         */
		cocos2d::Ref *top();
        /**
         * Clear all items of the stack.
         */
		void clear();
        /**
         * Check whether the stack is empty.
         *
         * @return Return boolean value.
         */
		bool isEmpty();
        /**
         * Return the size of the stack.
         */
		int getLength();
	private:
		std::stack<cocos2d::Ref*> *_container;
	};

}

#endif