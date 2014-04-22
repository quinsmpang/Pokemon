#include "GameLayer.h"
#include "lua/LuaUtils.h"

using namespace cocos2d;

namespace framework
{

GameLayer::GameLayer()
	: _parentLayer(nullptr)
	, _eventLayer(nullptr)
	, _touchListener(nullptr)
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	, _keyboardListener(nullptr)
#endif
{
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// create touch layer
	this->_eventLayer = EventLayer::create();
	this->_eventLayer->retain();

	this->addChild(this->_eventLayer);

	return true;
}

void GameLayer::pushLayer(GameLayer *pLayer)
{
	CCASSERT(pLayer, "the layer should not be null");

	pLayer->_parentLayer = this;
	this->unregisterTouchEvents();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	this->unregisterKeyboardEvents();
#endif

	auto pCurrentScene = this->getScene();
	pCurrentScene->addChild(pLayer);
}

void GameLayer::popLayer()
{
	if (this->_parentLayer)
	{
		this->registerTouchEvents();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		this->registerKeyboardEvents();
#endif
	}
	this->removeFromParentAndCleanup(true);
}

bool GameLayer::isCoreLayer()
{
	return !this->_parentLayer;
}

GameLayer *GameLayer::getParentLayer()
{
	return this->_parentLayer;
}

GameLayer *GameLayer::getCoreLayer()
{
	auto currentLayer = this;
	while (currentLayer->_parentLayer)
	{
		currentLayer = currentLayer->_parentLayer;
	}
	return currentLayer;
}

void GameLayer::setEventLayer(EventLayer *pLayer)
{
	CCASSERT(pLayer, "Event layer can't be null");
	if (this->_eventLayer)
	{
		this->_eventLayer->release();
		this->removeChild(_eventLayer);
	}
	
	this->_eventLayer = pLayer;
	pLayer->retain();
	this->addChild(pLayer);
}

void GameLayer::addControl(EventNode *pControl)
{
	this->_eventLayer->addChild(pControl);
}

void GameLayer::addControlByTag(EventNode *pControl, int tag)
{
	this->_eventLayer->addChild(pControl, pControl->getLocalZOrder(), tag);
}

void GameLayer::removeControl(EventNode *pControl)
{
	this->_eventLayer->removeChild(pControl);
}

void GameLayer::removeControlByTag(int tag, bool cleanup)
{
	this->_eventLayer->removeChildByTag(tag, cleanup);
}

void GameLayer::setFocusNode(EventNode *pNode)
{
	if (this->_eventLayer && this->_eventLayer->_focusNode)
	{
		this->_eventLayer->_focusNode->blur();
	}
	this->_eventLayer->_focusNode = pNode;
	if (pNode)
	{
		pNode->focus();
	}
}

void GameLayer::onEnter()
{
	Layer::onEnter();
#if ScriptType == 1
	LuaUtils::executePeertableFunction(this, "onEnter", Vector<Ref*>(), Vector<Ref*>(), false);
#endif
}

void GameLayer::onExit()
{
	Layer::onExit();
#if ScriptType == 1
	LuaUtils::executePeertableFunction(this, "onExit", Vector<Ref*>(), Vector<Ref*>(), false);
#endif
}

void GameLayer::registerTouchEvents()
{
	if (this->_eventLayer)
	{
		this->_eventLayer->enableTouch();
	}
}

void GameLayer::unregisterTouchEvents()
{
	if (this->_eventLayer)
	{
		this->_eventLayer->disableTouch();
	}
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
void GameLayer::registerKeyboardEvents()
{
	if (this->_eventLayer)
	{
		this->_eventLayer->enableKeyboard();
	}
}

void GameLayer::unregisterKeyboardEvents()
{
	if (this->_eventLayer)
	{
		this->_eventLayer->disableKeyboard();
	}
}
#endif

GameLayer::~GameLayer()
{
	CC_SAFE_RELEASE(this->_eventLayer);
	CC_SAFE_RELEASE_NULL(this->_touchListener);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	CC_SAFE_RELEASE_NULL(this->_keyboardListener);
#endif
}

}