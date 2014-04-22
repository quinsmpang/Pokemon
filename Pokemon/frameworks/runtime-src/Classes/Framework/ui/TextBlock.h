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
	static TextBlock *create(const std::string &szContent, const std::string &szFontName, int fontSize = 20, TouchCallback touchCallback = nullptr, KeyboardCallback keyboardCallback = nullptr);

	bool initWithString(const std::string &szContent, const std::string &szFontName, int fontSize, TouchCallback touchCallback, KeyboardCallback keyboardCallback);

	void setDefaultColor(cocos2d::Color3B color);
	void setSelectedColor(cocos2d::Color3B color);
	void setDisabledColor(cocos2d::Color3B color);
protected:
	virtual ~TextBlock();
};

}

#endif