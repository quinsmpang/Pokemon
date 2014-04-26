#include "GameLayer.h"
#include "MaskLayer.h"
#include "lua/LuaUtils.h"

using namespace cocos2d;

namespace framework
{

	GameLayer::GameLayer()
		: _eventLayer(nullptr)
	{
	}

	bool GameLayer::init()
	{
		if (!BaseLayer::init())
		{
			return false;
		}

		// create touch layer
		this->_eventLayer = EventLayer::create();
		this->_eventLayer->retain();

		this->addChild(this->_eventLayer);

		return true;
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

	void GameLayer::setEnabled(bool isEnabled)
	{
		BaseLayer::setEnabled(isEnabled);
		if (this->_eventLayer)
		{
			this->_eventLayer->setEnabled(isEnabled);
		}
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

	EventNode *GameLayer::getFocusNode()
	{
		if (this->_eventLayer)
		{
			return this->_eventLayer->_focusNode;
		}
		
		return nullptr;
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

		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::executePeertableFunction(this, "onEnter", Vector<Ref*>(), Vector<Ref*>(), false);
		}
	}

	void GameLayer::onExit()
	{
		Layer::onExit();
		
		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::executePeertableFunction(this, "onExit", Vector<Ref*>(), Vector<Ref*>(), false);
		}
	}

	void GameLayer::addChild(Node *child)
	{
		this->addChild(child, child->getLocalZOrder(), -1);
	}
	
	void GameLayer::addChild(Node *child, int localZOrder)
	{
		this->addChild(child, localZOrder, -1);
	}

	void GameLayer::addChild(Node *child, int localZOrder, int tag)
	{
		// ignore mask layer
		if (dynamic_cast<MaskLayer*>(child))
		{
			Layer::addChild(child, localZOrder, tag);
			return;
		}

		if (child != _eventLayer && this->_eventLayer)
		{
			_eventLayer->removeFromParent();
		}
		Layer::addChild(child, localZOrder, tag);
		if (child != _eventLayer && this->_eventLayer)
		{
			Layer::addChild(_eventLayer, _eventLayer->getLocalZOrder(), -1);
		}
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
	}

}