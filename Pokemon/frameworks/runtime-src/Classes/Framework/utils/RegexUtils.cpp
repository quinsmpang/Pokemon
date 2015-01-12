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
        return nullptr;
	}
    
    bool RegexUtils::replaceOnce(const std::string &content, const std::string &regex, const std::string &newStr)
    {
        return false;
    }
    
    int RegexUtils::replaceAll(const std::string &content, const std::string &regex, const std::string &newStr)
    {
        return 0;
    }
    
    int RegexUtils::replaceAll(const std::string &content, const std::string &regex, cocos2d::Ref *target, const std::function<const char*(const char*)> &callback)
    {
        return 0;
    }
}