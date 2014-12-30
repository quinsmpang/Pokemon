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
	/**
     * Base Ref integer object.
     */
	class RefInteger : public cocos2d::Ref
	{
	public:
		/**
         * Create RefInteger object.
         *
         * @param value Integer value.
         *
         * @return Return RefInteger instance, or return nullptr when encounter an error.
         */
		static RefInteger *create(int number = 0);
        
		/**
         * RefInteger constructor
         */
		explicit RefInteger(int number);
		/**
         * Get stored integer value.
         *
         * @return Return stored integer value.
         */
		int getNumber() const;

	private:
		int _num;
	};
}

#endif