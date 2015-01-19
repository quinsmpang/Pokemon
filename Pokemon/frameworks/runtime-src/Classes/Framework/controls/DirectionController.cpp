#include "DirectionController.h"
#include <new>
#include <functional>

using namespace cocos2d;
using namespace std;

namespace framework
{
    DirectionController::DirectionController()
        : _bg(nullptr)
        , _rocker(nullptr)
        , _touchListener(nullptr)
        , _isEnabled(true)
        , _controlDelegate(nullptr)
        , _radius(0.0)
        , _pressed(false)
        , _touchPos(Point::ZERO)
    {
    }
    
    DirectionController::~DirectionController()
    {
        if (_controlDelegate) {
            delete _controlDelegate;
        }
    }
    
    DirectionController *DirectionController::create(const std::string &bgFile, const std::string &rockerFile)
    {
        auto controller = new (nothrow) DirectionController();
        if (controller && controller->init(bgFile, rockerFile)) {
            controller->autorelease();
            return controller;
        }
        CC_SAFE_RELEASE(controller);
        return nullptr;
    }
    
    DirectionController *DirectionController::create(cocos2d::Node *bgNode, cocos2d::Node *rockerNode)
    {
        auto controller = new (nothrow) DirectionController();
        if (controller && controller->init(bgNode, rockerNode)) {
            controller->autorelease();
            return controller;
        }
        CC_SAFE_RELEASE(controller);
        return nullptr;
    }
    
    bool DirectionController::init(const std::string &bgFile, const std::string &rockerFile)
    {
        CCASSERT(bgFile.size() > 0 && rockerFile.size() > 0, "params can't be empty string");
        
        auto bgNode = Sprite::create(bgFile);
        auto controllerNode = Sprite::create(rockerFile);
        return this->init(bgNode, controllerNode);
    }
    
    bool DirectionController::init(cocos2d::Node *bgNode, cocos2d::Node *rockerNode)
    {
        CCASSERT(bgNode && rockerNode, "params can't be null");
        
        _bg = bgNode;
		_rocker = rockerNode;
        
        this->setContentSize(_bg->getContentSize());
        _bg->setAnchorPoint(Point(0.5, 0.5));
		_rocker->setAnchorPoint(Point(0.5, 0.5));
        // radius is set to the half of the min border size of the bg node.
        float min = MIN(_bg->getContentSize().width, _bg->getContentSize().height);
        _radius = min * 0.5;
        
        _bg->setPosition(this->getContentSize().width * 0.5, this->getContentSize().height * 0.5);
		_rocker->setPosition(_bg->getPosition());
        this->addChild(_bg);
		this->addChild(_rocker);
        this->setAnchorPoint(Point(0.5, 0.5));
        
        // register touch events
        _touchListener = EventListenerTouchOneByOne::create();
        _touchListener->setSwallowTouches(true);
        _touchListener->onTouchBegan = std::bind(&DirectionController::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
        _touchListener->onTouchMoved = std::bind(&DirectionController::onTouchMoved, this, std::placeholders::_1, std::placeholders::_2);
        _touchListener->onTouchEnded = std::bind(&DirectionController::onTouchEnded, this, std::placeholders::_1, std::placeholders::_2);
        _touchListener->onTouchCancelled = std::bind(&DirectionController::onTouchCancelled, this, std::placeholders::_1, std::placeholders::_2);
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
        
        return true;
    }
    
    bool DirectionController::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
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
        Point relativeLoc = this->convertToNodeSpace(loc);
		if (_rocker->getBoundingBox().containsPoint(relativeLoc)) {
            _pressed = true;
            _touchPos = loc;
            return true;
        }
        return false;
    }
    
    void DirectionController::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
    {
        CC_UNUSED_PARAM(unused_event);
        
        if (_pressed) {
            Point loc = touch->getLocation();
            Point vec = Point(loc.x - _touchPos.x, loc.y - _touchPos.y);
            Point exactPos = Point(this->getContentSize().width * 0.5 + vec.x, this->getContentSize().height * 0.5 + vec.y);
            // check whether the current position is out of the limited circle.
            float moduleSq = vec.x * vec.x + vec.y * vec.y;
            if (moduleSq > _radius * _radius) {
                float module = sqrt(moduleSq);
                exactPos.x = _radius * vec.x / module + this->getContentSize().width * 0.5;
                exactPos.y = _radius * vec.y / module + this->getContentSize().height * 0.5;
            }
			_rocker->setPosition(exactPos);     // update controller node position
            
            if (_controlDelegate) {
                float responseModule = this->_radius * 0.5;     // response radius condition
                if (moduleSq >= responseModule * responseModule) {
                    if (abs(vec.x) >= abs(vec.y)) {
                        if (vec.x > 0) {
                            // on right
                            _controlDelegate->onControlToRight(this);
                        } else {
                            // on left
                            _controlDelegate->onControlToLeft(this);
                        }
                    } else {
                        if (vec.y > 0) {
                            // on up
                            _controlDelegate->onControlToUp(this);
                        } else {
                            // on down
                            _controlDelegate->onControlToDown(this);
                        }
                    }
                } else {
                    _controlDelegate->onControlStop(this);
                }
            }
        }
    }
    
    void DirectionController::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
    {
        CC_UNUSED_PARAM(unused_event);
        
        _pressed = false;
        _touchPos = Point::ZERO;
        // move the controller to the origin
        auto pAction = EaseIn::create(MoveTo::create(0.1, Point(this->getContentSize().width * 0.5, this->getContentSize().height * 0.5)), 2);
		_rocker->runAction(pAction);
        
        if (_controlDelegate) {
            _controlDelegate->onControlStop(this);
        }
    }

	void DirectionController::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
	{
		CC_UNUSED_PARAM(unused_event);

		_pressed = false;
		_touchPos = Point::ZERO;
		// move the controller to the origin
		auto pAction = EaseIn::create(MoveTo::create(0.1, Point(this->getContentSize().width * 0.5, this->getContentSize().height * 0.5)), 2);
		_rocker->runAction(pAction);
        
        if (_controlDelegate) {
            _controlDelegate->onControlStop(this);
        }
	}
}