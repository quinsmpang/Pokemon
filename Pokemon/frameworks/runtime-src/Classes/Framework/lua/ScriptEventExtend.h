/******************************
Description: ScriptEvent extensions, to support custom events
Author: M.Wan
Date: 4/25/2014
******************************/

#ifndef __LUA_SCRIPTEVENTEXTEND__
#define __LUA_SCRIPTEVENTEXTEND__

#include "cocos2d.h"

namespace framework
{
	enum class ScriptEventType
	{
		kEventNodeTouchEvent,
		kEventNodeKeyboardEvent,
	};
	
	struct CustomHandlerTypes
	{
		static int EVENTNODE_TOUCH_HANDLER;
		static int EVENTNODE_KEYBOARD_HANDLER;
	};
	
	struct ScriptEvent
	{
		ScriptEventType _type;
		void *_data;

		ScriptEvent(ScriptEventType type, void *data)
			: _type(type)
			, _data(data)
		{
		}
	};

	struct EventNodeTouchScriptData
	{
		void *_nativeData;
		cocos2d::Ref *_sender;

		EventNodeTouchScriptData(void *nativeData, cocos2d::Ref *sender)
			: _nativeData(nativeData)
			, _sender(sender)
		{
		}
	};

	struct EventNodeKeyboardScriptData
	{
		void *_nativeData;
		cocos2d::Ref *_sender;
		cocos2d::EventKeyboard::KeyCode _keyCode;

		EventNodeKeyboardScriptData(void *nativeData, cocos2d::Ref *sender, cocos2d::EventKeyboard::KeyCode keyCode)
			: _nativeData(nativeData)
			, _sender(sender)
			, _keyCode(keyCode)
		{
		}
	};
}

#endif