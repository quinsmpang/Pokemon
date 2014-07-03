/******************************
Description: Use RefString instead of __Bool
Author: M.Wan
Date: 6/29/2014
******************************/

#ifndef __BASE_REFBOOLEAN__
#define __BASE_REFBOOLEAN__

#include "cocos2d.h"

namespace framework
{
	class RefBoolean : public cocos2d::Ref
	{
	public:
		static RefBoolean *create(bool value);

		explicit RefBoolean(bool value);
		bool getBoolean() const;

	private:
		bool _value;
	};
}

#endif