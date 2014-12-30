#include "RefBoolean.h"
#include <new>

using namespace cocos2d;

namespace framework
{
	RefBoolean *RefBoolean::create(bool value)
	{
		auto pBool = new (std::nothrow) RefBoolean(value);
		if (pBool) 
		{
			pBool->autorelease();
		}

		return pBool;
	}

	RefBoolean::RefBoolean(bool value)
		: _value(value)
	{
	}

	bool RefBoolean::getBoolean() const
	{
		return this->_value;
	}
}