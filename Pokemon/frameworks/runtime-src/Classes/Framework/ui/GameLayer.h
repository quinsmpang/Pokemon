/******************************
	Description: Game base layer
	Author: M.Wan
	Date: 4/20/2014
******************************/

#ifndef __UI_GAMELAYER__
#define __UI_GAMELAYER__

#include "cocos2d.h"
#include "EventLayer.h"
#include "../ui/EventNode.h"

namespace framework
{

class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();

	virtual bool init();

	CREATE_FUNC(GameLayer);

	// push new layer into the stack
	void pushLayer(GameLayer *pLayer);
	// pop current layer
	void popLayer();

	bool isCoreLayer();
	GameLayer *getParentLayer();
	GameLayer *getCoreLayer();
	void setEventLayer(EventLayer *pLayer);

	virtual void addControl(EventNode *pControl);
	virtual void addControlByTag(EventNode *pControl, int tag);
	virtual void removeControl(EventNode *pControl);
	virtual void removeControlByTag(int tag, bool cleanup = true);

	virtual void setFocusNode(EventNode *pNode);

	virtual void onEnter() override;
	virtual void onExit() override;

	void registerTouchEvents();
	void unregisterTouchEvents();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	void registerKeyboardEvents();
	void unregisterKeyboardEvents();
#endif
protected:
	~GameLayer();
	// the pointer to the parent layer, if it is null, then this layer is the core layer.
	GameLayer *_parentLayer;
	// touch layer, to storage touchable nodes
	EventLayer *_eventLayer;

	cocos2d::EventListenerTouchOneByOne *_touchListener;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	cocos2d::EventListenerKeyboard *_keyboardListener;
#endif
};

}

#endif