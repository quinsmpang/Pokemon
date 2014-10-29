#include "Win32EventListenerKeyboard.h"
#include "Win32EventArgs.h"
#include "CCLuaEngine.h"
#include <new>

using namespace cocos2d;

namespace framework
{
	const WIN32_LISTENER_ID Win32EventListenerKeyboard::LISTENER_ID = 1;

	Win32EventListenerKeyboard *Win32EventListenerKeyboard::createWithTarget(Node *target)
	{
		auto pListener = new (std::nothrow) Win32EventListenerKeyboard();

		if (pListener && pListener->initWithTarget(target))
		{
			pListener->autorelease();
			return pListener;
		}
		CC_SAFE_RELEASE(pListener);
		return pListener;
	}

	bool Win32EventListenerKeyboard::initWithTarget(Node *target)
	{
		auto callback = [this](Node *sender, Win32EventArgs* args) {
			void *pParams = args->getParams();
			int keyCode = *((int*)pParams);		// The first param is keycode
			int keyState = *((int*)pParams + 1);		// The second param is key state

			if (keyState == 1)
			{
				// key down
				if (this->onWin32KeyDown)
				{
					this->onWin32KeyDown(keyCode);
				}
				// script support
#if CC_ENABLE_SCRIPT_BINDING
				if (_scriptType == kScriptTypeLua && _keyDownScriptHandler > 0)
				{
					tolua_pushnumber(LuaEngine::getInstance()->getLuaStack()->getLuaState(), keyCode);
					LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(_keyDownScriptHandler, 1);
				}
#endif
			}
			else if (keyState == 2)
			{
				// key up
				if (this->onWin32KeyUp)
				{
					this->onWin32KeyUp(keyCode);
				}
				// script support
#if CC_ENABLE_SCRIPT_BINDING
				if (_scriptType == kScriptTypeLua && _keyUpScriptHandler > 0)
				{
					tolua_pushnumber(LuaEngine::getInstance()->getLuaStack()->getLuaState(), keyCode);
					LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(_keyUpScriptHandler, 1);
				}
#endif
			}
		};

		return Win32EventListener::init(Win32EventListenerType::KEYBOARD, Win32EventListenerKeyboard::LISTENER_ID, target, callback);
	}

	void Win32EventListenerKeyboard::registerScriptWin32Handler(int handler, int type)
	{
		if (type == 1)
		{
			// key down event
			_keyDownScriptHandler = handler;
		}
		else if (type == 2)
		{
			// key up event
			_keyUpScriptHandler = handler;
		}
	}

	void Win32EventListenerKeyboard::unregisterScriptWin32Handler(int type)
	{
		if (type == 1)
		{
			// key down event
			_keyDownScriptHandler = 0;
		}
		else if (type == 2)
		{
			// key up event
			_keyUpScriptHandler = 0;
		}
	}
}