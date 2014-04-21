#include "EventNode.h"

using namespace cocos2d;

namespace framework
{

/*********************public functions*********************/
bool EventNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void EventNode::setEnabled(bool isEnabled)
{
	if (this->_isEnabled != isEnabled)
	{
		this->removeAllChildren();
		if (isEnabled)
		{
			this->addChild(_defaultImage);
		}
		else
		{
			this->addChild(_disabledImage);
		}
	}
	this->_isEnabled = isEnabled;
}

void EventNode::setSelected(bool isSelected)
{
	if (this->_isSelected != isSelected)
	{
		this->removeAllChildren();
		if (isSelected)
		{
			this->addChild(_selectedImage);
		}
		else
		{
			this->addChild(_defaultImage);
		}
	}
	this->_isSelected = isSelected;
}

void EventNode::onTouch(void *pParam)
{
	CCASSERT(false, "override me");
}

void EventNode::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, void *pParam)
{
	CCASSERT(false, "override me");
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
	if (this->_defaultImage)
	{
		CC_SAFE_RELEASE_NULL(_defaultImage);
	}
}

}