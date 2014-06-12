/******************************
Description: Extended TextField
Author: M.Wan
Date: 6/12/2014
******************************/

#ifndef __CONTROLS_CURSORTEXTFIELD__
#define __CONTROLS_CURSORTEXTFIELD__

#include "cocos2d.h"
#include <string>

namespace framework
{
	class TextFieldTouchDelegate
	{
		virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) = 0;
		virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) = 0;
	};

	class CursorTextField : public cocos2d::TextFieldTTF, public cocos2d::TextFieldDelegate, public TextFieldTouchDelegate
	{
	public:
		CursorTextField();
		virtual ~CursorTextField();

		static CursorTextField *create(const std::string &placeholder, const std::string &fontName, float fontSize);

		void onEnter() override;
		void onExit() override;

		// init cursor sprite
		void initCursorSprite(int height);

		// IMEDelegate implementation
		bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF * sender) override;
		bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF * sender) override;
		bool onTextFieldInsertText(cocos2d::TextFieldTTF * sender, const char * text, size_t nLen) override;
		bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF * sender, const char * delText, size_t nLen) override;

		// TextFieldTouchDelegate implementation
		bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
		void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

		// check whether the touch is in the field region
		bool isInTextField(cocos2d::Touch *touch);
		// get region of the textfield
		const cocos2d::Rect &getFieldRegion();

		void openIME();
		void closeIME();

	protected:
		cocos2d::Point _beginPos;
		cocos2d::Sprite *_cursorSprite;
		cocos2d::Action *_cursorAction;
		cocos2d::Point _cursorPos;
		std::string *_inputText;
	};
}

#endif