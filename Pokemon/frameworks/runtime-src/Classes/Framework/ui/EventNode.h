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

typedef std::function<void(cocos2d::Ref*)> TouchCallback;
typedef std::function<void(cocos2d::Ref*, cocos2d::EventKeyboard::KeyCode)> KeyboardCallback;

#define TOUCH_EVENT_CALLBACK(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, ##__VA_ARGS__)
#define KEYBOARD_EVENT_CALLBACK(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)

#define SAFE_SET_VISIBILITY(__node__, __value__) \
	if (__node__) { \
		__node__->setVisible(__value__); \
	} \

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

	inline void setTouchCallback(TouchCallback callback)
	{
		this->_touchCallback = callback;
	}
	inline void setKeyboardCallback(KeyboardCallback callback)
	{
		this->_keyboardCallback = callback;
	}
	/*
	inline void setScriptTouchCallback(TouchCallback scriptCallback)
	{
		this->_scriptTouchCallback = scriptCallback;
	}
	inline void setScriptKeyboardCallback(KeyboardCallback scriptCallback)
	{
		this->_scriptKeyboardCallback = scriptCallback;
	}
	*/

	cocos2d::Rect rect() const;
protected:
	EventNode();
	virtual ~EventNode();

	virtual void onTouch(cocos2d::Ref *pSender);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	virtual void onKeyPressed(cocos2d::Ref *pSender, cocos2d::EventKeyboard::KeyCode keyCode);
#endif
	virtual void updateImageVisibility();

	bool _isEnabled;
	bool _isSelected;
	unsigned int _tabIndex;
	cocos2d::Node *_defaultImage;
	cocos2d::Node *_selectedImage;
	cocos2d::Node *_disabledImage;
	// cpp callback
	TouchCallback _touchCallback;
	KeyboardCallback _keyboardCallback;
	/*
	// lua callback
	TouchCallback _scriptTouchCallback;
	KeyboardCallback _scriptKeyboardCallback;
	*/
};

}

#endif