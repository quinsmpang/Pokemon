/******************************
	Description: Game base layer
	Author: M.Wan
	Date: 4/20/2014
******************************/

#ifndef __UI_GAMELAYER__
#define __UI_GAMELAYER__

#include "cocos2d.h"
#include "ui/TouchableNode.h"

namespace framework
{

class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();

	virtual bool init();

	CREATE_FUNC(GameLayer);

	CC_SYNTHESIZE(bool, _isEnabled, Enabled);

	// push new layer into the stack
	void push(GameLayer *pLayer);
	// pop current layer
	void pop();

	bool isCoreLayer();

	virtual void onEnter() override;
	virtual void onExit() override;

	void registerTouchEvents();
	void registerKeyboardEvents();

	/* touch events */
	virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
    virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
    virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
    virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;

	/* keyboard events */
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent) override;
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent) override;
protected:
	~GameLayer();
	// the pointer to the parent layer, if it is null, then this layer is the core layer.
	GameLayer *_parentLayer;
	// focused node
	TouchableNode *_focusNode;
};

}

#endif