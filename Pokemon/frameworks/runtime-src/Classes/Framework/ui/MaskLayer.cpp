#include "MaskLayer.h"
#include "../lua/LuaUtils.h"

using namespace cocos2d;

namespace framework
{

	/*****************public functions*****************/
	MaskLayer::MaskLayer()
		: LayerColor()
		, _opacity(200)
		, _color(Color3B(0, 0, 0))
		, _area(Rect(0, 0, 0, 0))
		, _stencil(nullptr)
		, _rect(nullptr)
		, _lazyUpdate(false)
		, _interceptAllEvents(false)
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
		if (!_visible)
		{
			return false;
		}

		CC_UNUSED_PARAM(pEvent);
		Point pos = pTouch->getLocation();
		bool needIntercept = this->isInterceptAllEvents() || !_area.containsPoint(pos);

		// lua callback
#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			// params
			Vector<Ref*> pParams(2);
			pParams.pushBack(__Float::create(pos.x));
			pParams.pushBack(__Float::create(pos.y));
			// param types
			Vector<Ref*> pTypes(2);
			pTypes.pushBack(__String::create("__Float"));
			pTypes.pushBack(__String::create("__Float"));
			if (needIntercept)
			{
				LuaUtils::getInstance()->executePeertableFunction(this, "onEventIntercepted", pParams, pTypes, false);
			}
			else
			{
				LuaUtils::getInstance()->executePeertableFunction(this, "onEventPenetrated", pParams, pTypes, false);
			}
		}
#endif
		if (needIntercept)
		{
			this->onEventIntercepted(pos.x, pos.y);
		}
		else
		{
			this->onEventPenetrated(pos.x, pos.y);
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

	void MaskLayer::onEventIntercepted(float x, float y)
	{
	}

	void MaskLayer::onEventPenetrated(float x, float y)
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
		this->addChild(_clipper);

		// set stencil
		_stencil = Sprite::create("framework/mask.png");
		_stencil->setAnchorPoint(Point::ZERO);
		_stencil->setPosition(Point::ZERO);
		_stencil->setVisible(false);
		_clipper->setStencil(_stencil);

		// create mask 
		_mask = LayerColor::create(Color4B(0, 0, 0, 255));
		_mask->setPosition(Point::ZERO);
		_mask->setAnchorPoint(Point::ZERO);
		_mask->ignoreAnchorPointForPosition(false);
		_clipper->addChild(_mask);

		_rect = extension::Scale9Sprite::create("framework/mask_rect.png", Rect(0, 0, 100, 100), Rect(48, 48, 2, 2));
		_rect->setAnchorPoint(Point::ZERO);
		this->addChild(_rect);
		_rect->setVisible(false);

		this->_lazyUpdate = true;

		// register touch events.
		auto pListener = EventListenerTouchOneByOne::create();
		pListener->setSwallowTouches(true);
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

		// draw available area with effect
		if (_area.size.width * _area.size.height == 0)
		{
			_stencil->setVisible(false);
			_rect->setVisible(false);
			return;
		}
		else
		{
			const int OFFSET = 10;

			_rect->setPreferredSize(Size(_area.size.width + OFFSET * 2, _area.size.height + OFFSET * 2));
			_rect->setPosition(_area.origin.x - OFFSET, _area.origin.y - OFFSET);
			_rect->setVisible(true);
			Node *parent = (Node*)_rect->getChildren().at(0);
			auto children = parent->getChildren();
			for (int i = 0; i < children.size(); ++i)
			{
				auto child = (Sprite*)children.at(i);
				child->setOpacity(_opacity);
			}

			_stencil->setScaleX(_area.size.width * 0.5 + OFFSET);
			_stencil->setScaleY(_area.size.height * 0.5 + OFFSET);
			_stencil->setPosition(_area.origin.x - OFFSET, _area.origin.y - OFFSET);
			_stencil->setVisible(true);
		}

		/*
		// draw area -- deprecated, there are some issues using DrawNode when there are multiple layers covering together.
		if (_area.size.width != 0 && _area.size.height != 0)
		{
			auto pDrawNode = DrawNode::create();
			// The origin of the rect is at bottom-left
			Point rect[4] = { Point(_area.origin.x, _area.origin.y + _area.size.height), Point(_area.origin.x + _area.size.width, _area.origin.y + _area.size.height), Point(_area.origin.x + _area.size.width, _area.origin.y), _area.origin };
			pDrawNode->drawPolygon(rect, 4, Color4F::WHITE, 0, Color4F::WHITE);
			_clipper->setStencil(pDrawNode);
		}
		*/
	}

}