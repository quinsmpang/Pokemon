/******************************
Description: Win32 event listener base class
Author: M.Wan
Date: 10/28/2014
******************************/

#ifndef __WIN32_WIN32EVENTLISTENER__
#define __WIN32_WIN32EVENTLISTENER__

#include "cocos2d.h"
#include <functional>

namespace framework
{
	class Win32EventArgs;

	typedef unsigned int WIN32_LISTENER_ID;

	class Win32EventListener : public cocos2d::Ref
	{
		friend class Win32Notifier;
		friend std::greater<framework::Win32EventListener*>;
	public:
		enum class Win32EventListenerType
		{
			KEYBOARD = 1,
		};

        /**
         * Win32EventListener destructor.
         */
		virtual ~Win32EventListener();

        /**
         * Listener getter and setter.
         */
		inline void setEnabled(bool isEnabled)
		{
			this->_isEnabled = isEnabled;
		}
		inline bool isEnabled() const
		{
			return this->_isEnabled;
		}
		
		/**
         * Whether to swallow the event.
         */
		inline void setEventsSwallowed(bool bSwallowed)
		{
			this->_swallowed = bSwallowed;
		}
		inline bool isEventsSwallowed() const
		{
			return this->_swallowed;
		}

	protected:
		Win32EventListener();

		bool init(Win32EventListenerType type, WIN32_LISTENER_ID listenerId, cocos2d::Node *target, const std::function<void(cocos2d::Node*, Win32EventArgs*)> &callback);

		bool _isEnabled;
		bool _swallowed;
		Win32EventListenerType _type;
		WIN32_LISTENER_ID _listenerId;
		cocos2d::Node *_target;
		std::function<void(cocos2d::Node*, Win32EventArgs*)> _callback;

#if CC_ENABLE_SCRIPT_BINDING
		cocos2d::ccScriptType _scriptType;		// script type
#endif
	};
}

#endif