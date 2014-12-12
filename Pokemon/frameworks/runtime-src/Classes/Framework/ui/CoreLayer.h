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

		CoreLayer();
		virtual ~CoreLayer();

		virtual bool init();

		void pushLayer(GameLayer *topLayer);

		void popLayer();

		GameLayer *getTopLayer();

	protected:
		// The top layer goes out at first when push a new layer.
		virtual void topLayerDidGoOutWhenPush(GameLayer *newLayer);
		// New layer comes in.
		virtual void newLayerReadyToComeInWhenPush(GameLayer *newLayer);
		// The top layer goes out at first when pop.
		virtual void newLayerDidGoOutWhenPop();
		// The front layer comes in after pop.
		virtual void topLayerReadyToComeInWhenPop();

		Stack *_layers;
	};
}

#endif