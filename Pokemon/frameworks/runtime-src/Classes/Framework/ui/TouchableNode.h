/******************************
	Description: The base node which supports touch
	Author: M.Wan
	Date: 4/19/2014
******************************/

#ifndef __UI_TOUCHABLENODE__
#define __UI_TOUCHABLENODE__

#include "cocos2d.h"

namespace framework
{

typedef void (*TouchCallback)(void*);

class TouchableNode : public cocos2d::Node
{
public:
	CREATE_FUNC(TouchableNode);

	virtual bool init();

	virtual void onTouch(void *pParam);
	
	CC_SYNTHESIZE(bool, _isEnabled, Enabled);
protected:
	TouchableNode();
	~TouchableNode();

	cocos2d::Node *_defaultImage;
	TouchCallback _callback;
};

}

#endif