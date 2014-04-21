/******************************
	Description: The base node which supports touch
	Author: M.Wan
	Date: 4/19/2014
******************************/

#ifndef __UI_EVENTNODE__
#define __UI_EVENTNODE__

#include "cocos2d.h"

namespace framework
{

typedef void (*TouchCallback)(void*);
typedef void (*KeyboardCallback)(cocos2d::EventKeyboard::KeyCode, void*);

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