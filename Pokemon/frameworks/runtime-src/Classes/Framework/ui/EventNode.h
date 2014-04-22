/******************************
	Description: The base node which supports touch
	Author: M.Wan
	Date: 4/19/2014
******************************/

#ifndef __UI_EVENTNODE__
#define __UI_EVENTNODE__

#include "cocos2d.h"
#include <functional>

namespace framework
{

typedef std::function<void(cocos2d::Ref*, void*)> TouchCallback;
typedef std::function<void(cocos2d::Ref*, cocos2d::EventKeyboard::KeyCode, void*)> KeyboardCallback;

#define TOUCH_EVENT_CALLBACK(__selector__, __target__) std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2)
#define KEYBOARD_EVENT_CALLBACK(__selector__, __target__) std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

class EventNode : public cocos2d::Node
{
	friend class EventLayer;
public:
	inline bool isEnabled()
	{
		return _isEnabled;
	}
	void setEnabled(bool isEnabled);
	inline bool isSelected()
	{
		return _isSelected;
	}
	void setSelected(bool isSelected);

	// to change the default behavior by rewriting these two methods on focus and blur.
	virtual void focus();
	virtual void blur();

	cocos2d::Rect rect() const;
protected:
	EventNode();
	virtual ~EventNode();

	virtual void onTouch(cocos2d::Ref *pSender, void *pParam);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	virtual void onKeyPressed(cocos2d::Ref *pSender, cocos2d::EventKeyboard::KeyCode keyCode, void *pParam);
#endif

	bool _isEnabled;
	bool _isSelected;
	unsigned int _tabIndex;
	cocos2d::Node *_defaultImage;
	cocos2d::Node *_selectedImage;
	cocos2d::Node *_disabledImage;
	TouchCallback _touchCallback;
	KeyboardCallback _keyboardCallback;
};

}

#endif