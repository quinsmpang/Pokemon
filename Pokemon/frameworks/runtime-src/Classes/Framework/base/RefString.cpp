#include "RefString.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace framework
{
	RefString *RefString::create(const std::string &str)
	{
		auto pStr = new (nothrow) RefString(str);
        if (pStr) {
            pStr->autorelease();
        }
            
		return pStr;
	}

	RefString::RefString(const std::string &str)
		: _str(str)
	{
	}

	const char *RefString::getCString() const
	{
		return _str.c_str();
	}
}