#include "Vector.h"
#include "../base/RefString.h"
#include "../base/RefInteger.h"
#include "../base/RefDouble.h"
#include "../base/RefBoolean.h"

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
		this->clear();
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
    
    void Vector::addBoolean(const bool &value)
    {
        auto refBool = RefBoolean::create(value);
        refBool->retain();
        this->_container->push_back(refBool);
    }

	void Vector::addString(const string &str)
	{
		auto refStr = RefString::create(str.c_str());
		refStr->retain();
		this->_container->push_back(refStr);
	}

	void Vector::addInteger(const int &num)
	{
		auto refNum = RefInteger::create(num);
		refNum->retain();
		this->_container->push_back(refNum);
	}

	void Vector::addDouble(const float &num)
	{
		auto refNum = RefDouble::create(num);
		refNum->retain();
		this->_container->push_back(refNum);
	}

	void Vector::addObject(Ref *obj)
	{
		obj->retain();
		this->_container->push_back(obj);
	}

	void Vector::removeObject(Ref *obj)
	{
		for (auto iter = this->_container->cbegin(); iter != this->_container->cend(); ++iter)
		{
			if (*iter == obj)
			{
				obj->release();
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
		(*iter)->release();
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

		this->_container->at(index)->release();
		obj->retain();
		this->_container->at(index) = obj;
	}

	void Vector::clear()
	{
		for (auto iter = this->_container->cbegin(); iter != this->_container->cend(); ++iter)
		{
			(*iter)->release();
		}
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