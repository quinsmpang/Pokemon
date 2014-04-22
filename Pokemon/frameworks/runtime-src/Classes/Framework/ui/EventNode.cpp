#include "EventNode.h"

using namespace cocos2d;

namespace framework
{

/*********************public functions*********************/
void EventNode::setEnabled(bool isEnabled)
{
	this->_isEnabled = isEnabled;
	this->updateImageVisibility();
}

void EventNode::setSelected(bool isSelected)
{
	this->_isSelected = isSelected;
	this->updateImageVisibility();
}

void EventNode::focus()
{
	if (!this->_isEnabled)
		return;

	SAFE_SET_VISIBILITY(this->_selectedImage, true);
	SAFE_SET_VISIBILITY(this->_defaultImage, false);
}

void EventNode::blur()
{
	if (!this->_isEnabled)
		return;

	SAFE_SET_VISIBILITY(this->_selectedImage, false);
	SAFE_SET_VISIBILITY(this->_defaultImage, true);
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

void EventNode::onTouch(cocos2d::Ref *pSender)
{
	if (this->_touchCallback)
	{
		this->_touchCallback(this);
	}
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
void EventNode::onKeyPressed(cocos2d::Ref *pSender, cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (this->_keyboardCallback)
	{
		this->_keyboardCallback(this, keyCode);
	}
}
#endif

void EventNode::updateImageVisibility()
{
	if (this->_isEnabled)
	{
		SAFE_SET_VISIBILITY(_disabledImage, false);
		if (this->_isSelected)
		{
			SAFE_SET_VISIBILITY(_selectedImage, true);
			SAFE_SET_VISIBILITY(_defaultImage, false);
		}
		else
		{
			SAFE_SET_VISIBILITY(_selectedImage, false);
			SAFE_SET_VISIBILITY(_defaultImage, true);
		}
	}
	else
	{
		SAFE_SET_VISIBILITY(_defaultImage, false);
		SAFE_SET_VISIBILITY(_selectedImage, false);
		SAFE_SET_VISIBILITY(_disabledImage, true);
	}
}

}