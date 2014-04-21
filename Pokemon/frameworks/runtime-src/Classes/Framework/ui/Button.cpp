#include "Button.h"

using namespace cocos2d;

namespace framework
{

bool Button::initWithNodes(cocos2d::Node *pDefaultImage, cocos2d::Node *pSelectedImage, cocos2d::Node *pDisabledImage, TouchCallback touchCallback, KeyboardCallback keyboardCallback)
{
	if (!EventNode::init())
	{
		return false;
	}

	this->_defaultImage = pDefaultImage;
	this->_selectedImage = pSelectedImage;
	this->_disabledImage = pDisabledImage;

	this->addChild(pDefaultImage);
	this->addChild(pSelectedImage);
	this->addChild(pDisabledImage);

	this->_selectedImage->setVisible(false);
	this->_disabledImage->setVisible(false);

	this->setContentSize(pDefaultImage->getContentSize());

	this->_touchCallback = touchCallback;
	this->_keyboardCallback = keyboardCallback;

	return true;
}

Button *Button::create(const char *szDefaultImagePath, TouchCallback touchCallback, KeyboardCallback keyboardCallback)
{
	return Button::create(szDefaultImagePath, szDefaultImagePath, szDefaultImagePath, touchCallback, keyboardCallback);
}

Button *Button::create(const char *szDefaultImagePath, const char *szSelectedImagePath, TouchCallback touchCallback, KeyboardCallback keyboardCallback)
{
	return Button::create(szDefaultImagePath, szSelectedImagePath, szDefaultImagePath, touchCallback, keyboardCallback);
}

Button *Button::create(const char *szDefaultImagePath, const char *szSelectedImagePath, const char *szDisabledImagePath, TouchCallback touchCallback, KeyboardCallback keyboardCallback)
{
	auto pDefaultImage = Sprite::create(szDefaultImagePath);
	auto pSelectedImage = Sprite::create(szSelectedImagePath);
	auto pDisabledImage = Sprite::create(szDisabledImagePath);

	return Button::create(pDefaultImage, pSelectedImage, pDisabledImage, touchCallback, keyboardCallback);
}

Button *Button::create(cocos2d::Node *pDefaultImage, TouchCallback touchCallback, KeyboardCallback keyboardCallback)
{
	return Button::create(pDefaultImage, pDefaultImage, pDefaultImage, touchCallback, keyboardCallback);
}

Button *Button::create(cocos2d::Node *pDefaultImage, cocos2d::Node *pSelectedImage, TouchCallback touchCallback, KeyboardCallback keyboardCallback)
{
	return Button::create(pDefaultImage, pSelectedImage, pDefaultImage, touchCallback, keyboardCallback);
}

Button *Button::create(cocos2d::Node *pDefaultImage, cocos2d::Node *pSelectedImage, cocos2d::Node *pDisabledImage, TouchCallback touchCallback, KeyboardCallback keyboardCallback)
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
	CC_SAFE_RELEASE_NULL(_defaultImage);
	CC_SAFE_RELEASE_NULL(_selectedImage);
	CC_SAFE_RELEASE_NULL(_disabledImage);
}

}