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

	class GameLayer : public cocos2d::Layer
	{
	public:
		CREATE_FUNC(GameLayer);

		inline bool isEnabled()
		{
			return _isEnabled;
		}
		void setEnabled(bool isEnabled)
		{
			_isEnabled = isEnabled;
		}

		/* touch events */
		virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
		virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
		virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); 
		virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	protected:
		GameLayer();
		virtual ~GameLayer();

		bool _isEnabled;
	};

}

#endif