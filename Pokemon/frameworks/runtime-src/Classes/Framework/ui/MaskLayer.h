/******************************
Description: The layer can penetrate and intercept touch events
Author: M.Wan
Date: 4/18/2014
******************************/

#include "cocos2d.h"
#include "BaseLayer.h"

namespace framework
{

	class MaskLayerDelegate
	{
	public:
		virtual ~MaskLayerDelegate()
		{
		}

		/* 事件穿透 */
		virtual void onEventPenetrated(float x, float y) = 0;

		/* 事件拦截 */
		virtual void onEventIntercepted(float x, float y) = 0;
	};

	class MaskLayer : public BaseLayer
	{
	public:
		MaskLayer();

		static MaskLayer *create();

		static MaskLayer *create(cocos2d::Rect area);

		void setColor(const cocos2d::Color3B &color);

		void setOpacity(GLubyte opacity);

		void setEnabled(bool isEnabled) override;

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

		CC_SYNTHESIZE(MaskLayerDelegate*, _delegate, Delegate);
		// lua delegate
		CC_SYNTHESIZE(Ref*, _scriptDelegate, ScriptDelegate);

		virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
	protected:
		cocos2d::Color3B _color;		// mask color
		GLubyte _opacity;		// mask opacity
		cocos2d::Rect _area;	// available area

		bool _lazyUpdate;
		cocos2d::ClippingNode *_clipper;
		cocos2d::LayerColor *_mask;

		bool _interceptAllEvents;	// whether to intercept all events

		bool initWithArea(const cocos2d::Rect &area);
		void updateView();
	};

}