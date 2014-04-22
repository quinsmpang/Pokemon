#include "TextBlock.h"

using namespace cocos2d;

namespace framework
{

TextBlock *TextBlock::create(const std::string &szContent, const std::string &szFontName, int fontSize, TouchCallback touchCallback, KeyboardCallback keyboardCallback)
{
	auto pBlock = new TextBlock();

	if (pBlock && pBlock->initWithString(szContent, szFontName, fontSize, touchCallback, keyboardCallback))
	{
		pBlock->autorelease();

		return pBlock;
	}

	return nullptr;
}

bool TextBlock::initWithString(const std::string &szContent, const std::string &szFontName, int fontSize, TouchCallback touchCallback, KeyboardCallback keyboardCallback)
{
	if (!EventNode::init())
	{
		return false;
	}

	_defaultImage = Label::create(szContent, szFontName, fontSize);
	_defaultImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	_selectedImage = Label::create(szContent, szFontName, fontSize);
	_selectedImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	_disabledImage = Label::create(szContent, szFontName, fontSize);
	_disabledImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	_selectedImage->setVisible(false);
	_disabledImage->setVisible(false);
	
	CC_SAFE_RETAIN(_defaultImage);
	CC_SAFE_RETAIN(_selectedImage);
	CC_SAFE_RETAIN(_disabledImage);

	this->setContentSize(_defaultImage->getContentSize());
	this->setAnchorPoint(Point::ANCHOR_MIDDLE);

	this->addChild(_defaultImage);
	this->addChild(_selectedImage);
	this->addChild(_disabledImage);

	this->_touchCallback = touchCallback;
	this->_keyboardCallback = keyboardCallback;

	return true;
}

void TextBlock::setDefaultColor(Color3B color)
{
	this->_defaultImage->setColor(color);
}

void TextBlock::setSelectedColor(Color3B color)
{
	this->_selectedImage->setColor(color);
}

void TextBlock::setDisabledColor(Color3B color)
{
	this->_disabledImage->setColor(color);
}

TextBlock::~TextBlock()
{
}

}