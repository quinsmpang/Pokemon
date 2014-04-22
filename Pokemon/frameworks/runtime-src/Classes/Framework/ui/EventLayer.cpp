#include "EventLayer.h"

using namespace cocos2d;

namespace framework
{

EventLayer::EventLayer()
	: _focusNode(nullptr)
	, _state(State::Waiting)
	, _isTouchEnabled(true)
	, _isKeyboardEnabled(true)
{
}

bool EventLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Point(0.5f, 0.5f));
	this->setPosition(winSize.width * 0.5, winSize.height * 0.5);
	this->setContentSize(winSize);

	// register touch events
	auto pTouchListener = EventListenerTouchOneByOne::create();
	pTouchListener->onTouchBegan = CC_CALLBACK_2(EventLayer::onTouchBegan, this);
	pTouchListener->onTouchMoved = CC_CALLBACK_2(EventLayer::onTouchMoved, this);
	pTouchListener->onTouchEnded = CC_CALLBACK_2(EventLayer::onTouchEnded, this);
	pTouchListener->onTouchCancelled = CC_CALLBACK_2(EventLayer::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pTouchListener, this);

	// register keyboard events
	auto pKeyboardListener = EventListenerKeyboard::create();
	pKeyboardListener->onKeyPressed = CC_CALLBACK_2(EventLayer::onKeyPressed, this);
	pKeyboardListener->onKeyReleased = CC_CALLBACK_2(EventLayer::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pKeyboardListener, this);

	return true;
}

bool EventLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	if (_state != State::Waiting || !_visible || !_isTouchEnabled)
	{
		return false;
	}

	// check whether parents is visible
	for (Node *pNode = this->getParent(); pNode; pNode = pNode->getParent())
	{
		if (!pNode->isVisible())
		{
			return false;
		}
	}

	_focusNode = this->getNodeForTouch(pTouch);
	if (_focusNode)
	{
		_state = State::Tracking;
		_focusNode->setSelected(true);

		return true;
	}

	return false;
}

void EventLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	CCASSERT(_state == State::Tracking, "Invalid operation during touch moved.");
	auto pNode = this->getNodeForTouch(pTouch);
	if (pNode != _focusNode)
	{
		if (_focusNode)
		{
			_focusNode->setSelected(false);
		}
		_focusNode = pNode;
		if (_focusNode)
		{
			_focusNode->setSelected(true);
		}
	}
}

void EventLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	CCASSERT(_state == State::Tracking, "Invalid operation during touch ended.");
	if (_focusNode)
	{
		_focusNode->setSelected(false);
		_focusNode->onTouch(nullptr);
	}
	this->_state = State::Waiting;
}

void EventLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
	CCASSERT(_state == State::Tracking, "Invalid operation during touch cancelled.");
	if (_focusNode)
	{
		_focusNode->setSelected(false);
	}
	this->_state = State::Waiting;
}

void EventLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
	if (_state != State::Waiting || !_visible || !_isKeyboardEnabled || !_focusNode)
	{
		return;
	}

	this->_state = State::Tracking;
	_focusNode->onKeyPressed(keyCode, nullptr);
	this->_state = State::Waiting;
}

void EventLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
}


/*************************** private functions ***************************/
EventLayer::~EventLayer()
{
	if (this->_focusNode)
	{
		CC_SAFE_RELEASE_NULL(this->_focusNode);
	}
}
EventNode *EventLayer::getNodeForTouch(Touch *pTouch)
{
	Point location = pTouch->getLocation();

	for (auto iter = _children.crbegin(); iter != _children.crend(); ++iter)
	{
		auto child = dynamic_cast<EventNode*>(*iter);
		if (child && child->isVisible())
		{
			Point nodePos = child->convertToNodeSpace(location);
			Rect region = child->rect();
			region.origin = Point::ZERO;

			if (region.containsPoint(nodePos))
			{
				if (child->isEnabled())
				{
					return child;
				}
				else	// intercepted
				{
					return nullptr;
				}
			}

		}
	}

	return nullptr;
}

}