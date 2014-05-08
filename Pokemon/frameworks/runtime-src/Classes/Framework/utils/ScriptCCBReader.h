/******************************
Description: Read .ccbi file in lua
Author: M.Wan
Date: 5/8/2014
******************************/

#ifndef __UTILS_SCRIPTCCBREADER__
#define __UTILS_SCRIPTCCBREADER__

#include "cocos2d.h"
#include "cocos\editor-support\cocosbuilder\CCBSelectorResolver.h"
#include <string>

namespace framework
{
	class ScriptCCBOwner : public cocos2d::Ref, public cocosbuilder::CCBSelectorResolver
	{
	public:
		static ScriptCCBOwner *create();

		CC_SYNTHESIZE(cocos2d::Ref*, _scriptDelegate, ScriptDelegate);

		cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName);

		cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);

		void onMenuItemSelect(cocos2d::Ref *sender);

		void onControlSelect(cocos2d::Ref *sender, cocos2d::extension::Control::EventType eventType);
	};

	class ScriptCCBReader
	{
	public:
		static cocos2d::Node *readCCB(const std::string &ccbFilePath, cocos2d::Ref *scriptDelegate);
	};
}

#endif