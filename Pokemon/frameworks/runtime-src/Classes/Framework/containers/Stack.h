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
	
class Stack
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

/*
// definitions
template <typename T>
Stack<T>::Stack()
	: _container(new std::stack<T>())
{
	static_assert(std::is_convertible<T, Ref*>::value, "T should be Ref*");
}

template <typename T>
Stack<T>::~Stack()
{
	if (this->_container)
	{
		while (!this->isEmpty())
		{
			this->pop();
		}
		delete this->_container;
	}
}

template <typename T>
void Stack<T>::push(T pObj)
{
	this->_container->push(pObj);
	pObj->retain();
}

template <typename T>
void Stack<T>::pop()
{
	auto pObj = this->top();
	this->_container->pop();
	pObj->release();
}

template <typename T>
T Stack<T>::top()
{
	return this->_container->top();
}

template <typename T>
void Stack<T>::clear()
{
	while (!this->isEmpty())
	{
		this->pop();
	}
}

template <typename T>
bool Stack<T>::isEmpty()
{
	return this->_container->empty();
}

template <typename T>
int Stack<T>::length()
{
	return this->_container->size();
}
*/

}

#endif