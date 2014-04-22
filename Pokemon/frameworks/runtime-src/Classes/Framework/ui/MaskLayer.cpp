#include "MaskLayer.h"
#include "lua/LuaUtils.h"

using namespace cocos2d;

namespace framework
{

/*****************public functions*****************/
MaskLayer::MaskLayer()
	: _opacity(200)
	, _color(Color3B(0, 0, 0))
	, _area(Rect(0, 0, 0, 0))
	, _lazyUpdate(false)
	, _interceptAllEvents(false)
	, _delegate(nullptr)
	, _scriptDelegate(nullptr)
{
}

MaskLayer *MaskLayer::create()
{
	return MaskLayer::create(Rect::ZERO);
}

MaskLayer *MaskLayer::create(Rect area)
{
	MaskLayer *pLayer = new MaskLayer();
	pLayer->autorelease();
	if (!pLayer->initWithArea(area))
	{
		CC_SAFE_RELEASE_NULL(pLayer);
		return nullptr;
	}
	
	return pLayer;
}

void MaskLayer::setColor(const Color3B &color)
{
	this->_color = color;
	this->updateView();
}

void MaskLayer::setOpacity(GLubyte opacity)
{
	this->_opacity = opacity;
	this->updateView();
}

bool MaskLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	CC_UNUSED_PARAM(pEvent);
	Point pos = pTouch->getLocation();
	bool needIntercept = this->isInterceptAllEvents() || !_area.containsPoint(pos);

	// cpp callback
	if (this->_delegate)
	{
		if (needIntercept)
		{
			this->_delegate->onEventIntercepted(pos.x, pos.y);
		}
		else
		{
			this->_delegate->onEventPenetrated(pos.x, pos.y);
		}
	}

	// lua callback
	if (this->_scriptDelegate)
	{
		// params
		Vector<Ref*> *pParams = new Vector<Ref*>();
		pParams->pushBack(__Float::create(pos.x));
		pParams->pushBack(__Float::create(pos.y));
		// param types
		Vector<Ref*> *pTypes = new Vector<Ref*>();
		pTypes->pushBack(__String::create("__Float"));
		pTypes->pushBack(__String::create("__Float"));
		if (needIntercept)
		{
			LuaUtils::executePeertableFunction(this->_scriptDelegate, "onEventIntercepted", pParams, pTypes, false);
		}
		else
		{
			LuaUtils::executePeertableFunction(this->_scriptDelegate, "onEventPenetrated", pParams, pTypes, false);
		}
	}

	return true;
}

void MaskLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
}

void MaskLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
}

void MaskLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
}

/*****************private functions*****************/
bool MaskLayer::initWithArea(const cocos2d::Rect &area)
{
	if (!LayerColor::init())
	{
		return false;
	}

	this->_area = area;
	this->_color = Color3B(0, 0, 0);
	this->_opacity = 255;

	// create clipper
	_clipper = ClippingNode::create();
	_clipper->setAnchorPoint(Point::ZERO);
	_clipper->setPosition(Point::ZERO);
	_clipper->setAlphaThreshold(0.0f);
	_clipper->setInverted(true);
	this->addChild(_clipper, 999);

	// create mask 
	_mask = LayerColor::create(Color4B(0, 0, 0, 255));
	_mask->setPosition(Point::ZERO);
	_mask->setAnchorPoint(Point::ZERO);
	_mask->ignoreAnchorPointForPosition(false);
	_clipper->addChild(_mask);

	this->_lazyUpdate = true;

	// register touch events.
	auto pListener = EventListenerTouchOneByOne::create();
	pListener->onTouchBegan = CC_CALLBACK_2(MaskLayer::onTouchBegan, this);
	pListener->onTouchMoved = CC_CALLBACK_2(MaskLayer::onTouchMoved, this);
	pListener->onTouchEnded = CC_CALLBACK_2(MaskLayer::onTouchEnded, this);
	pListener->onTouchCancelled = CC_CALLBACK_2(MaskLayer::onTouchCancelled, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);

	this->_lazyUpdate = false;
	this->updateView();

	return true;
}

void MaskLayer::updateView()
{
	if (_lazyUpdate)
	{
		return;
	}

	_mask->setColor(_color);
	_mask->setOpacity(_opacity);

	// draw area
	if (_area.size.width != 0 && _area.size.height != 0)
	{
		auto pDrawNode = DrawNode::create();
		// The origin of the rect is at bottom-left
		Point rect[4] = { Point(_area.origin.x, _area.origin.y + _area.size.height), Point(_area.origin.x + _area.size.width, _area.origin.y + _area.size.height), Point(_area.origin.x + _area.size.width, _area.origin.y), _area.origin };
		pDrawNode->drawPolygon(rect, 4, Color4F::WHITE, 0, Color4F::WHITE);
		_clipper->setStencil(pDrawNode);
	}
}

}