#include "Queue.h"

using namespace cocos2d;

namespace framework
{

Queue::Queue()
	: _container(new std::queue<Ref*>())
{
}

Queue::~Queue()
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

void Queue::enqueue(Ref *pObj)
{
	this->_container->push(pObj);
	pObj->retain();
}

void Queue::dequeue()
{
	auto pObj = this->_container->front();
	this->_container->pop();
	pObj->release();
}

Ref *Queue::front()
{
	return this->_container->front();
}

void Queue::clear()
{
	while (!this->_container->empty())
	{
		this->dequeue();
	}
}

bool Queue::isEmpty()
{
	return this->_container->empty();
}

int Queue::getLength()
{
	return this->_container->size();
}

}