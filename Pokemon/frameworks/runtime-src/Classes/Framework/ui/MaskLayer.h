/******************************
Description: The layer can penetrate and intercept touch events
Author: M.Wan
Date: 4/18/2014
******************************/

#include "cocos2d.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

namespace framework
{

	class MaskLayerDelegate
	{
	public:
		/* Touch penetrated */
		virtual void onEventPenetrated(float x, float y) = 0;

		/* Touch intercepted */
		virtual void onEventIntercepted(float x, float y) = 0;
	};

	class MaskLayer : public cocos2d::LayerColor, public MaskLayerDelegate
	{
	public:
		MaskLayer();

		static MaskLayer *create();

		static MaskLayer *create(cocos2d::Rect area);

		void setColor(const cocos2d::Color3B &color);

		void setOpacity(GLubyte opacity);

		inline cocos2d::Rect getArea()
		{
			return this->_area;
		}

		inline void setArea(cocos2d::Rect area)
		{
			this->_area = area;
			this->updateView();
		}

		inline void forceInterceptAllEvents(bool interceptAllEvent)
		{
			this->_interceptAllEvents = interceptAllEvent;
		}

		inline bool isInterceptAllEvents()
		{
			return this->_interceptAllEvents;
		}

		virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;

		virtual void onEventPenetrated(float x, float y);
		virtual void onEventIntercepted(float x, float y);
	protected:
		cocos2d::Color3B _color;		// mask color
		GLubyte _opacity;		// mask opacity
		cocos2d::Rect _area;	// available area

		bool _lazyUpdate;
		cocos2d::ClippingNode *_clipper;
		cocos2d::LayerColor *_mask;
		cocos2d::Sprite *_stencil;
		cocos2d::extension::Scale9Sprite *_rect;

		bool _interceptAllEvents;	// whether to intercept all events

		bool initWithArea(const cocos2d::Rect &area);
		void updateView();
	};

}