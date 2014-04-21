/******************************
	Description: Button, inherit EventNode
	Author: M.Wan
	Date: 4/21/2014
******************************/

#ifndef __UI_BUTTON_H__
#define __UI_BUTTON_H__

#include "EventNode.h"

namespace framework
{

class Button : public EventNode
{
public:
	bool initWithNodes(cocos2d::Node *pDefaultImage, cocos2d::Node *pSelectedImage, cocos2d::Node *pDisabledImage, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback = nullptr);

	static Button *create(const char *szDefaultImagePath, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback = nullptr);
	static Button *create(const char *szDefaultImagePath, const char *szSelectedImagePath, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback = nullptr);
	static Button *create(const char *szDefaultImagePath, const char *szSelectedImagePath, const char *szDisabledImagePath, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback = nullptr);

	static Button *create(cocos2d::Node *pDefaultImage, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback = nullptr);
	static Button *create(cocos2d::Node *pDefaultImage, cocos2d::Node *pSelectedImage, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback = nullptr);
	static Button *create(cocos2d::Node *pDefaultImage, cocos2d::Node *pSelectedImage, cocos2d::Node *pDisabledImage, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback = nullptr);
protected:
	virtual ~Button();
};

}

#endif