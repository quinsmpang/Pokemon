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
        /**
         * Create a CoreLayer.
         */
		CREATE_FUNC(CoreLayer);

        /**
         * CoreLayer constructor.
         */
		CoreLayer();
        /**
         * CoreLayer destructor.
         */
		virtual ~CoreLayer();

        /**
         * Push a new layer into the current scene.
         *
         * @param topLayer The new layer to push into.
         */
		void pushLayer(GameLayer *topLayer);
        /**
         * Pop out the top layer of the current scene.
         */
		void popLayer();

        /**
         * Get the top game layer.
         *
         * @return Current top game layer.
         */
		GameLayer *getTopLayer();

	protected:
		virtual bool init();
        
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