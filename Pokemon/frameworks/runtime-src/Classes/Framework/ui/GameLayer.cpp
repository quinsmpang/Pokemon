#include "GameLayer.h"

using namespace cocos2d;

namespace framework
{
	GameLayer::GameLayer()
		: Layer()
		, _winSize(Director::getInstance()->getWinSize())
		, _isShown(false)
		, _comeInWhenPushAction(nullptr)
		, _comeInWhenPopAction(nullptr)
		, _goOutWhenPushAction(nullptr)
		, _goOutWhenPopAction(nullptr)
	{
	}

	GameLayer::~GameLayer()
	{
	}

	bool GameLayer::init()
	{
		if (!Layer::init())
		{
			return false;
		}

		auto pListener = EventListenerTouchOneByOne::create();
		pListener->setSwallowTouches(true);

		pListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
		pListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
		pListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
		pListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);

		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);

		return true;
	}

	GameLayer *GameLayer::createWithTransitions(cocos2d::ActionInterval *comeInWhenPushAction, cocos2d::ActionInterval *comeInWhenPopAction, cocos2d::ActionInterval *goOutWhenPushAction, cocos2d::ActionInterval *goOutWhenPopAction)
	{
		auto pLayer = new GameLayer();
		if (pLayer && pLayer->init())
		{
			pLayer->_comeInWhenPushAction = comeInWhenPushAction;
			pLayer->_comeInWhenPopAction = comeInWhenPopAction;
			pLayer->_goOutWhenPushAction = goOutWhenPushAction;
			pLayer->_goOutWhenPopAction = goOutWhenPopAction;
			
			pLayer->_comeInWhenPushAction->retain();
			pLayer->_comeInWhenPopAction->retain();
			pLayer->_goOutWhenPushAction->retain();
			pLayer->_goOutWhenPopAction->retain();

			pLayer->autorelease();

			return pLayer;
		}

		CC_SAFE_RELEASE_NULL(pLayer);
		return nullptr;
	}

	bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
	{
		if (!this->_isShown)
		{
			return true;
		}

		return Layer::onTouchBegan(touch, unused_event);
	}

	void GameLayer::onTouchMoved(Touch *touch, Event *unused_event)
	{
		if (!this->_isShown)
		{
			return;
		}

		Layer::onTouchMoved(touch, unused_event);
	}

	void GameLayer::onTouchEnded(Touch *touch, Event *unused_event)
	{
		if (!this->_isShown)
		{
			return;
		}

		Layer::onTouchEnded(touch, unused_event);
	}

	void GameLayer::onTouchCancelled(Touch *touch, Event *unused_event)
	{
		if (!this->_isShown)
		{
			return;
		}

		Layer::onTouchCancelled(touch, unused_event);
	}

}