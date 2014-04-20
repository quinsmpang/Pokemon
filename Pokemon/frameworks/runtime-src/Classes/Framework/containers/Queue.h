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
	
template <typename T>
class Queue
{
public:
	explicit Queue();
	~Queue();
	void enqueue(T pObj);
	T dequeue();
	T front();
	void clear();
	bool isEmpty();
	int length();
private:
	std::queue<T> *_container;
};

// definitions
template <typename T>
Queue<T>::Queue()
	: _container(new std::queue<T>())
{
	static_assert(std::is_convertible<T, Ref*>::value, "T should be Ref*");
}

template <typename T>
Queue<T>::~Queue()
{
	if (this->_container)
	{
		while (!this->isEmpty())
		{
			this->dequeue();
		}
		delete this->_container;
	}
}

template <typename T>
void Queue<T>::enqueue(T pObj)
{
	this->_container->push(pObj);
	pObj->retain();
}

template <typename T>
T Queue<T>::dequeue()
{
	auto pObj = this->_container->front();
	this->_container->pop();
	pObj->release();

	return pObj;
}

template <typename T>
T Queue<T>::front()
{
	return this->_container->front();
}

template <typename T>
void Queue<T>::clear()
{
	while (!this->_container->empty())
	{
		this->dequeue();
	}
}

template <typename T>
bool Queue<T>::isEmpty()
{
	return this->_container->empty();
}

template <typename T>
int Queue<T>::length()
{
	return this->_container->size();
}

}

#endif