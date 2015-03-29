/******************************
Description: Run a color fade action.
Author: M.Wan
Date: 03/29/2015
******************************/

#ifndef __ACTIONS_ACTIONCOLORTO__
#define __ACTIONS_ACTIONCOLORTO__

#include "cocos2d.h"

namespace framework
{
	class ActionColorTo : public cocos2d::ActionInterval
	{
	public:
		/**
		* Create color fade action.
		*
		* @param duration Action duration.
		* @param targetColor The final color to display.
		*/
		static ActionColorTo *create(float duration, const cocos2d::Color3B &targetColor);

		/**
		* Overrides
		*/
		virtual ActionColorTo *clone() const override;
		virtual ActionColorTo *reverse(void) const  override;
		virtual void startWithTarget(cocos2d::Node *target) override;
		virtual void update(float time) override;

	protected:
		bool init(float duration, const cocos2d::Color3B &targetColor);

		cocos2d::Color3B _targetColor;
		cocos2d::Color3B _deltaColor;
		cocos2d::Color3B _previousColor;
		cocos2d::Color3B _startColor;
	};
}

#endif