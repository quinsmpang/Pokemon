/******************************
Description: Game base layer
Author: M.Wan
Date: 4/20/2014
******************************/

#ifndef __UI_GAMELAYER__
#define __UI_GAMELAYER__

#include "cocos2d.h"

namespace framework
{
	class Win32EventListener;

	class GameLayer : public cocos2d::Layer
	{
		friend class CoreLayer;
	public:
		CREATE_FUNC(GameLayer);

		virtual bool init();

		static GameLayer *createWithTransitions(cocos2d::ActionInterval *comeInWhenPushAction, cocos2d::ActionInterval *comeInWhenPopAction, cocos2d::ActionInterval *goOutWhenPushAction, cocos2d::ActionInterval *goOutWhenPopAction);

		// Action when push into the core layer.
		CC_SYNTHESIZE(cocos2d::ActionInterval*, _comeInWhenPushAction, ComeInWhenPushAction);
		// Action when the top layer is popped.
		CC_SYNTHESIZE(cocos2d::ActionInterval*, _comeInWhenPopAction, ComeInWhenPopAction);
		// Action when a new layer is pushed into the core layer.
		CC_SYNTHESIZE(cocos2d::ActionInterval*, _goOutWhenPushAction, GoOutWhenPushAction);
		// Action when the popped. 
		CC_SYNTHESIZE(cocos2d::ActionInterval*, _goOutWhenPopAction, GoOutWhenPopAction);

		inline bool isShown()
		{
			return this->_isShown;
		}

		virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;

	protected:
		GameLayer();
		virtual ~GameLayer();

		cocos2d::Size _winSize;
		bool _isShown;
	};

}

#endif