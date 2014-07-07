#include "LuaEngineEx.h"
#include "tolua_fix.h"
#include "lua_framework_manual.hpp"

using namespace cocos2d;

namespace framework
{
	LuaEngineEx *LuaEngineEx::getInstance()
	{
		return (LuaEngineEx*)LuaEngine::getInstance();
	}

	int LuaEngineEx::handleFrameworkEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data)
	{
		switch (type)
		{
		case ScriptHandlerMgr::HandlerType::LISTMENU_ITEMSELECTED:
		case ScriptHandlerMgr::HandlerType::LISTMENU_ITEMFOCUSED:
		case ScriptHandlerMgr::HandlerType::LISTMENU_ITEMBLURRED:
		case ScriptHandlerMgr::HandlerType::LISTMENU_ITEMWILLRECYCLE:
			{
				return this->handleListMenuEvent(type, data);
			}
			break;
		}
	}

	int LuaEngineEx::handleFrameworkEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func)
	{
		switch (type)
		{
		case ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_SIZE_FOR_MENU:
		case ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_AT_INDEX:
		case ScriptHandlerMgr::HandlerType::LISTMENU_COUNT_OF_ITEMS:
			{
				return this->handleListMenuEvent(type, data, numResults, func);
			}
			break;
		default:
			break;
		}

		return 0;
	}

	int LuaEngineEx::handleListMenuEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data)
	{
		if (!data)
		{
			return 0;
		}

		BasicScriptData *eventData = static_cast<BasicScriptData*>(data);
		if (!eventData->nativeObject || !eventData->value)
		{
			return 0;
		}

		LuaListMenuEventData *listMenuData = static_cast<LuaListMenuEventData*>(eventData->value);
		int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, type);

		if (!handler)
		{
			return 0;
		}

		Ref *pObj = static_cast<Ref*>(eventData->nativeObject);
		Ref *pItemObj = static_cast<Ref*>(listMenuData->_value);

		if (!pObj || !pItemObj)
		{
			return 0;
		}

		int ret = 0;
		toluafix_pushusertype_ccobject(this->getLuaStack()->getLuaState(), pObj->_ID, &(pObj->_luaID), (void*)pObj, "pf.ListMenu");
		toluafix_pushusertype_ccobject(this->getLuaStack()->getLuaState(), pItemObj->_ID, &(pItemObj->_luaID), (void*)pItemObj, "pf.ListMenuItem");
		ret = this->getLuaStack()->executeFunctionByHandler(handler, 2);

		return ret;
	}

	int LuaEngineEx::handleListMenuEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func)
	{
		if (!data || numResults <= 0)
		{
			return 0;
		}

		BasicScriptData *eventData = static_cast<BasicScriptData*>(data);
		if (!eventData->nativeObject || !eventData->value)
		{
			return 0;
		}

		LuaListMenuEventData *listMenuData = static_cast<LuaListMenuEventData*>(eventData->value);
		int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, type);

		if (!handler)
		{
			return 0;
		}

		Ref *pObj = static_cast<Ref*>(eventData->nativeObject);

		if (!pObj)
		{
			return 0;
		}

		int ret = 0;
		switch (type)
		{
		case ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_SIZE_FOR_MENU:
			{
				toluafix_pushusertype_ccobject(this->getLuaStack()->getLuaState(), pObj->_ID, &(pObj->_luaID), (void*)pObj, "pf.ListMenu");
				ret = this->getLuaStack()->executeFunction(handler, 1, 2, func);
			}
			break;
		case ScriptHandlerMgr::HandlerType::LISTMENU_COUNT_OF_ITEMS:
			{
				toluafix_pushusertype_ccobject(this->getLuaStack()->getLuaState(), pObj->_ID, &(pObj->_luaID), (void*)pObj, "pf.ListMenu");
				ret = this->getLuaStack()->executeFunction(handler, 1, 1, func);
			}
			break;
		case ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_AT_INDEX:
			{
				toluafix_pushusertype_ccobject(this->getLuaStack()->getLuaState(), pObj->_ID, &(pObj->_luaID), (void*)pObj, "pf.ListMenu");
				this->getLuaStack()->pushLong(*((ssize_t*)listMenuData->_value));
				ret = this->getLuaStack()->executeFunction(handler, 2, 1, func);
			}
			break;
		default:
			break;
		}

		return ret;
	}
}