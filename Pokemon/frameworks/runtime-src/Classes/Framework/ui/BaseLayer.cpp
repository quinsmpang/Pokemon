#include "BaseLayer.h"

using namespace cocos2d;

namespace framework
{
	BaseLayer::BaseLayer()
		: _touchListener(nullptr)
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		, _keyboardListener(nullptr)
#endif
	{
	}

	BaseLayer::~BaseLayer()
	{
		CC_SAFE_RELEASE_NULL(_touchListener);
		CC_SAFE_RELEASE_NULL(_keyboardListener);
	}

	bool BaseLayer::init()
	{
		if (!Layer::init())
		{
			return false;
		}

		auto pTouchListener = EventListenerTouchOneByOne::create();
		// dismiss the event bubble
		pTouchListener->setSwallowTouches(true);
		pTouchListener->onTouchBegan = CC_CALLBACK_2(BaseLayer::onTouchBegan, this);
		pTouchListener->onTouchMoved = CC_CALLBACK_2(BaseLayer::onTouchMoved, this);
		pTouchListener->onTouchEnded = CC_CALLBACK_2(BaseLayer::onTouchEnded, this);
		pTouchListener->onTouchCancelled = CC_CALLBACK_2(BaseLayer::onTouchCancelled, this);

		this->_touchListener = pTouchListener;

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		// register keyboard events
		auto pKeyboardListener = EventListenerKeyboard::create();
		pKeyboardListener->onKeyPressed = CC_CALLBACK_2(BaseLayer::onKeyPressed, this);
		pKeyboardListener->onKeyReleased = CC_CALLBACK_2(BaseLayer::onKeyReleased, this);

		this->_keyboardListener = pKeyboardListener;
#endif

		this->_touchListener->retain();
		this->_keyboardListener->retain();

		return true;
	}

	void BaseLayer::setEnabled(bool isEnabled)
	{
		this->_isEnabled = isEnabled;

		if (isEnabled)
		{
			this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
#endif
		}
		else
		{
			this->_eventDispatcher->removeEventListener(_touchListener);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			this->_eventDispatcher->removeEventListener(_keyboardListener);
#endif
		}
	}

	bool BaseLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
	{
		return Layer::onTouchBegan(pTouch, pEvent);
	}

	void BaseLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
	{
		Layer::onTouchMoved(pTouch, pEvent);
	}

	void BaseLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
	{
		Layer::onTouchEnded(pTouch, pEvent);
	}

	void BaseLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
	{
		Layer::onTouchCancelled(pTouch, pEvent);
	}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	void BaseLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *pEvent)
	{
		CCASSERT(false, "override me");
	}

	void BaseLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
	{
		CCASSERT(false, "override me");
	}

#endif
}