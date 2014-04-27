#include "GameLayer.h"

using namespace cocos2d;

namespace framework
{
	GameLayer::GameLayer()
		: _isEnabled(true)
	{
	}

	GameLayer::~GameLayer()
	{
	}

	bool GameLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
	{
		if (!_isEnabled)
		{
			return false;
		}

		return Layer::onTouchBegan(pTouch, pEvent);
	}

	void GameLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchMoved(pTouch, pEvent);
	}

	void GameLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchEnded(pTouch, pEvent);
	}

	void GameLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchCancelled(pTouch, pEvent);
	}

}