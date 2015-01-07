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
        /**
         * Create a new ViewController.
         */
		CREATE_FUNC(ViewController);

        /**
         * ViewController destructor.
         */
		virtual ~ViewController();

        /**
         * Do sth when you load this view controller.
         */
		virtual void load();
        /**
         * Do sth when you unload this view controller.
         */
		virtual void unload();

        /**
         * Get the related GameScene object of this controller.
         */
		CC_SYNTHESIZE(GameScene*, _scene, Scene);
        
    protected:
		virtual bool init();
	};

}

#endif