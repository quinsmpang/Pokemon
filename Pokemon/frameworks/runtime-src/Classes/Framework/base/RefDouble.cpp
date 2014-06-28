#include "RefDouble.h"

using namespace cocos2d;

namespace framework
{
	RefDouble *RefDouble::create(double number)
	{
		auto pNum = new RefDouble(number);
		pNum->autorelease();

		return pNum;
	}

	RefDouble::RefDouble(double number)
		: _num(number)
	{
	}

	double RefDouble::getNumber() const
	{
		return _num;
	}
}