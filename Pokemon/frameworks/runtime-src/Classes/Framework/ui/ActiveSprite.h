/******************************
Description: ActiveSprite, extends EventNode
Author: M.Wan
Date: 4/22/2014
******************************/

#ifndef __UI_ACTIVESPRITE__
#define __UI_ACTIVESPRITE__

#include "EventNode.h"

namespace framework
{

	class ActiveSprite : public EventNode
	{
	public:
		static ActiveSprite *create(const char *szSpritePath);
		static ActiveSprite *create(cocos2d::Node *pSprite);
		static ActiveSprite *createWithCallback(const char *szSpritePath, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback);
		static ActiveSprite *createWithCallback(cocos2d::Node *pSprite, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback);
	protected:
		virtual ~ActiveSprite();

		bool initWithSprite(cocos2d::Node *pSprite, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback);
		void updateImageVisibility() override;
	};

}

#endif