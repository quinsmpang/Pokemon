/******************************
Description: Extend LuaEngine to handle custom events
Author: M.Wan
Date: 7/5/2014
******************************/

#ifndef __LUA_LUAENGINEEX__
#define __LUA_LUAENGINEEX__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif
#include "CCLuaEngine.h"

namespace framework
{
	class LuaEngineEx : public cocos2d::LuaEngine
	{
	public:
		static LuaEngineEx *getInstance();

		// copy the value at index from lua_State(from) to lua_State(to)
		void copyBetweenLuaStates(lua_State *from, lua_State *to, int index = -1);

		int handleFrameworkEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data);
		int handleFrameworkEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func);

	private:
		int handleListMenuEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data);
		int handleListMenuEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func);
	};
}

#endif