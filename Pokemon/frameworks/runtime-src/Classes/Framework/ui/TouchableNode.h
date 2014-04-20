/******************************
	Description: The base node which supports touch
	Author: M.Wan
	Date: 4/19/2014
******************************/

#ifndef __UI_TOUCHABLENODE__
#define __UI_TOUCHABLENODE__

#include "cocos2d.h"

namespace framework
{

class TouchableNode : public cocos2d::Node
{
public:
	TouchableNode();

	virtual ~TouchableNode();

	CREATE_FUNC(TouchableNode);

	virtual bool init();

	//void registerTouchEvents();
	//void unregisterTouchEvents();

	//void registerKeyboardEvents();
	//void unregisterKeyboardEvents();

	//// touch events
	//virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	//virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
 //   virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
 //   virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	//// keyboard events
	//virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* pEvent);
 //   virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* pEvent);
private:

};

}

#endif