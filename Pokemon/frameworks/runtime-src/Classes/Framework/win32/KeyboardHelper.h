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
        /**
         * KeyboardHelper is a singleton.
         */
		SINGLETON(KeyboardHelper);
	public:
        /**
         * Open the keyboard hook.
         *
         * @return Operation result.
         */
		bool hookOn();
        /**
         * Close the keyboard hook.
         *
         * @return Operation result.
         */
		bool hookOff();
        /**
         * Check whether the win32 key is pressed.
         *
         * @param keyCode Win32 virtual key code.
         *
         * @return Is pressed.
         */
		bool isKeyPressed(int keyCode);
	};
}

#endif