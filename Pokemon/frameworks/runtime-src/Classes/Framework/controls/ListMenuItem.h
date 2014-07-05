/******************************
Description: List menu item.
Author: M.Wan
Date: 7/5/2014
******************************/

#ifndef __CONTROLS_LISTMENUITEM__
#define __CONTROLS_LISTMENUITEM__

#include "cocos2d.h"

namespace framework
{
	class ListMenuItem : public cocos2d::Node
	{
	public:
		static ssize_t INVALID_INDEX;
		CREATE_FUNC(ListMenuItem);

		ListMenuItem();
		virtual ~ListMenuItem();

		CC_SYNTHESIZE(ssize_t, _showIndex, ShowIndex);

		void reset();
	};
}

#endif