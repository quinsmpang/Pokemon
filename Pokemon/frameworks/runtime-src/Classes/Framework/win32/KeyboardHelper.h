/******************************
Description: The win32 keyboard functionalities is limited in cocos2d-x, win32 vk_code is not supported. Add this class to add some supports on win32.
Author: M.Wan
Date: 10/28/2014
******************************/

#ifndef __WIN32_KEYBOARDHELPER__
#define __WIN32_KEYBOARDHELPER__

#include "cocos2d.h"
#include "../base/Macros.h"

#define INVALID_HOOK 0

namespace framework
{
	class KeyboardHelper : public cocos2d::Ref
	{
		SINGLETON(KeyboardHelper);
	public:
		bool hookOn();
		bool hookOff();
		bool isKeyPressed(int keyCode);
	};
}

#endif