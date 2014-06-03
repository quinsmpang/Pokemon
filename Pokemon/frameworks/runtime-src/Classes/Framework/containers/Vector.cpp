#include "Vector.h"

using namespace std;
using namespace cocos2d;

namespace framework
{
	Vector::Vector()
		: Ref()
		, _container(new vector<Ref*>())
	{
	}

	Vector::~Vector()
	{
		if (this->_container)
		{
			delete this->_container;
		}
	}

	Vector *Vector::create()
	{
		auto pAry = new Vector();
		if (pAry)
		{
			pAry->autorelease();
			return pAry;
		}
		CC_SAFE_RELEASE_NULL(pAry);
		return nullptr;
	}

	void Vector::addString(const string &str)
	{
		this->_container->push_back(__String::create(str));
	}

	void Vector::addInteger(const int &num)
	{
		this->_container->push_back(__Integer::create(num));
	}

	void Vector::addDouble(const float &num)
	{
		this->_container->push_back(__Double::create(num));
	}

	void Vector::addObject(Ref *obj)
	{
		this->_container->push_back(obj);
	}

	void Vector::removeObject(Ref *obj)
	{
		for (auto iter = this->_container->cbegin(); iter != this->_container->cend(); ++iter)
		{
			if (*iter == obj)
			{
				this->_container->erase(iter);
				break;
			}
		}
	}

	void Vector::removeAt(int index)
	{
		CCASSERT(index >= 0 && index < this->_container->size(), "index is out of bound");

		auto iter = this->_container->cbegin();
		iter += index;
		this->_container->erase(iter);
	}

	Ref *Vector::objectAt(int index)
	{
		CCASSERT(index >= 0 && index < this->_container->size(), "index is out of bound");

		return this->_container->at(index);
	}

	void Vector::setObjectAt(Ref *obj, int index)
	{
		CCASSERT(index >= 0 && index < this->_container->size(), "index is out of bound");

		this->_container->at(index) = obj;
	}

	void Vector::clear()
	{
		this->_container->clear();
	}

	int Vector::getLength()
	{
		return this->_container->size();
	}

	bool Vector::isEmpty()
	{
		return this->_container->empty();
	}
}