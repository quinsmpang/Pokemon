/******************************
Description: Core layer to manage layer stack, one GameScene should only contain one CoreLayer
Author: M.Wan
Date: 4/26/2014
******************************/

#ifndef __UI_CORELAYER__
#define __UI_CORELAYER__

#include "cocos2d.h"
#include "../containers/Stack.h"
#include "GameLayer.h"

namespace framework
{
	class CoreLayer : public GameLayer
	{
	public:
		CREATE_FUNC(CoreLayer);

		virtual bool init();

		void pushLayer(BaseLayer *topLayer);

		void popLayer();

		BaseLayer *getTopLayer();

	protected:
		CoreLayer();
		virtual ~CoreLayer();

		Stack *_layers;
	};
}

#endif