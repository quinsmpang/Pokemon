#include "EventLayer.h"

using namespace cocos2d;

namespace framework
{

EventLayer::EventLayer()
	: _selectedNode(nullptr)
	, _focusNode(nullptr)
	, _state(State::Waiting)
	, _isTouchEnabled(true)
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	, _isKeyboardEnabled(true)
#endif
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

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	// register keyboard events
	auto pKeyboardListener = EventListenerKeyboard::create();
	pKeyboardListener->onKeyPressed = CC_CALLBACK_2(EventLayer::onKeyPressed, this);
	pKeyboardListener->onKeyReleased = CC_CALLBACK_2(EventLayer::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pKeyboardListener, this);
#endif

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

	_selectedNode = this->getNodeForTouch(pTouch);
	if (_selectedNode)
	{
		_state = State::Tracking;
		_selectedNode->setSelected(true);

		return true;
	}

	return false;
}

void EventLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	CCASSERT(_state == State::Tracking, "Invalid operation during touch moved.");
	auto pNode = this->getNodeForTouch(pTouch);
	if (pNode != _selectedNode)
	{
		if (_selectedNode)
		{
			_selectedNode->setSelected(false);
		}
		_selectedNode = pNode;
		if (_selectedNode)
		{
			_selectedNode->setSelected(true);
		}
	}
}

void EventLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	CCASSERT(_state == State::Tracking, "Invalid operation during touch ended.");
	if (_selectedNode)
	{
		_selectedNode->setSelected(false);
		_selectedNode->onTouch(nullptr);
	}
	this->_state = State::Waiting;
}

void EventLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
	CCASSERT(_state == State::Tracking, "Invalid operation during touch cancelled.");
	if (_selectedNode)
	{
		_selectedNode->setSelected(false);
	}
	this->_state = State::Waiting;
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
void EventLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
	if (_state != State::Waiting || !_visible || !_isKeyboardEnabled || !_selectedNode)
	{
		return;
	}

	this->_state = State::Tracking;
	_selectedNode->onKeyPressed(keyCode, nullptr);
	this->_state = State::Waiting;
}

void EventLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *pEvent)
{
}

#endif


/*************************** private functions ***************************/
EventLayer::~EventLayer()
{
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