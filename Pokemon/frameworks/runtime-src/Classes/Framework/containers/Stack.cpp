#include "Stack.h"

using namespace cocos2d;

namespace framework
{

	Stack::Stack()
		: _container(new std::stack<Ref*>())
	{
	}

	Stack::~Stack()
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

	void Stack::push(Ref *pObj)
	{
		this->_container->push(pObj);
		pObj->retain();
	}

	void Stack::pop()
	{
		auto pObj = this->top();
		this->_container->pop();
		pObj->release();
	}

	Ref *Stack::top()
	{
		return this->_container->top();
	}

	void Stack::clear()
	{
		while (!this->isEmpty())
		{
			this->pop();
		}
	}

	bool Stack::isEmpty()
	{
		return this->_container->empty();
	}

	int Stack::getLength()
	{
		return this->_container->size();
	}

}