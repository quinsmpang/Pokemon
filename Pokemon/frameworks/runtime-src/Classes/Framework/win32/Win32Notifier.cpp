#include "Win32Notifier.h"
#include "Win32EventListenerKeyboard.h"
#include <algorithm>

using namespace cocos2d;
using namespace std;

static std::unordered_map<int, std::vector<cocos2d::Node*> > g_globalZOrderNodeMap;		// save all node zorder
static std::unordered_map<cocos2d::Node*, int> g_nodePriorityMap;		// node priority map
static std::unordered_map<Node*, bool> g_listenerTargetMap;
static int g_nodePriorityIndex;

static bool isInScene(Node *node)
{
	Node *pCurrent = node;
	if (!pCurrent->isVisible())
	{
		return false;
	}
	while (pCurrent->getParent())
	{
		pCurrent = pCurrent->getParent();
		if (!pCurrent->isVisible())
		{
			return false;
		}
	}

	if (pCurrent != Director::getInstance()->getRunningScene())
	{
		return false;
	}
	return true;
}

namespace std
{
	template<>
	struct greater<framework::Win32EventListener*>
	{
		bool operator()(framework::Win32EventListener*& _Left, framework::Win32EventListener*& _Right) const
		{
			if (isInScene(_Left->_target) && !isInScene(_Right->_target))
			{
				return true;
			}
			else if (!isInScene(_Left->_target) && isInScene(_Right->_target))
			{
				return false;
			}
			return (g_nodePriorityMap[_Left->_target]) > (g_nodePriorityMap[_Right->_target]);
		}
	};
}

namespace framework
{
	/*static bool sortListenerFunc(const Win32EventListener *el1, const Win32EventListener *el2)
	{
	return (*el1)._target->getPositionZ() > (*el2)._target->getPositionZ();
	}*/

	Win32Notifier::Win32Notifier()
	{
	}

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
			this->sortAllListenersWithScenePriority(listeners);
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

	void Win32Notifier::sortAllListenersWithScenePriority(std::list<Win32EventListener*> &listeners)
	{
		// save listener target as hash
		g_listenerTargetMap.clear();
		for (auto &listener : listeners)
		{
			g_listenerTargetMap[listener->_target] = true;
		}

		auto rootNode = Director::getInstance()->getRunningScene();
		if (rootNode) 
		{
			// reset
			g_nodePriorityIndex = 0;
			g_nodePriorityMap.clear();

			this->visitTarget(rootNode, true);

			listeners.sort(std::greater<Win32EventListener*>());
		}
	}

	void Win32Notifier::visitTarget(cocos2d::Node *target, bool isRoot)
	{
		auto &children = target->getChildren();
		int childrenCount = children.size();
		if (childrenCount > 0)
		{
			Node *pCurrent = nullptr;
			int i = 0;
			for ( ; i < childrenCount; ++i)
			{
				pCurrent = children.at(i);
				if (pCurrent && pCurrent->getLocalZOrder() < 0)
				{
					this->visitTarget(pCurrent, false);
				}
				else
				{
					break;
				}
			}

			if (g_listenerTargetMap.find(target) != g_listenerTargetMap.end())
			{
				g_globalZOrderNodeMap[target->getGlobalZOrder()].push_back(target);
			}

			for ( ; i < childrenCount; ++i)
			{
				pCurrent = children.at(i);
				if (pCurrent)
				{
					this->visitTarget(pCurrent, false);
				}
			}
		}
		else
		{
			if (g_listenerTargetMap.find(target) != g_listenerTargetMap.end())
			{
				g_globalZOrderNodeMap[target->getGlobalZOrder()].push_back(target);
			}
		}

		if (isRoot)
		{
			std::vector<float> globalZOrders;
			globalZOrders.reserve(g_globalZOrderNodeMap.size());

			for (const auto &pair : g_globalZOrderNodeMap)
			{
				globalZOrders.push_back(pair.first);
			}

			std::sort(globalZOrders.begin(), globalZOrders.end(), [](const float a, const float b){
				return a < b;
			});

			for (const auto &globalZ : globalZOrders)
			{
				for (const auto &node : g_globalZOrderNodeMap[globalZ])
				{
					g_nodePriorityMap[node] = ++g_nodePriorityIndex;
				}
			}

			g_globalZOrderNodeMap.clear();
		}
	}
}