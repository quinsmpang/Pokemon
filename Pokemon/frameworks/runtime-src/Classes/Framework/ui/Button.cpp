#include "Button.h"

using namespace cocos2d;

namespace framework
{

bool Button::initWithNodes(cocos2d::Node *pDefaultImage, cocos2d::Node *pSelectedImage, cocos2d::Node *pDisabledImage, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	if (!EventNode::init())
	{
		return false;
	}

	this->_defaultImage = pDefaultImage;
	this->_selectedImage = pSelectedImage;
	this->_disabledImage = pDisabledImage;
	this->_defaultImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	this->_selectedImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	this->_disabledImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	CC_SAFE_RETAIN(this->_defaultImage);
	CC_SAFE_RETAIN(this->_selectedImage);
	CC_SAFE_RETAIN(this->_disabledImage);

	this->addChild(pDefaultImage);
	this->addChild(pSelectedImage);
	this->addChild(pDisabledImage);

	this->_selectedImage->setVisible(false);
	this->_disabledImage->setVisible(false);

	this->setAnchorPoint(Point::ANCHOR_MIDDLE);
	this->setContentSize(pDefaultImage->getContentSize());

	this->_touchCallback = touchCallback;
	this->_keyboardCallback = keyboardCallback;

	return true;
}

Button *Button::create(const char *szDefaultImagePath, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	return Button::create(szDefaultImagePath, szDefaultImagePath, szDefaultImagePath, touchCallback, keyboardCallback);
}

Button *Button::create(const char *szDefaultImagePath, const char *szSelectedImagePath, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	return Button::create(szDefaultImagePath, szSelectedImagePath, szDefaultImagePath, touchCallback, keyboardCallback);
}

Button *Button::create(const char *szDefaultImagePath, const char *szSelectedImagePath, const char *szDisabledImagePath, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	auto pDefaultImage = Sprite::create(szDefaultImagePath);
	auto pSelectedImage = Sprite::create(szSelectedImagePath);
	auto pDisabledImage = Sprite::create(szDisabledImagePath);

	return Button::create(pDefaultImage, pSelectedImage, pDisabledImage, touchCallback, keyboardCallback);
}

Button *Button::create(cocos2d::Node *pDefaultImage, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	return Button::create(pDefaultImage, pDefaultImage, pDefaultImage, touchCallback, keyboardCallback);
}

Button *Button::create(cocos2d::Node *pDefaultImage, cocos2d::Node *pSelectedImage, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	return Button::create(pDefaultImage, pSelectedImage, pDefaultImage, touchCallback, keyboardCallback);
}

Button *Button::create(cocos2d::Node *pDefaultImage, cocos2d::Node *pSelectedImage, cocos2d::Node *pDisabledImage, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback)
{
	auto pBtn = new Button();
	if (pBtn && pBtn->initWithNodes(pDefaultImage, pSelectedImage, pDisabledImage, touchCallback, keyboardCallback))
	{
		pBtn->autorelease();

		return pBtn;
	}

	return nullptr;
}

Button::~Button()
{
}

}