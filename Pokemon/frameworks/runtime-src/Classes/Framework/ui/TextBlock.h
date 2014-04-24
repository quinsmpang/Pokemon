/******************************
	Description: TextBlock, extends EventNode
	Author: M.Wan
	Date: 4/22/2014
******************************/

#ifndef __UI_LABEL__
#define __UI_LABEL__

#include "EventNode.h"
#include <string>

namespace framework
{

class TextBlock : public EventNode
{
public:
	static TextBlock *create(const std::string &szContent, const std::string &szFontName, int fontSize = 20);
	static TextBlock *createWithCallback(const std::string &szContent, const std::string &szFontName, int fontSize = 20, const TouchCallback &touchCallback = nullptr, const KeyboardCallback &keyboardCallback = nullptr);

	void setDefaultColor(cocos2d::Color3B color);
	void setSelectedColor(cocos2d::Color3B color);
	void setDisabledColor(cocos2d::Color3B color);
protected:
	virtual ~TextBlock();

	bool initWithString(const std::string &szContent, const std::string &szFontName, int fontSize, const TouchCallback &touchCallback, const KeyboardCallback &keyboardCallback);
};

}

#endif