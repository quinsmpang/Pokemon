#include "CoreLayer.h"

using namespace cocos2d;

namespace framework
{
	CoreLayer::CoreLayer()
		: _layers(nullptr)
	{
	}

	CoreLayer::~CoreLayer()
	{
		if (this->_layers)
		{
			CC_SAFE_RELEASE_NULL(this->_layers);
		}
	}

	bool CoreLayer::init()
	{
		if (!GameLayer::init())
		{
			return false;
		}

		this->_layers = Stack::create();
		this->_layers->retain();
		return true;
	}

	void CoreLayer::pushLayer(BaseLayer *topLayer)
	{
		this->getTopLayer()->setEnabled(false);
		this->_layers->push(topLayer);

		this->addChild(topLayer);
	}

	void CoreLayer::popLayer()
	{
		this->getTopLayer()->removeFromParentAndCleanup(true);
		this->_layers->pop();

		this->getTopLayer()->setEnabled(true);
	}

	BaseLayer *CoreLayer::getTopLayer()
	{
		if (this->_layers->isEmpty())
		{
			return this;
		}
		else
		{
			return (BaseLayer*)this->_layers->top();
		}
	}
}