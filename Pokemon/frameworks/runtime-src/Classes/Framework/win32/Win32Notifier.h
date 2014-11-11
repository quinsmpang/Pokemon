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
#include <vector>

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
		void sortAllListenersWithScenePriority(std::list<Win32EventListener*> &listeners);
		void visitTarget(cocos2d::Node *target, bool isRoot);

		std::unordered_map<int, std::list<Win32EventListener*> > _listenerMap;
	};
}

#endif