#include "KeyboardHelper.h"
#include "Win32Notifier.h"
#include "Win32EventArgs.h"
#include <iostream>
#include <list>

using namespace std;

namespace framework
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	static HHOOK g_hHook = INVALID_HOOK;	// handle of the hook
	static list<int> g_pressedKeys;	// record pressed keys

	// default hook callback function
	LRESULT CALLBACK DefaultKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		if (nCode == HC_ACTION)
		{
			int vkCode = (int)wParam;

			// the 31th bit indicates the key state
			if (lParam & 0x80000000)
			{
				///todo memory leak
				// the key is released
				int *keyData = new int[2];
				keyData[0] = vkCode;
				keyData[1] = 2;
				auto eventArgs = new Win32EventArgs(keyData);
				Win32Notifier::getInstance()->notify(Win32EventListener::Win32EventListenerType::KEYBOARD, eventArgs);

				g_pressedKeys.remove(vkCode);
			}
			else
			{
				// the key is pressed
				if (g_pressedKeys.size() <= 0 || g_pressedKeys.back() != vkCode)
				{
					int *keyData = new int[2];
					keyData[0] = vkCode;
					keyData[1] = 1;
					auto eventArgs = new Win32EventArgs(keyData);
					Win32Notifier::getInstance()->notify(Win32EventListener::Win32EventListenerType::KEYBOARD, eventArgs);

					g_pressedKeys.push_back(vkCode);
				}
			}

			return CallNextHookEx(g_hHook, nCode, wParam, lParam);
		}
	}
#endif

	KeyboardHelper::KeyboardHelper()
	{
	}

	bool KeyboardHelper::isKeyPressed(int keyCode)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		return GetAsyncKeyState(keyCode) & 0x8000;
#else
        return false;
#endif
	}

	bool KeyboardHelper::hookOn()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		// get current application handle
		// HINSTANCE instance = GetModuleHandle(nullptr);
		// CCASSERT(instance, "Invalid application handle");

		// the hook is already installed
		if (g_hHook != INVALID_HOOK)
		{
			return false;
		}

		// g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, DefaultKeyboardProc, instance, NULL);
		// low-level keyboard hook can only be set to global, so use normal keyboard hook here.
		g_hHook = SetWindowsHookEx(WH_KEYBOARD, DefaultKeyboardProc, NULL, GetCurrentThreadId());

		// install failed
		if (g_hHook == INVALID_HOOK)
		{
			return false;
		}

		return true;
#else
        return false;
#endif
	}

	bool KeyboardHelper::hookOff()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		// no hook
		if (g_hHook == INVALID_HOOK)
		{
			return false;
		}
		if (UnhookWindowsHookEx(g_hHook) == 0)
		{
			return false;
		}

		g_hHook = INVALID_HOOK;
		return true;
#else
        return false;
#endif
	}
}