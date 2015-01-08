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
        /**
         * Touch penetrated delegate.
         *
         * @param x Touch x coordinate.
         * @param y Touch y coordinate.
         */
		virtual void onEventPenetrated(float x, float y) = 0;

		/**
         * Touch intercepted delegate.
         *
         * @param x Touch x coordinate.
         * @param y Touch y coordinate.
         */
		virtual void onEventIntercepted(float x, float y) = 0;
	};

	class MaskLayer : public cocos2d::LayerColor, public MaskLayerDelegate
	{
	public:
        /**
         * MaskLayer constructor.
         */
		MaskLayer();
        /**
         * Create a new MaskLayer with no clickable area.
         *
         * @return Return new MaskLayer object.
         */
		static MaskLayer *create();
        /**
         * Create a new MaskLayer with specified penetrated area.
         *
         * @param area Penetrated area.
         *
         * @return Return new MaskLayer object.
         */
		static MaskLayer *create(cocos2d::Rect area);

        /**
         * Set the mask color.
         *
         * @param color Color of the mask.
         */
		void setColor(const cocos2d::Color3B &color);
        /**
         * Set the mask opacity.
         *
         * @param opacity Transparency of the mask.
         */
		void setOpacity(GLubyte opacity);

        /**
         * Get current clickable area.
         *
         * @return Return the clickable area.
         */
		inline cocos2d::Rect getArea()
		{
			return this->_area;
		}
        /**
         * Set clickable area.
         *
         * @param area Clickable area.
         */
		inline void setArea(cocos2d::Rect area)
		{
			this->_area = area;
			this->updateView();
		}
        
        /**
         * Whether to intercept all touch events.
         *
         * @param interceptAllEvent A boolean value if to intercept all touch events.
         */
		inline void forceInterceptAllEvents(bool interceptAllEvent)
		{
			this->_interceptAllEvents = interceptAllEvent;
		}
        /**
         * Is the layer entirely intercepted?
         *
         * @return A boolean value.
         */
		inline bool isInterceptAllEvents()
		{
			return this->_interceptAllEvents;
		}

        /**
         * Touch events overrides.
         */
		virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
        
        /**
         * MaskLayerDelegate overrides.
         */
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