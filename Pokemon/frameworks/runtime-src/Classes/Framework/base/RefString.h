/******************************
Description: Use RefString instead of __String
Author: M.Wan
Date: 6/4/2014
******************************/

#ifndef __BASE_REFSTRING__
#define __BASE_REFSTRING__

#include "cocos2d.h"
#include <string>

namespace framework
{
	class RefString : public cocos2d::Ref
	{
	public:
		static RefString *create(const std::string &str);

		explicit RefString(const std::string &str);
		const char *getCString();

	private:
		std::string _str;
	};
}

#endif