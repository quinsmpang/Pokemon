/******************************
 Description: Circle control which is used to control directions
 Author: M.Wan
 Date: 12/30/2014
 ******************************/

#ifndef __CONTROL_DIRECTIONCONTROLLER__
#define __CONTROL_DIRECTIONCONTROLLER__

#include "cocos2d.h"
#include <string>

namespace framework
{
    class DirectionController;
    
    class DirectionControllerDelegate
    {
    public:
        virtual ~DirectionControllerDelegate() {}
        
        // direction response events
        virtual void onControlToRight(DirectionController *sender) = 0;
        virtual void onControlToLeft(DirectionController *sender) = 0;
        virtual void onControlToUp(DirectionController *sender) = 0;
        virtual void onControlToDown(DirectionController *sender) = 0;
        virtual void onControlStop(DirectionController *sender) = 0;
    };
    
    class DirectionController : public cocos2d::Node
    {
    public:
        // touch area radius will be set to the half of the value, which is the min one between the width and height of the content size of bg node.
        static DirectionController *create(const std::string &bgFile, const std::string &rockerFile);
        static DirectionController *create(cocos2d::Node *bgNode, cocos2d::Node *rockerNode);
        
        DirectionController();
        virtual ~DirectionController();
        
        inline void setTouchRadius(float radius)
        {
            _radius = radius;
        }
        
        inline void setControllerDelegate(DirectionControllerDelegate *controlDelegate)
        {
            _controlDelegate = controlDelegate;
        }
        
        inline bool isEnabled() const
        {
            return _isEnabled;
        }
        inline void setEnabled(bool isEnabled)
        {
            _isEnabled = isEnabled;
        }
        
        // override touch events
        virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        
    protected:
        virtual bool init(const std::string &bgFile, const std::string &controllerFile);
        virtual bool init(cocos2d::Node *bgNode, cocos2d::Node *controllerNode);
        
        cocos2d::Node *_bg;
        cocos2d::Node *_rocker;
        
        cocos2d::EventListenerTouchOneByOne *_touchListener;
        bool _isEnabled;
        
        DirectionControllerDelegate *_controlDelegate;      // direction response delegate
        
        // control variables
        float _radius;         // controller movement range
        bool _pressed;
        cocos2d::Point _touchPos;   // touch position
    };
}

#endif /* defined(__CONTROL_DIRECTIONCONTROLLER__) */
