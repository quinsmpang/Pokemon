/******************************
Description: Helper class on win32 keyboard events
Author: M.Wan
Date: 7/1/2014
******************************/

#ifndef __UTILS_KEYBOARDHELPER__
#define __UTILS_KEYBOARDHELPER__

#include "cocos2d.h"

namespace framework
{
	class KeyboardHelper : public cocos2d::Ref
	{
	public:
		static KeyboardHelper *getInstance();

		bool isKeyPressed(int keyCode);
		bool isKeyReleased(int keyCode);

	private:
		KeyboardHelper();

		static KeyboardHelper *_instance;
	};
}

#endif