/******************************
	Description: While lua-binding doesn't support std::function and std::bind, we have to rewrite a new function to bind lua functions to callbacks.
	Author: M.Wan
	Date: 4/24/2014
******************************/

#ifndef __psframework_extra__
#define __psframework_extra__

#include "tolua++.h"

// EventNode touch callback bind
int tolua_psframework_EventNode_registerScriptTouchHandler(lua_State *tolua_S);
int tolua_psframework_EventNode_unregisterScriptTouchHandler(lua_State *tolua_S);

// EventNode keyboard callback bind
int tolua_psframework_EventNode_registerScriptKeyboardHandler(lua_State *tolua_S);
int tolua_psframework_EventNode_unregisterScriptKeyboardHandler(lua_State *tolua_S);

#endif