#include "Win32Notifier.h"
#include "Win32EventListenerKeyboard.h"
#include <algorithm>

using namespace cocos2d;

namespace std
{
	static int calculateGlobalZOrder(Node *node)
	{
		auto rootNode = Director::getInstance()->getRunningScene();
		if (rootNode)
		{
			int globalZ = 0;
			Node *pCurrentNode = node;
			if (!pCurrentNode->isVisible())
			{
				return -1;
			}
			Node *pParentNode = pCurrentNode->getParent();
			while (pParentNode && pParentNode != rootNode)
			{
				if (!pParentNode->isVisible())
				{
					return -1;
				}
				globalZ += pCurrentNode->getLocalZOrder() + pParentNode->getChildren().getIndex(pCurrentNode);
				++globalZ;	// local zorder may be 0, accumulate the zorder by 1 for each node.
				pCurrentNode = pParentNode;
				pParentNode = pCurrentNode->getParent();
			}
			return globalZ;
		}
		return -1;
	}

	template<>
	struct greater<framework::Win32EventListener*>
	{
		bool operator()(framework::Win32EventListener*& _Left, framework::Win32EventListener*& _Right) const
		{
			return calculateGlobalZOrder(_Left->_target) < calculateGlobalZOrder(_Right->_target);
		}
	};
}

namespace framework
{
	/*static bool sortListenerFunc(const Win32EventListener *el1, const Win32EventListener *el2)
	{
	return (*el1)._target->getPositionZ() > (*el2)._target->getPositionZ();
	}*/

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
			auto &listeners = _listenerMap[listenerType];
			for (auto iter = listeners.begin(); iter != listeners.end(); )
			{
				if (listener == *iter)
				{
					iter = listeners.erase(iter);
					listener->release();
				}
				else
				{
					++iter;
				}
			}
		}
	}

	void Win32Notifier::notify(Win32EventListener::Win32EventListenerType type, Win32EventArgs *args)
	{
		int nType = (int)type;
		if (this->_listenerMap.find(nType) != _listenerMap.end())
		{
			auto &listeners = _listenerMap[nType];
			// sort listeners by zorder
			listeners.sort(std::greater<Win32EventListener*>());	
			//std::sort(listeners.begin(), listeners.end(), sortListenerFunc);	// list iterator is not a random iterator, so it doesn't support std::sort
			// with scene graph priority
			for (auto iter = listeners.begin(); iter != listeners.end(); ++iter)
			{
				auto listener = *iter;
				if (listener->isEnabled() && listener->_callback)
				{
					listener->_callback(listener->_target, args);
					// check whether to swallow the event
					if (listener->isEventsSwallowed())
					{
						break;
					}
				}
			}
		}
	}
}