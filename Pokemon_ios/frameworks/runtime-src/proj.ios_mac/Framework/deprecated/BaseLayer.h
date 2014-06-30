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

		virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
		virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
		virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
		virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
	protected:
		BaseLayer();
		virtual ~BaseLayer();

		bool _isEnabled;
	};
}

#endif