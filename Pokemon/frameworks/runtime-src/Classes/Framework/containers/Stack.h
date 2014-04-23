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
	explicit Stack();
	~Stack();
	void push(cocos2d::Ref *pObj);
	void pop();
	cocos2d::Ref *top();
	void clear();
	bool isEmpty();
	int getLength();
private:
	std::stack<cocos2d::Ref*> *_container;
};

}

#endif