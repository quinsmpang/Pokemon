/******************************
Description: Game base layer
Author: M.Wan
Date: 4/20/2014
******************************/

#ifndef __UI_GAMELAYER__
#define __UI_GAMELAYER__

#include "cocos2d.h"
#include "EventLayer.h"
#include "BaseLayer.h"
#include "EventNode.h"

namespace framework
{

	class GameLayer : public BaseLayer
	{
	public:
		GameLayer();

		virtual bool init();

		CREATE_FUNC(GameLayer);

		void setEventLayer(EventLayer *pLayer);

		void setEnabled(bool isEnabled) override;

		virtual void addControl(EventNode *pControl);
		virtual void addControlByTag(EventNode *pControl, int tag);
		virtual void removeControl(EventNode *pControl);
		virtual void removeControlByTag(int tag, bool cleanup = true);

		virtual EventNode *getFocusNode();
		virtual void setFocusNode(EventNode *pNode);

		virtual void onEnter() override;
		virtual void onExit() override;

		virtual void addChild(cocos2d::Node *child);
		virtual void addChild(cocos2d::Node *child, int localZOrder);
		virtual void addChild(cocos2d::Node *child, int localZOrder, int tag);

		void registerTouchEvents();
		void unregisterTouchEvents();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		void registerKeyboardEvents();
		void unregisterKeyboardEvents();
#endif
	protected:
		~GameLayer();
		// touch layer, to storage touchable nodes
		EventLayer *_eventLayer;
	};

}

#endif