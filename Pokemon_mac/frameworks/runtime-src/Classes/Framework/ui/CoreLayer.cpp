#include "CoreLayer.h"

using namespace cocos2d;

namespace framework
{
	CoreLayer::CoreLayer()
		: GameLayer()
		, _layers(nullptr)
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

	void CoreLayer::pushLayer(GameLayer *topLayer)
	{
		CCASSERT(topLayer, "Pushed layer can't be null");

		topLayer->retain();
		if (this->getTopLayer())
		{
			this->getTopLayer()->_isShown = false;
			// run go out action if there exists.
			auto goOutWhenPushAction = this->getTopLayer()->getGoOutWhenPushAction();
			if (goOutWhenPushAction)
			{
				auto outAction = Sequence::create(goOutWhenPushAction, CallFunc::create(CC_CALLBACK_0(CoreLayer::topLayerDidGoOutWhenPush, this, topLayer)), nullptr);
				this->getTopLayer()->runAction(outAction);
				return;
			}
		}

		// run come in action directly.
		this->topLayerDidGoOutWhenPush(topLayer);
	}

	void CoreLayer::popLayer()
	{
		CCASSERT(this->getTopLayer(), "Top layer must not be null");
		
		this->getTopLayer()->_isShown = false;
		// run pop out acton if there exists.
		auto goOutWhenPopAction = this->getTopLayer()->getGoOutWhenPopAction();
		if (goOutWhenPopAction)
		{
			auto outAction = Sequence::create(goOutWhenPopAction, CallFunc::create(CC_CALLBACK_0(CoreLayer::newLayerDidGoOutWhenPop, this)), nullptr);
			this->getTopLayer()->runAction(outAction);
			return;
		}

		// the front layer comes in directly.
		this->newLayerDidGoOutWhenPop();
	}

	GameLayer *CoreLayer::getTopLayer()
	{
		if (this->_layers->isEmpty())
		{
			return nullptr;
		}
		else
		{
			return (GameLayer*)this->_layers->top();
		}
	}

	void CoreLayer::topLayerDidGoOutWhenPush(GameLayer *newLayer)
	{
		if (newLayer)
		{
			this->_layers->push(newLayer);
			this->newLayerReadyToComeInWhenPush(newLayer);
		}
	}

	void CoreLayer::newLayerReadyToComeInWhenPush(GameLayer *newLayer)
	{
		CCASSERT(newLayer, "The new layer can't be null");

		this->addChild(newLayer);
		newLayer->release();
		if (newLayer->_comeInWhenPushAction)
		{
			auto inAction = Sequence::create(newLayer->_comeInWhenPushAction, CallFunc::create([=] () {
				newLayer->_isShown = true;
			}), nullptr);
			newLayer->runAction(inAction);
		}
		else
		{
			newLayer->_isShown = true;
		}
	}

	void CoreLayer::newLayerDidGoOutWhenPop()
	{
		this->getTopLayer()->removeFromParentAndCleanup(true);
		this->_layers->pop();

		this->topLayerReadyToComeInWhenPop();
	}

	void CoreLayer::topLayerReadyToComeInWhenPop()
	{
		if (this->getTopLayer())
		{
			if (this->getTopLayer()->_comeInWhenPopAction)
			{
				auto inAction = Sequence::create(this->getTopLayer()->_comeInWhenPopAction, CallFunc::create([this] () {
					this->getTopLayer()->_isShown = true;
				}), nullptr);
				this->getTopLayer()->runAction(inAction);
			}
			else
			{
				this->getTopLayer()->_isShown = true;
			}
		}
	}
}