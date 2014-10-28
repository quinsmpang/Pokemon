/******************************
Description: Win32 keyboard event listener
Author: M.Wan
Date: 10/28/2014
******************************/

#ifndef __WIN32_WIN32EVENTLISTENERKEYBOARD__
#define __WIN32_WIN32EVENTLISTENERKEYBOARD__

#include "Win32EventListener.h"

namespace framework
{
	class GameLayer;

	class Win32EventListenerKeyboard : public Win32EventListener
	{
	public:
		static const WIN32_LISTENER_ID LISTENER_ID;

		static Win32EventListenerKeyboard *createWithTarget(cocos2d::Node *target);

		// for scripting
		void registerScriptWin32Handler(int handler, int type);
		void unregisterScriptWin32Handler(int type);

		std::function<void(int)> onWin32KeyDown;
		std::function<void(int)> onWin32KeyUp;

	protected:
		bool initWithTarget(cocos2d::Node *target);

		// script support
		int _keyDownScriptHandler;
		int _keyUpScriptHandler;
	};
}

#endif