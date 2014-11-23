#include "ModalLayer.h"
#include "../lua/LuaUtils.h"

using namespace cocos2d;

namespace framework
{
	ModalLayer *ModalLayer::create()
	{
		auto modalLayer = new ModalLayer();
		if (modalLayer && modalLayer->init())
		{
			modalLayer->autorelease();
			return modalLayer;
		}

		CC_SAFE_RELEASE_NULL(modalLayer);
		return nullptr;
	}

	bool ModalLayer::init()
	{
		if (!LayerColor::init())
		{
			return false;
		}

		this->setColor(Color3B(0, 0, 0));
		this->setOpacity(0);

		auto pListener = EventListenerTouchOneByOne::create();
		pListener->setSwallowTouches(true);
		pListener->onTouchBegan = CC_CALLBACK_2(ModalLayer::onTouchBegan, this);
		pListener->onTouchMoved = CC_CALLBACK_2(ModalLayer::onTouchMoved, this);
		pListener->onTouchEnded = CC_CALLBACK_2(ModalLayer::onTouchEnded, this);
		pListener->onTouchCancelled = CC_CALLBACK_2(ModalLayer::onTouchCancelled, this);
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);

		return true;
	}

	void ModalLayer::onEnter()
	{
		LayerColor::onEnter();

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::getInstance()->executePeertableFunction(this, "onComeIn", Vector<Ref*>(), Vector<Ref*>(), false);
		}
#endif
	}

	void ModalLayer::onExit()
	{
#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::getInstance()->executePeertableFunction(this, "onGoOut", Vector<Ref*>(), Vector<Ref*>(), false);
		}
#endif

		LayerColor::onExit();
	}

	bool ModalLayer::onTouchBegan(Touch *touch, Event *unused_event)
	{
		CC_UNUSED_PARAM(unused_event);

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			Point pos = touch->getLocation();

			// params
			Vector<Ref*> pParams(2);
			pParams.pushBack(__Float::create(pos.x));
			pParams.pushBack(__Float::create(pos.y));
			// param types
			Vector<Ref*> pTypes(2);
			pTypes.pushBack(__String::create("__Float"));
			pTypes.pushBack(__String::create("__Float"));

			LuaUtils::getInstance()->executePeertableFunction(this, "onModalTouchBegan", pParams, pTypes, false);
		}
#endif

		return true;
	}

	void ModalLayer::onTouchMoved(Touch *touch, Event *unused_event)
	{
		CC_UNUSED_PARAM(unused_event);

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			Point pos = touch->getLocation();

			// params
			Vector<Ref*> pParams(2);
			pParams.pushBack(__Float::create(pos.x));
			pParams.pushBack(__Float::create(pos.y));
			// param types
			Vector<Ref*> pTypes(2);
			pTypes.pushBack(__String::create("__Float"));
			pTypes.pushBack(__String::create("__Float"));

			LuaUtils::getInstance()->executePeertableFunction(this, "onModalTouchMoved", pParams, pTypes, false);
		}
#endif
	}


	void ModalLayer::onTouchEnded(Touch *touch, Event *unused_event)
	{
		CC_UNUSED_PARAM(unused_event);

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			Point pos = touch->getLocation();

			// params
			Vector<Ref*> pParams(2);
			pParams.pushBack(__Float::create(pos.x));
			pParams.pushBack(__Float::create(pos.y));
			// param types
			Vector<Ref*> pTypes(2);
			pTypes.pushBack(__String::create("__Float"));
			pTypes.pushBack(__String::create("__Float"));

			LuaUtils::getInstance()->executePeertableFunction(this, "onModalTouchEnded", pParams, pTypes, false);
		}
#endif
	}

	void ModalLayer::onTouchCancelled(Touch *touch, Event *unused_event)
	{
		CC_UNUSED_PARAM(unused_event);

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			Point pos = touch->getLocation();

			// params
			Vector<Ref*> pParams(2);
			pParams.pushBack(__Float::create(pos.x));
			pParams.pushBack(__Float::create(pos.y));
			// param types
			Vector<Ref*> pTypes(2);
			pTypes.pushBack(__String::create("__Float"));
			pTypes.pushBack(__String::create("__Float"));

			LuaUtils::getInstance()->executePeertableFunction(this, "onModalTouchCancelled", pParams, pTypes, false);
		}
#endif
	}

	/// Wait for override
	void ModalLayer::onModalTouchBegan(float x, float y)
	{
		// override me.
	}
	
	void ModalLayer::onModalTouchMoved(float x, float y)
	{
		// override me.
	}
	
	void ModalLayer::onModalTouchEnded(float x, float y)
	{
		// override me.
	}
	
	void ModalLayer::onModalTouchCancelled(float x, float y)
	{
		// override me.
	}

	void ModalLayer::onComeIn()
	{
		// override with come in actions here.
	}

	void ModalLayer::onGoOut()
	{
		// override with go out actions here.
	}
}