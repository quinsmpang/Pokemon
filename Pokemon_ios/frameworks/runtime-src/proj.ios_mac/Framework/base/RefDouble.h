/******************************
Description: Use RefDouble instead of __Float and __Double
Author: M.Wan
Date: 6/4/2014
******************************/

#ifndef __BASE_REFDOUBLE__
#define __BASE_REFDOUBLE__

#include "cocos2d.h"

namespace framework
{
	class RefDouble : public cocos2d::Ref
	{
	public:
		static RefDouble *create(double number);

		explicit RefDouble(double number);
		double getNumber() const;

	private:
		double _num;
	};
}

#endif