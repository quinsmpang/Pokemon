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
public:
	CREATE_FUNC(EventNode);

	virtual bool init();

	virtual void onTouch(void *pParam);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, void *pParam);
	
	inline bool getEnabled()
	{
		return _isEnabled;
	}
	void setEnabled(bool isEnabled);
	inline bool getSelected()
	{
		return _isSelected;
	}
	void setSelected(bool isSelected);
protected:
	EventNode();
	~EventNode();

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