#include "KeyboardHelper.h"

namespace framework
{
	KeyboardHelper *KeyboardHelper::_instance = nullptr;

	KeyboardHelper *KeyboardHelper::getInstance()
	{
		if (!_instance)
		{
			_instance = new KeyboardHelper();
		}
		return _instance;
	}

	KeyboardHelper::KeyboardHelper()
	{
	}

	bool KeyboardHelper::isKeyPressed(int keyCode)
	{
#ifdef WIN32
		return (GetAsyncKeyState(keyCode) & 0x8000) ? true : false;
#else
		return false;
#endif
	}

	bool KeyboardHelper::isKeyReleased(int keyCode)
	{
#ifdef WIN32
		return (GetAsyncKeyState(keyCode) & 0x8000) ? false : true;
#else
		return false;
#endif
	}
}