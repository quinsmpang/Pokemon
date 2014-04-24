#include "lua_framework_extra.h"
#include "framework.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"

int tolua_psframework_EventNode_registerScriptTouchHandler(lua_State *tolua_S)
{
	if (!tolua_S)
		return 0;

	int argc = 0;
	framework::EventNode *pNode = nullptr;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S, 1, "pf.EventNode", 0, &tolua_err)) 
		goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)	// if has param
	{
#if COCOS2D_DEBUG >= 1
		if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
			goto tolua_lerror;
#endif
		LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);

		return 0;
	}
	
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptTapHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_psframework_EventNode_registerScriptKeyboardHandler(lua_State *tolua_S)
{
	return 0;
}