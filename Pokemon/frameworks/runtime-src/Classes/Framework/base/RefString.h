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
	/**
     * Base Ref string object.
     */
	class RefString : public cocos2d::Ref
	{
	public:
		/**
         * Create RefString object.
         *
         * @param value String value.
         *
         * @return Return RefString instance, or return nullptr when encounter an error.
         */
		static RefString *create(const std::string &str);
        
		/**
         * RefString constructor
         */
		explicit RefString(const std::string &str);
		/**
         * Get stored string.
         *
         * @return Return stored string.
         */
		const char *getCString() const;

	private:
		std::string _str;
	};
}

#endif