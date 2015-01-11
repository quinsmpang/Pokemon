#include "RegexUtils.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <regex>
#else
#include <regex.h>
#endif

using namespace cocos2d;
using namespace std;

namespace framework
{
	RegexUtils::RegexUtils()
	{
	}

	const char *RegexUtils::match(const std::string &content, const std::string &regex)
	{

	}
}