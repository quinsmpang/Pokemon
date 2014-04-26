/******************************
Description: Base layer in the framework, all framework layers should extend this class
Author: M.Wan
Date: 4/26/2014
******************************/

#ifndef __UI_BASELAYER__
#define __UI_BASELAYER__

#include "cocos2d.h"

namespace framework
{
	class BaseLayer : public cocos2d::Layer
	{
	public:
		virtual inline bool isEnabled()
		{
			return this->_isEnabled;
		}
		virtual void setEnabled(bool isEnabled);

		virtual bool init();

		/* touch events */
		virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
		virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
		virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
		virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		/* keyboard events */
		virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent);
		virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent);
#endif

	protected:
		BaseLayer();
		virtual ~BaseLayer();

		bool _isEnabled;

		cocos2d::EventListenerTouchOneByOne *_touchListener;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		cocos2d::EventListenerKeyboard *_keyboardListener;
#endif
	};
}

#endif