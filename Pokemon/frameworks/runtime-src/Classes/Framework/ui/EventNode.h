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

typedef std::function<void(void*)> TouchCallback;
typedef std::function<void(cocos2d::EventKeyboard::KeyCode, void*)> KeyboardCallback;

#define TOUCH_EVENT_CALLBACK(__selector__, __target__, ...) std::bind(&__selector__, __target__, ##__VA_ARGS__)
#define KEYBOARD_EVENT_CALLBACK(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, ##__VA_ARGS__)

class EventNode : public cocos2d::Node
{
	friend class EventLayer;
public:
	CREATE_FUNC(EventNode);

	virtual bool init();
	
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

	cocos2d::Rect rect() const;
protected:
	EventNode();
	virtual ~EventNode();

	virtual void onTouch(void *pParam);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, void *pParam);

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