#include "RefInteger.h"

using namespace cocos2d;

namespace framework
{
	RefInteger *RefInteger::create(int number)
	{
		auto pInt = new RefInteger(number);
		pInt->autorelease();

		return pInt;
	}

	RefInteger::RefInteger(int number)
		: _num(number)
	{
	}

	int RefInteger::getNumber()
	{
		return _num;
	}
}