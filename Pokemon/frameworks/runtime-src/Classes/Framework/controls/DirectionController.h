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
        /**
         * DirectionControllerDelegate destructor.
         */
        virtual ~DirectionControllerDelegate() {}
        
        /**
         * The callback when you response right event.
         *
         * @param sender Sender.
         */
        virtual void onControlToRight(DirectionController *sender) = 0;
        /**
         * The callback when you response left event.
         *
         * @param sender Sender.
         */
        virtual void onControlToLeft(DirectionController *sender) = 0;
        /**
         * The callback when you response up event.
         *
         * @param sender Sender.
         */
        virtual void onControlToUp(DirectionController *sender) = 0;
        /**
         * The callback when you response down event.
         *
         * @param sender Sender.
         */
        virtual void onControlToDown(DirectionController *sender) = 0;
        /**
         * The callback when you stop controlling.
         *
         * @param sender Sender.
         */
        virtual void onControlStop(DirectionController *sender) = 0;
    };
    
    class DirectionController : public cocos2d::Node
    {
    public:
        /**
         * @brief Create a DirectionController control.
         * Touch area radius will be set to the half of the value, which is the min one between the width and height of the content size of bg node.
         *
         * @param bgFile Background file path.
         * @param rockerFile Rocker file path.
         *
         * @return Return a new DirectionController object.
         */
        static DirectionController *create(const std::string &bgFile, const std::string &rockerFile);
        /**
         * @brief Create a DirectionController control.
         * Touch area radius will be set to the half of the value, which is the min one between the width and height of the content size of bg node.
         *
         * @param bgNode Background node.
         * @param rockerNode Rocker node.
         *
         * @return Return a new DirectionController object.
         */
        static DirectionController *create(cocos2d::Node *bgNode, cocos2d::Node *rockerNode);
        
        /**
         * DirectionController constructor.
         */
        DirectionController();
        /**
         * DirectionController destructor.
         */
        virtual ~DirectionController();
        
        /**
         * Set the boundary from the center of control.
         *
         * @param radius Available circle radius.
         */
        inline void setTouchRadius(float radius)
        {
            _radius = radius;
        }
        /**
         * Set the delegate of the control.
         *
         * @param controlDelegate Control delegate.
         */
        inline void setControllerDelegate(DirectionControllerDelegate *controlDelegate)
        {
            _controlDelegate = controlDelegate;
        }
        
        /**
         * Whether the control is enabled.
         *
         * @return A boolean value.
         */
        inline bool isEnabled() const
        {
            return _isEnabled;
        }
        /**
         * Whether to enable the control.
         *
         * @param isEnabled A boolean value.
         */
        inline void setEnabled(bool isEnabled)
        {
            _isEnabled = isEnabled;
        }
        
        /**
         * Touch events.
         */
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
