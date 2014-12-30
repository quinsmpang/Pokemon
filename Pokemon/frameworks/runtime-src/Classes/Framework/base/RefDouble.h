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
	/**
     * Base Ref double object.
     */
	class RefDouble : public cocos2d::Ref
	{
	public:
		/**
         * Create RefDouble object.
         *
         * @param value Double value.
         *
         * @return Return RefDouble instance, or return nullptr when encounter an error.
         */
		static RefDouble *create(double number);
        
		/**
         * RefDouble constructor
         */
		explicit RefDouble(double number);
		/**
         * Get stored double value.
         *
         * @return Return stored double value.
         */
		double getNumber() const;

	private:
		double _num;
	};
}

#endif