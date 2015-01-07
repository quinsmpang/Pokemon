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
        /**
         * Create a new ListMenuItem object.
         */
		CREATE_FUNC(ListMenuItem);

        /**
         * ListMenuItem constructor.
         */
		ListMenuItem();
        /**
         * ListMenuItem destructor.
         */
		virtual ~ListMenuItem();

        /**
         * Shown index of the item getter and setter.
         */
		CC_SYNTHESIZE(ssize_t, _showIndex, ShowIndex);

        /**
         * Reset the menu item as unused.
         */
		void reset();
	};
}

#endif