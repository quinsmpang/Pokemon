#include "CheckedButton.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace framework {
    CheckedButton::CheckedButton()
        : _checkedNode(nullptr)
        , _uncheckedNode(nullptr)
        , _isChecked(false)
        , _isEnabled(true)
        , _delegate(nullptr)
    {
    }
    
    CheckedButton::~CheckedButton()
    {
    }
    
    CheckedButton *CheckedButton::create(const std::string &checkedImgPath, const std::string &uncheckedImgPath)
    {
        auto pBtn = new (nothrow) CheckedButton();
        if (pBtn && pBtn->initWithFiles(checkedImgPath, uncheckedImgPath)) {
            pBtn->autorelease();
            return pBtn;
        }
        CC_SAFE_RELEASE_NULL(pBtn);
        return nullptr;
    }
    
    CheckedButton *CheckedButton::create(cocos2d::Node *checkedNode, cocos2d::Node *uncheckedNode)
    {
        auto pBtn = new (nothrow) CheckedButton();
        if (pBtn && pBtn->initWithNodes(checkedNode, uncheckedNode)) {
            pBtn->autorelease();
            return pBtn;
        }
        CC_SAFE_RELEASE_NULL(pBtn);
        return nullptr;
    }
    
    bool CheckedButton::initWithFiles(const std::string &checkedImgPath, const std::string &uncheckedImgPath)
    {
        if (!Node::init()) {
            return false;
        }
        auto pCheckedImg = Sprite::create(checkedImgPath);
        auto pUncheckedImg = Sprite::create(uncheckedImgPath);
        
        return this->initWithNodes(pCheckedImg, pUncheckedImg);
    }
    
    bool CheckedButton::initWithNodes(cocos2d::Node *checkedNode, cocos2d::Node *uncheckedNode)
    {
        checkedNode->setAnchorPoint(Point(0.5, 0.5));
        uncheckedNode->setAnchorPoint(Point(0.5, 0.5));
        auto checkedSize = checkedNode->getContentSize();
        auto uncheckedSize = uncheckedNode->getContentSize();
        Size fitSize = Size(MAX(checkedSize.width, uncheckedSize.width), MAX(checkedSize.height, uncheckedSize.height));
        this->setContentSize(fitSize);
        this->setAnchorPoint(Point(0.5, 0.5));
        checkedNode->setAnchorPoint(Point(0.5, 0.5));
        uncheckedNode->setAnchorPoint(Point(0.5, 0.5));
        checkedNode->setPosition(fitSize.width * 0.5, fitSize.height * 0.5);
        uncheckedNode->setPosition(fitSize.width * 0.5, fitSize.height * 0.5);
        this->addChild(uncheckedNode);
        this->addChild(checkedNode);
        uncheckedNode->setVisible(false);
        checkedNode->setVisible(false);
        _checkedNode = checkedNode;
        _uncheckedNode = uncheckedNode;
        
        // register touch events
        _touchListener = EventListenerTouchOneByOne::create();
        _touchListener->setSwallowTouches(true);
        _touchListener->onTouchBegan = std::bind(&CheckedButton::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
        _touchListener->onTouchMoved = std::bind(&CheckedButton::onTouchMoved, this, std::placeholders::_1, std::placeholders::_2);
        _touchListener->onTouchEnded = std::bind(&CheckedButton::onTouchEnded, this, std::placeholders::_1, std::placeholders::_2);
        _touchListener->onTouchCancelled = std::bind(&CheckedButton::onTouchCancelled, this, std::placeholders::_1, std::placeholders::_2);
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
        
        this->needUpdate();
        
        return true;
    }
    
    void CheckedButton::setChecked(bool isChecked)
    {
        _isChecked = isChecked;
        
        this->needUpdate();
    }
    
    void CheckedButton::needUpdate()
    {
        _checkedNode->setVisible(_isChecked);
        _uncheckedNode->setVisible(!_isChecked);
    }
    
    bool CheckedButton::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
    {
        CC_UNUSED_PARAM(unused_event);
        
        if (!_isEnabled) {
            return false;
        }
        
        for (Node *c = this->_parent; c; c = c->getParent())
        {
            if (!c->isVisible())
            {
                return false;
            }
        }
        
        Point loc = touch->getLocation();
		if (this->getBoundingBox().containsPoint(loc)) {
            return true;
        }
        return false;
    }
    
    void CheckedButton::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
    {
        CC_UNUSED_PARAM(unused_event);
    }
    
    void CheckedButton::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
    {
        CC_UNUSED_PARAM(unused_event);
        
        Point loc = touch->getLocation();
		if (this->getBoundingBox().containsPoint(loc)) {
            this->setChecked(!_isChecked);
            if (_delegate) {
                if (_isChecked) {
                    _delegate->onButtonChecked(this);
                } else {
                    _delegate->onButtonUnchecked(this);
                }
            }
        }
    }
    
    void CheckedButton::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
    {
        CC_UNUSED_PARAM(unused_event);
    }
}