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


	void LuaEngineEx::copyBetweenLuaStates(lua_State *from, lua_State *to, int index)
	{
		switch (lua_type(from, index))
		{
		case LUA_TBOOLEAN:
			lua_pushboolean(to, lua_toboolean(from, index));
			break;
		case LUA_TNUMBER:
		{
							lua_Number num = lua_tonumber(from, index);
							lua_pushnumber(to, num);
		}
			break;
		case LUA_TSTRING:
		{
							size_t len;
							const char *s = lua_tolstring(from, index, &len);
							lua_pushlstring(to, s, len);
		}
			break;
		case LUA_TLIGHTUSERDATA:
			lua_pushlightuserdata(to, lua_touserdata(from, index));
			break;
		case LUA_TUSERDATA:
			// any issues??
			tolua_pushuserdata(to, lua_touserdata(from, index));
			break;
		case LUA_TNIL:
			lua_pushnil(to);
			break;
		case LUA_TTABLE:
			lua_newtable(to);
			lua_pushnil(from);		// start iteration
			while (lua_next(from, -2))
			{
				unsigned int val_i = lua_gettop(from);
				unsigned int key_i = val_i - 1;

				copyBetweenLuaStates(from, to, key_i);
				copyBetweenLuaStates(from, to, val_i);

				lua_rawset(to, -3);		// without __newIndex trigger
				lua_pop(from, 1);		// next round, pop out the value
			}
			// end iteration
			break;
		case LUA_TFUNCTION:
			// todo
			break;
		case LUA_TTHREAD:
			// doesn't support
			break;
		}
	}

	int LuaEngineEx::handleFrameworkEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data)
	{
		switch (type)
		{
            case ScriptHandlerMgr::HandlerType::LISTMENU_ITEMSELECTED:
            case ScriptHandlerMgr::HandlerType::LISTMENU_ITEMFOCUSED:
            case ScriptHandlerMgr::HandlerType::LISTMENU_ITEMBLURRED:
            case ScriptHandlerMgr::HandlerType::LISTMENU_ITEMWILLRECYCLE:
                return this->handleListMenuEvent(type, data);
            case ScriptHandlerMgr::HandlerType::DIRECTION_CONTROLLER_ON_RIGHT:
            case ScriptHandlerMgr::HandlerType::DIRECTION_CONTROLLER_ON_LEFT:
            case ScriptHandlerMgr::HandlerType::DIRECTION_CONTROLLER_ON_UP:
            case ScriptHandlerMgr::HandlerType::DIRECTION_CONTROLLER_ON_DOWN:
            case ScriptHandlerMgr::HandlerType::DIRECTION_CONTROLLER_ON_STOP:
                return this->handleDirectionControllerEvent(type, data);
            case ScriptHandlerMgr::HandlerType::CHECKEDBUTTON_ON_CHECKED:
            case ScriptHandlerMgr::HandlerType::CHECKEDBUTTON_ON_UNCHECKED:
                return this->handleCheckedButtonEvent(type, data);
            default:
                break;
		}
        
        return 0;
	}

	int LuaEngineEx::handleFrameworkEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*, int)>& func)
	{
		switch (type)
		{
            case ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_SIZE_FOR_MENU:
            case ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_AT_INDEX:
            case ScriptHandlerMgr::HandlerType::LISTMENU_COUNT_OF_ITEMS:
                return this->handleListMenuEvent(type, data, numResults, func);
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

	int LuaEngineEx::handleListMenuEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*, int)>& func)
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
    
    int LuaEngineEx::handleDirectionControllerEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void *data)
    {
        if (!data) {
            return 0;
        }
        
		BasicScriptData *eventData = static_cast<BasicScriptData*>(data);
		if (!eventData->nativeObject)
		{
			return 0;
		}
        
		LuaDirectionControllerEventData *directionControllerData = static_cast<LuaDirectionControllerEventData*>(eventData->value);
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
		toluafix_pushusertype_ccobject(this->getLuaStack()->getLuaState(), pObj->_ID, &(pObj->_luaID), (void*)pObj, "pf.DirectionController");
		ret = this->getLuaStack()->executeFunctionByHandler(handler, 1);
        
		return ret;
    }
    
    int LuaEngineEx::handleCheckedButtonEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void *data)
    {
        if (!data) {
            return 0;
        }
        
        BasicScriptData *eventData = static_cast<BasicScriptData*>(data);
        if (!eventData->nativeObject) {
            return 0;
        }
        
        LuaCheckedButtonEventData *checkedBtnData = static_cast<LuaCheckedButtonEventData*>(eventData->value);
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)eventData->nativeObject, type);
        
        if (!handler) {
            return 0;
        }
        
        Ref *pObj = static_cast<Ref*>(eventData->nativeObject);
        
        if (!pObj) {
            return 0;
        }
        
        int ret = 0;
        toluafix_pushusertype_ccobject(this->getLuaStack()->getLuaState(), pObj->_ID, &(pObj->_luaID), (void*)pObj, "pf.CheckedButton");
        ret = this->getLuaStack()->executeFunctionByHandler(handler, 1);
        
        return ret;
    }
}