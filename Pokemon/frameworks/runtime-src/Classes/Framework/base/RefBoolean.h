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
	/**
	* Base Ref boolean object.
	*/
	class RefBoolean : public cocos2d::Ref
	{
	public:
		/**
		* Create RefBoolean object.
		*
		* @param value Boolean data.
		*
		* @return Return RefBoolean instance, or return nullptr when encounter an error.
		*/
		static RefBoolean *create(bool value);

		/**
		* RefBoolean constructor
		*/
		explicit RefBoolean(bool value);
		/**
		* Get stored boolean value.
		*
		* @return Return stored boolean value.
		*/
		bool getBoolean() const;

	private:
		bool _value;
	};
}

#endif