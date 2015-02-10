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
		* Overrides
		*/
		virtual ActionParabola* clone() const override;
		virtual ActionParabola* reverse(void) const  override;
		virtual void startWithTarget(Node *target) override;
		virtual void update(float time) override;
	};
}

#endif