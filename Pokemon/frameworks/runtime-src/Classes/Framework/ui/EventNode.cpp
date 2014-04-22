#include "EventNode.h"

using namespace cocos2d;

namespace framework
{

/*********************public functions*********************/
void EventNode::setEnabled(bool isEnabled)
{
	if (this->_isEnabled != isEnabled)
	{
		this->_selectedImage->setVisible(false);
		this->_defaultImage->setVisible(!isEnabled);
		this->_disabledImage->setVisible(isEnabled);
	}
	this->_isEnabled = isEnabled;
}

void EventNode::setSelected(bool isSelected)
{
	if (!this->_isEnabled)
	{
		return;
	}
	if (this->_isSelected != isSelected)
	{
		this->_selectedImage->setVisible(isSelected);
		this->_defaultImage->setVisible(!isSelected);
		this->_disabledImage->setVisible(false);
	}
	this->_isSelected = isSelected;
}

Rect EventNode::rect() const
{
    return Rect( _position.x - _contentSize.width * _anchorPoint.x,
                      _position.y - _contentSize.height * _anchorPoint.y,
                      _contentSize.width, _contentSize.height);
}

/*********************private functions*********************/
EventNode::EventNode()
	: _tabIndex(0)
	, _defaultImage(nullptr)
	, _selectedImage(nullptr)
	, _disabledImage(nullptr)
	, _touchCallback(nullptr)
	, _keyboardCallback(nullptr)
{
}

EventNode::~EventNode()
{
	CC_SAFE_RELEASE_NULL(_defaultImage);
	CC_SAFE_RELEASE_NULL(_selectedImage);
	CC_SAFE_RELEASE_NULL(_disabledImage);
}

void EventNode::onTouch(void *pParam)
{
	if (this->_touchCallback)
	{
		this->_touchCallback(pParam);
	}
}

void EventNode::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, void *pParam)
{
	if (this->_keyboardCallback)
	{
		this->_keyboardCallback(keyCode, pParam);
	}
}

}