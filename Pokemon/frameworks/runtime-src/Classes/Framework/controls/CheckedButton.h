/******************************
 Description: The button can be checked.
 Author: M.Wan
 Date: 1/16/2015
 ******************************/

#ifndef __CONTROL_CHECKEDBUTTON__
#define __CONTROL_CHECKEDBUTTON__

#include "cocos2d.h"
#include <string>

namespace framework {
    class CheckedButton;
    
    class CheckedButtonDelegate
    {
    public:
        /**
         * CheckedButtonDelegate destructor.
         */
        virtual ~CheckedButtonDelegate() {};
        
        /**
         * The callback when the button is checked.
         *
         * @param sender Sender
         */
        virtual void onButtonChecked(CheckedButton *sender) = 0;
        /**
         * The callback when the button is unchecked.
         *
         * @param sender Sender
         */
        virtual void onButtonUnchecked(CheckedButton *sender) = 0;
    };
    
    class CheckedButton : public cocos2d::Node
    {
    public:
        /**
         * Create a CheckedButton with two images.
         *
         * @param checkedImgPath The image path in checked state.
         * @param uncheckedImgPath The image path in unchecked state.
         *
         * @return Return a new CheckedButton object.
         */
        static CheckedButton *create(const std::string &checkedImgPath, const std::string &uncheckedImgPath);
        /**
         * Create a CheckedButton with two nodes.
         *
         * @param checkedNode The represent node in checked state.
         * @param uncheckedNode The represent node in unchecked state.
         *
         * @return Return a new CheckedButton object.
         */
        static CheckedButton *create(cocos2d::Node *checkedNode, cocos2d::Node *uncheckedNode);
        
        /**
         * CheckedButton constructor.
         */
        explicit CheckedButton();
        /**
         * CheckedButton destructor.
         */
        virtual ~CheckedButton();
        
        /**
         * Set button delegate.
         */
        inline void setDelegate(CheckedButtonDelegate *delegate)
        {
            _delegate = delegate;
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
         * Whether the control is in checked state.
         *
         * @return A boolean value.
         */
        inline bool isChecked() const
        {
            return _isChecked;
        }
        /**
         * Whether to check the control. Only update UI without delegate responses.
         *
         * @param isEnabled A boolean value.
         */
        void setChecked(bool isChecked);
        
        /**
         * Touch events.
         */
        virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        
    protected:
        bool initWithNodes(cocos2d::Node *checkedNode, cocos2d::Node *uncheckedNode);
        bool initWithFiles(const std::string &checkedImgPath, const std::string &uncheckedImgPath);
        
        void needUpdate();
        
        cocos2d::Node *_checkedNode;
        cocos2d::Node *_uncheckedNode;
        bool _isChecked;
        
        CheckedButtonDelegate *_delegate;
        
        cocos2d::EventListenerTouchOneByOne *_touchListener;
        bool _isEnabled;
    };
}

#endif /* defined(__CONTROL_CHECKEDBUTTON__) */
