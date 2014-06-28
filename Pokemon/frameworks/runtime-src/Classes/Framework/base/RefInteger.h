/******************************
Description: Use RefInteger instead of __Integer
Author: M.Wan
Date: 6/4/2014
******************************/

#ifndef __BASE_REFINTEGER__
#define __BASE_REFINTEGER__

#include "cocos2d.h"

namespace framework
{
	class RefInteger : public cocos2d::Ref
	{
	public:
		static RefInteger *create(int number = 0);

		explicit RefInteger(int number);
		int getNumber() const;

	private:
		int _num;
	};
}

#endif