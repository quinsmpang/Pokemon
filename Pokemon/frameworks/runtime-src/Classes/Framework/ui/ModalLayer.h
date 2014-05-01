/******************************
Description: Modal layer, which swallows all events below the layer.
Author: M.Wan
Date: 5/1/2014
******************************/

#ifndef __UI_MODALLAYER__
#define __UI_MODALLAYER__

#include "cocos2d.h"

namespace framework
{
	class ModalLayer : public cocos2d::LayerColor
	{
	public:
		static ModalLayer *create();

		virtual bool init();

		virtual void onEnter();

		virtual void onExit();
	};
}

#endif