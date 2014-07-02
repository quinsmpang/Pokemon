/******************************
Description: Modal layer, which swallows all events below the layer.
Author: M.Wan
Date: 5/1/2014
******************************/

#ifndef __UI_MODALLAYER__
#define __UI_MODALLAYER__

#include "cocos2d.h"

namespace framework
{
	class ModalLayerDelegate
	{
	public:
		// handle modal layer touch events
		virtual void onModalTouchBegan(float x, float y) = 0;
		virtual void onModalTouchMoved(float x, float y) = 0;
		virtual void onModalTouchEnded(float x, float y) = 0;
		virtual void onModalTouchCancelled(float x, float y) = 0;

		// handle come in event and go out event.
		virtual void onComeIn() = 0;
		virtual void onGoOut() = 0;
	};

	class ModalLayer : public cocos2d::LayerColor, public ModalLayerDelegate
	{
	public:
		static ModalLayer *create();

		virtual bool init();

		void onEnter() override;

		void onExit() override;

		bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override; 
		void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		
		// handle modal layer touch events
		virtual void onModalTouchBegan(float x, float y);
		virtual void onModalTouchMoved(float x, float y);
		virtual void onModalTouchEnded(float x, float y);
		virtual void onModalTouchCancelled(float x, float y);

		// handle come in event and go out event.
		virtual void onComeIn();
		virtual void onGoOut();
	};
}

#endif