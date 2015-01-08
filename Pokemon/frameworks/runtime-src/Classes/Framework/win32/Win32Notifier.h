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
        /**
         * Win32Notifier is a singleton.
         */
		SINGLETON(Win32Notifier);
	public:
        /**
         * Store a new event listener.
         *
         * @param listener The win32 listener to add.
         */
		void addEventListener(Win32EventListener *listener);
        /**
         * Remove the event listener.
         *
         * @param listener The win32 listener to remove.
         */
		void removeEventListener(Win32EventListener *listener);
        /**
         * Send notifications for every event listeners.
         *
         * @param type Win32 event type.
         * @param args Related parameters of the event.
         */
		void notify(Win32EventListener::Win32EventListenerType type, Win32EventArgs *args);

	protected:
		void sortAllListenersWithScenePriority(std::list<Win32EventListener*> &listeners);
		void visitTarget(cocos2d::Node *target, bool isRoot);

		std::unordered_map<int, std::list<Win32EventListener*> > _listenerMap;
	};
}

#endif