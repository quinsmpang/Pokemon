/******************************
	Description: Event layer, to deal with touch and keyboard events
	Author: M.Wan
	Date: 4/21/2014
******************************/

#ifndef __UI_EVENTLAYER_H__
#define __UI_EVENTLAYER_H__

#include "cocos2d.h"
#include "EventNode.h"

namespace framework
{

/* use as internal class in GameLayer */
class EventLayer : public cocos2d::Layer
{

enum class State
{
	Waiting,
	Tracking,
};

public:
	EventLayer();

	CREATE_FUNC(EventLayer);

	virtual bool init();

	inline void enableTouch()
	{
		this->_isTouchEnabled = true;
	}
	inline void disableTouch()
	{
		this->_isTouchEnabled = false;
	}
	inline void enableKeyboard()
	{
		this->_isKeyboardEnabled = true;
	}
	inline void disableKeyboard()
	{
		this->_isKeyboardEnabled = false;
	}
	
	/* touch events */
	virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
    virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
    virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
    virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	/* keyboard events */
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent);
protected:
	~EventLayer();
	EventNode *getNodeForTouch(cocos2d::Touch *pTouch);

	EventNode *_focusNode;	// one layer can only have one focus node.
	State _state;
	bool _isTouchEnabled;
	bool _isKeyboardEnabled;
};

}

#endif