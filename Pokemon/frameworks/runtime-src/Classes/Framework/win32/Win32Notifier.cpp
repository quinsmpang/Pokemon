#include "Win32Notifier.h"

using namespace cocos2d;

namespace framework
{
	void Win32Notifier::addEventListener(Win32EventListener *listener)
	{
		CCASSERT(listener, "param can't be null");
		auto listenerType = (int)listener->_type;
		if (this->_listenerMap.find(listenerType) == _listenerMap.end())
		{
			this->_listenerMap[listenerType] = std::list<Win32EventListener*>();
		}
		listener->retain();
		this->_listenerMap[listenerType].push_back(listener);
	}

	void Win32Notifier::removeEventListener(Win32EventListener *listener)
	{
		CCASSERT(listener, "param can't be null");
		auto listenerType = (int)listener->_type;
		if (this->_listenerMap.find(listenerType) != _listenerMap.end())
		{
			auto listeners = _listenerMap[listenerType];
			for (auto iter = listeners.begin(); iter != listeners.end(); ++iter)
			{
				if (listener == *iter)
				{
					listeners.remove(*iter);
					listener->release();
				}
			}
		}
	}

	void Win32Notifier::notify(Win32EventListener::Win32EventListenerType type, Win32EventArgs *args)
	{
		int nType = (int)type;
		if (this->_listenerMap.find(nType) != _listenerMap.end())
		{
			auto listeners = _listenerMap[nType];
			// with scene graph priority
			Win32EventListener *pTargetListener = nullptr;
			for (auto iter = listeners.begin(); iter != listeners.end(); ++iter)
			{
				auto listener = *iter;
				if (!pTargetListener)
				{
					pTargetListener = listener;
				}
				else
				{
					if (listener->_target->getPositionZ() >= pTargetListener->_target->getPositionZ())
					{
						pTargetListener = listener;
					}
				}
			}

			if (pTargetListener)
			{
				pTargetListener->_callback(pTargetListener->_target, args);
			}
		}
	}
}