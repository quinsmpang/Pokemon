#include "RefDouble.h"
#include <new>

using namespace cocos2d;

namespace framework
{
	RefDouble *RefDouble::create(double number)
	{
		auto pNum = new (std::nothrow) RefDouble(number);
        if (pNum) {
            pNum->autorelease();
        }

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