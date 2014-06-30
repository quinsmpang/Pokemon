#include "ScriptCCBReader.h"
#include "cocos/editor-support/cocosbuilder/CCNodeLoaderLibrary.h"
#include "cocos/editor-support/cocosbuilder/CCBReader.h"
#include "lua/LuaUtils.h"

using namespace cocos2d;
using namespace cocosbuilder;

namespace framework
{
	/***********************ScriptCCBOwner implementation***********************/
	ScriptCCBOwner *ScriptCCBOwner::create()
	{
		auto pOwner = new ScriptCCBOwner();
		if (pOwner)
		{
			pOwner->autorelease();

			return pOwner;
		}

		CC_SAFE_RELEASE_NULL(pOwner);
		return nullptr;
	}

	cocos2d::SEL_MenuHandler ScriptCCBOwner::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
	{
		CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, pSelectorName, ScriptCCBOwner::onMenuItemSelect);
		return nullptr;
	}

	cocos2d::extension::Control::Handler ScriptCCBOwner::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
	{
		CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, pSelectorName, ScriptCCBOwner::onControlSelect);
		return nullptr;
	}

	void ScriptCCBOwner::onMenuItemSelect(cocos2d::Ref *sender)
	{
		if (this->_scriptDelegate)
		{
#if CC_ENABLE_SCRIPT_BINDING
			// params
			Vector<Ref*> pParams(1);
			pParams.pushBack(sender);
			Vector<Ref*> pParamTypes(1);
			pParams.pushBack(__String::create("cc.Node"));
			LuaUtils::getInstance()->executePeertableFunction(this->_scriptDelegate, "onMenuItemSelect", pParams, pParamTypes, false);
#endif
		}
	}

	void ScriptCCBOwner::onControlSelect(cocos2d::Ref *sender, cocos2d::extension::Control::EventType eventType)
	{
		if (this->_scriptDelegate)
		{
#if CC_ENABLE_SCRIPT_BINDING
			// params
			Vector<Ref*> pParams(2);
			pParams.pushBack(sender);
			pParams.pushBack(__Integer::create((int)eventType));
			Vector<Ref*> pParamTypes(2);
			pParams.pushBack(__String::create("cc.Node"));
			pParams.pushBack(__String::create("__Integer"));
			LuaUtils::getInstance()->executePeertableFunction(this->_scriptDelegate, "onControlSelect", pParams, pParamTypes, false);
#endif
		}
	}

	/***********************ScriptCCBReader implementation***********************/
	Node *ScriptCCBReader::readCCB(const std::string &ccbFilePath, Ref *scriptDelegate)
	{
		static Vector<ScriptCCBOwner*> scriptCCBOwnerArray;

		// 创建一个owner接受事件，owner负责接收ccb的各种事件并转发到scriptDelegate
		auto pOwner = ScriptCCBOwner::create();
		pOwner->setScriptDelegate(scriptDelegate);
		scriptCCBOwnerArray.pushBack(pOwner);

		// 读取ccb
		auto pReader = new CCBReader(NodeLoaderLibrary::getInstance());
		pReader->autorelease();
		return pReader->readNodeGraphFromFile(ccbFilePath.c_str(), pOwner);
	}
}