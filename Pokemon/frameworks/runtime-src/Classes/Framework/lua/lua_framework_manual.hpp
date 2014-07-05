/******************************
Description: Manual lua-binding code.
Author: M.Wan
Date: 7/5/2014
******************************/

#ifndef __psframework_manual_h__
#define __psframework_manual_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "LuaScriptHandlerMgr.h"

int register_all_psframework_manual(lua_State* tolua_S);

struct LuaListMenuEventData
{
	void *_value;

	LuaListMenuEventData(void *value = nullptr)
		: _value(value)
	{
	}
};

#endif