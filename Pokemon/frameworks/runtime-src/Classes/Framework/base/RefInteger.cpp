#include "RefInteger.h"
#include <new>

using namespace cocos2d;

namespace framework
{
	RefInteger *RefInteger::create(int number)
	{
		auto pInt = new (std::nothrow) RefInteger(number);
        if (pInt) {
            pInt->autorelease();
        }

		return pInt;
	}

	RefInteger::RefInteger(int number)
		: _num(number)
	{
	}

	int RefInteger::getNumber() const
	{
		return _num;
	}
}