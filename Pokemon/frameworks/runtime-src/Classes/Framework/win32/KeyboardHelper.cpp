#include "KeyboardHelper.h"
#include "Win32Notifier.h"
#include "Win32EventArgs.h"
#include <iostream>

using namespace std;

namespace framework
{
	HHOOK g_hHook = INVALID_HOOK;	// handle of the hook
	int g_lastKeyCode = 0;		// the last pressed key

	// default hook callback function
	LRESULT CALLBACK DefaultKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		if (nCode == HC_ACTION)
		{
			KBDLLHOOKSTRUCT *pKbdInfo = (KBDLLHOOKSTRUCT*)lParam;
			int vkCode = pKbdInfo->vkCode;
			DWORD keyState = wParam;
			if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
			{
				// key down
				//cout << vkCode << " key down" << endl;
				if (vkCode != g_lastKeyCode)
				{
					int *keyData = new int[2];
					keyData[0] = vkCode;
					keyData[1] = 1;
					Win32Notifier::getInstance()->notify(Win32EventListener::Win32EventListenerType::KEYBOARD, new Win32EventArgs(keyData));

					g_lastKeyCode = vkCode;
				}
			}
			else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
			{
				// key up
				//cout << vkCode << " key up" << endl;
				int *keyData = new int[2];
				keyData[0] = vkCode;
				keyData[1] = 2;
				Win32Notifier::getInstance()->notify(Win32EventListener::Win32EventListenerType::KEYBOARD, new Win32EventArgs(keyData));

				// reset
				g_lastKeyCode = 0;
			}

			return CallNextHookEx(g_hHook, nCode, wParam, lParam);
		}
	}

	bool KeyboardHelper::isKeyPressed(int keyCode)
	{
		return GetAsyncKeyState(keyCode) & 0x8000;
	}

	bool KeyboardHelper::hookOn()
	{
		// get current application handle
		// HINSTANCE instance = GetModuleHandle(nullptr);
		// CCASSERT(instance, "Invalid application handle");
		HWND hwnd = GetActiveWindow();
		DWORD processId;
		DWORD threadId = GetWindowThreadProcessId(hwnd, &processId);

		// the hook is already installed
		if (g_hHook != INVALID_HOOK)
		{
			return false;
		}

		// g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, DefaultKeyboardProc, instance, NULL);
		g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, DefaultKeyboardProc, NULL, threadId);

		// install failed
		if (g_hHook == INVALID_HOOK)
		{
			return false;
		}

		return true;
	}

	bool KeyboardHelper::hookOff()
	{
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
	}
}