#ifndef __VERSION_H__
#define __VERSION_H__

#include <iostream>
#include "tolua_fix.h"

static const char *VERSION = "v1.00";
static float VERSION_NUM = 1.00;

void printVersion()
{
	printf("\n/**************************************************/\npsframework current version: %s\n/**************************************************/\n\n", VERSION);
} 

void lua_register_psframework_version(lua_State *tolua_S)
{
	lua_pushstring(tolua_S, VERSION);
	lua_setglobal(tolua_S, "PSFrameworkVersionStr");
	lua_pop(tolua_S, -2);

	lua_pushnumber(tolua_S, VERSION_NUM);
	lua_setglobal(tolua_S, "PSFrameworkVersionNumber");
	lua_pop(tolua_S, -2);
}

#endif