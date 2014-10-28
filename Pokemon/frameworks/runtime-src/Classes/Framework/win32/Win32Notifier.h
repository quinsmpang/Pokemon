/******************************
Description: Win32 event notifier
Author: M.Wan
Date: 10/28/2014
******************************/

#ifndef __WIN32_WIN32NOTIFIER__
#define __WIN32_WIN32NOTIFIER__

#include "cocos2d.h"
#include "../base/Macros.h"
#include "Win32EventListener.h"
#include <unordered_map>
#include <list>

namespace framework
{
	class Win32Notifier : public cocos2d::Ref
	{
		SINGLETON(Win32Notifier);
	public:
		void addEventListener(Win32EventListener *listener);
		void removeEventListener(Win32EventListener *listener);
		void notify(Win32EventListener::Win32EventListenerType type, Win32EventArgs *args);

	protected:
		std::unordered_map<int, std::list<Win32EventListener*> > _listenerMap;
	};
}

#endif