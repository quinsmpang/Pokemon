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

        /**
         * Copy value at specified index from a lua state to another lua state.
         *
         * @param from Source lua state.
         * @param to Destination lua state.
         * @param index The index at lua state.
         */
		void copyBetweenLuaStates(lua_State *from, lua_State *to, int index = -1);

        /**
         * Handle those framework userdefined events with no argument.
         *
         * @param type Event type.
         * @param data Event param.
         *
         * @return Handle result.
         */
		int handleFrameworkEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data);
        /**
         * Handle framework userdefined events with arguments or return values.
         *
         * @param type Event type.
         * @param data Event param.
         *
         * @return Handle result.
         */
		int handleFrameworkEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func);

	private:
		int handleListMenuEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data);
		int handleListMenuEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func);
        int handleDirectionControllerEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data);
        int handleCheckedButtonEvent(cocos2d::ScriptHandlerMgr::HandlerType type, void* data);
	};
}

#endif