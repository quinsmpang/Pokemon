/******************************
Description: Run a path with parabola.
Author: M.Wan
Date: 02/10/2015
******************************/

#ifndef __ACTIONS_ACTIONPARABOLA__
#define __ACTIONS_ACTIONPARABOLA__

#include "cocos2d.h"

namespace framework
{
	class ActionParabola : public cocos2d::ActionInterval
	{
	public:
		/**
		* Create parabola path action with formula: y = a * (x - h) ^ 2 + k.
		*
		* @param a Coefficient, it affects the expansion of the parabola.
		* @param h Top point's x-axis value.
		* @param k Top point's y-axis value.
		* @param x1, Start position x.
		* @param x2, End position x.
		*/
		static ActionParabola *create(float duration, float a, float h, float k, float x1, float x2);

		/**
		* Overrides
		*/
		virtual ActionParabola* clone() const override;
		virtual ActionParabola* reverse(void) const  override;
		virtual void startWithTarget(cocos2d::Node *target) override;
		virtual void update(float time) override;

	protected:
		bool init(float duration, float a, float h, float k, float x1, float x2);

		float _a, _h, _k;
		float _x1, _x2;
		float _perimeter;
		cocos2d::Point _startPosition;
		cocos2d::Point _previousPosition;
	};
}

#endif