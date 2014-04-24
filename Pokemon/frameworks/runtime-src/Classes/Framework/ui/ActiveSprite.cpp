#include "ActiveSprite.h"

using namespace cocos2d;

namespace framework
{

bool ActiveSprite::initWithSprite(Node *pSprite, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	if (!EventNode::init() || !pSprite)
	{
		return false;
	}

	this->_defaultImage = pSprite;
	this->_defaultImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	CC_SAFE_RETAIN(this->_defaultImage);

	this->addChild(pSprite);

	this->setAnchorPoint(Point::ANCHOR_MIDDLE);
	this->setContentSize(pSprite->getContentSize());

	this->_touchCallback = touchCallback;
	this->_keyboardCallback = keyboardCallback;

	return true;
}

ActiveSprite *ActiveSprite::create(const char *szSpritePath)
{
	return ActiveSprite::createWithCallback(szSpritePath, nullptr, nullptr);
}

ActiveSprite *ActiveSprite::create(cocos2d::Node *pSprite)
{
	return ActiveSprite::createWithCallback(pSprite, nullptr, nullptr);
}

ActiveSprite *ActiveSprite::createWithCallback(const char *szSpritePath, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	auto pSprite = Sprite::create(szSpritePath);
	
	return ActiveSprite::createWithCallback(pSprite, touchCallback, keyboardCallback);
}

ActiveSprite *ActiveSprite::createWithCallback(Node *pSprite, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	auto pActiveSprite = new ActiveSprite();

	if (pActiveSprite && pActiveSprite->initWithSprite(pSprite, touchCallback, keyboardCallback))
	{
		pActiveSprite->autorelease();

		return pActiveSprite;
	}

	CC_SAFE_DELETE(pActiveSprite);
	return nullptr;
}

ActiveSprite::~ActiveSprite()
{
}

void ActiveSprite::updateImageVisibility()
{
	SAFE_SET_VISIBILITY(this->_defaultImage, true);
}

}