#include "RefBoolean.h"

using namespace cocos2d;

namespace framework
{
	RefBoolean *RefBoolean::create(bool value)
	{
		auto pBool = new RefBoolean(value);
		pBool->autorelease();

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