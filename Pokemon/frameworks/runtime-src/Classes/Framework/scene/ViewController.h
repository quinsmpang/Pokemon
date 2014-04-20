/******************************
	Description: ViewController base class
	Author: M.Wan
	Date: 4/17/2014
******************************/

#ifndef __SCENE_VIEWCONTROLLER__
#define __SCENE_VIEWCONTROLLER__

#include "cocos2d.h"

namespace framework
{

class GameScene;

class ViewController : public cocos2d::Ref
{
public:
	CREATE_FUNC(ViewController);

	virtual ~ViewController();

	virtual bool init();

	virtual void load();

	virtual void unload();

	CC_SYNTHESIZE(GameScene*, _scene, Scene);
};

}

#endif