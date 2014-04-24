#include "ScriptHandlerManager.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

/*******ScriptHandlerDelegate********/

ScriptHandlerDelegate *ScriptHandlerDelegate::create(cocos2d::Node *listener, void *handler)
{
	auto pDelegate = new ScriptHandlerDelegate(listener, handler);

	if (pDelegate)
	{
		pDelegate->autorelease();
		return pDelegate;
	}

	CC_SAFE_DELETE(pDelegate);
	return nullptr;
}

ScriptHandlerDelegate::ScriptHandlerDelegate(cocos2d::Node *listener, void *handler)
	: _listener(listener)
	, _handler(handler)
{
	CCASSERT(listener && handler, "listener and handler can't be null");

	this->_listener->retain();
}

ScriptHandlerDelegate::~ScriptHandlerDelegate()
{
	CC_SAFE_RELEASE(this->_listener);
}

/*******ScriptHandlerManager********/

ScriptHandlerManager *ScriptHandlerManager::_instance = nullptr;

ScriptHandlerManager *ScriptHandlerManager::getInstance()
{
	if (!_instance)
	{
		_instance = new ScriptHandlerManager();
	}

	return _instance;
}

ScriptHandlerManager::ScriptHandlerManager()
	: _handlers(std::map<cocos2d::Node*, std::vector<ScriptHandlerDelegate*> >())
{
	this->_handlers.clear();
}

ScriptHandlerManager::~ScriptHandlerManager()
{
}

void ScriptHandlerManager::addHandler(cocos2d::Node *listener, void *handler, ScriptHandlerType handlerType)
{
	auto pHandler = ScriptHandlerDelegate::create(listener, handler);
	pHandler->retain();

	auto iter = this->_handlers.find(handlerType);
	std::vector<ScriptHandlerDelegate*> delegates;
	if (iter != this->_handlers.end())
	{
		delegates = iter->second;
	}

	delegates.push_back(pHandler);
	this->_handlers[handlerType] = delegates;
}

void ScriptHandlerManager::removeHandler(cocos2d::Node *listener, ScriptHandlerType handlerType)
{
	if (!listener)
	{
		return;
	}

	auto iter = this->_handlers.find(handlerType);
	if (iter == this->_handlers.end() || iter->second.empty())
	{
		return;
	}

	auto handlerIter = iter->second.begin();
	bool bExist = false;
	for ( ; handlerIter != iter->second.end(); ++handlerIter)
	{
		if ((*handlerIter)->_listener == listener)
		{
			bExist = true;
			break;
		}
	}

	if (bExist)
	{
		LuaEngine::getInstance()->removeScriptHandler((int)((*handlerIter)->_handler));
		iter->second.erase(handlerIter);
	}
}

void ScriptHandlerManager::notify(ScriptHandlerType handlerType)
{
	auto iter = this->_handlers.begin();
	for ( ; iter != this->_handlers.end(); ++iter)
	{
		if (iter->first == handlerType)
		{
			auto handlers = iter->second;
			auto handlerIter = handlers.begin();

			for ( ; handlerIter != handlers.end(); ++handlerIter)
			{
				Node *pListener = (*handlerIter)->_listener;
				void *pDelegate = (*handlerIter)->_handler;

				switch (handlerType)
				{
				case ScriptHandlerType::EVENTNODE_TOUCH:
					break;
				case ScriptHandlerType::EVENTNODE_KEYBOARD:
					break;
				default:
					break;
				}
			}
		}
	}
}