#include "ModalLayer.h"

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
		this->setOpacity(200);

		return true;
	}

	void ModalLayer::onEnter()
	{
		LayerColor::onEnter();

		// You should add listeners after addChild method, otherwise the events of this layer would also be paused.
		this->_eventDispatcher->pauseEventListenersForTarget(this->_parent, true);
	}

	void ModalLayer::onExit()
	{
		this->_eventDispatcher->resumeEventListenersForTarget(this->_parent, true);

		LayerColor::onExit();
	}
}