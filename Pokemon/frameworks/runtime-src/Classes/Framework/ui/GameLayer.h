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
        /**
         * Create a GameLayer.
         */
		CREATE_FUNC(GameLayer);

        /**
         * GameLayer constructor.
         */
		GameLayer();
        /**
         * GameLayer destructor.
         */
		virtual ~GameLayer();

        /**
         * Create a GameLayer, which would play the specified actions when push or pop.
         *
         * @param comeInWhenPushAction Come in action when pushed into the scene.
         * @param comeInWhenPopAction Come out action when the top layer is popped.
         * @param goOutWhenPushAction Go out action of the last top layer when push a new game layer.
         * @param goOutWhenPopAction Go out action of the popped game layer.
         *
         * @return Return a GameLayer.
         */
		static GameLayer *createWithTransitions(cocos2d::ActionInterval *comeInWhenPushAction, cocos2d::ActionInterval *comeInWhenPopAction, cocos2d::ActionInterval *goOutWhenPushAction, cocos2d::ActionInterval *goOutWhenPopAction);

		CC_SYNTHESIZE(cocos2d::ActionInterval*, _comeInWhenPushAction, ComeInWhenPushAction);
		CC_SYNTHESIZE(cocos2d::ActionInterval*, _comeInWhenPopAction, ComeInWhenPopAction);
		CC_SYNTHESIZE(cocos2d::ActionInterval*, _goOutWhenPushAction, GoOutWhenPushAction);
		CC_SYNTHESIZE(cocos2d::ActionInterval*, _goOutWhenPopAction, GoOutWhenPopAction);

        /**
         * Whether the game layer is still in action.
         *
         * @return Whether the game layer is in action.
         */
		inline bool isShown()
		{
			return this->_isShown;
		}

        /**
         * Touch events overrides.
         */
		virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;

	protected:
		virtual bool init();

		cocos2d::Size _winSize;
		bool _isShown;
	};

}

#endif