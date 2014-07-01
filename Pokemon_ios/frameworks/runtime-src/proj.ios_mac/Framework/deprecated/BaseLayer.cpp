#include "BaseLayer.h"

using namespace cocos2d;

namespace framework
{
	BaseLayer::BaseLayer()
		: _isEnabled(true)
	{
	}

	BaseLayer::~BaseLayer()
	{
	}

	bool BaseLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
	{
		if (!_isEnabled)
		{
			return false;
		}

		return Layer::onTouchBegan(pTouch, pEvent);
	}

	void BaseLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchMoved(pTouch, pEvent);
	}

	void BaseLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchEnded(pTouch, pEvent);
	}

	void BaseLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchCancelled(pTouch, pEvent);
	}

	void BaseLayer::onTouchesBegan(const std::vector<Touch*> &touches, Event *unused_event)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchesBegan(touches, unused_event);
	}

	void BaseLayer::onTouchesMoved(const std::vector<Touch*> &touches, Event *unused_event)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchesMoved(touches, unused_event);
	}

	void BaseLayer::onTouchesEnded(const std::vector<Touch*> &touches, Event *unused_event)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchesEnded(touches, unused_event);
	}

	void BaseLayer::onTouchesCancelled(const std::vector<Touch*> &touches, Event *unused_event)
	{
		if (!_isEnabled)
		{
			return;
		}

		Layer::onTouchesCancelled(touches, unused_event);
	}

}