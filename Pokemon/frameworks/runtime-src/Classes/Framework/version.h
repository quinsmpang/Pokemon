#ifndef __VERSION_H__
#define __VERSION_H__

/***********************************************
UPDATE LOG:
v1.00	Add cocos2d-x lua based essential components to the framework
v1.01		Add some UI and utilities for the project
v1.02	Add some encrytion mechanism to the framework
v1.03	Add ListMenu to the framework
***********************************************/

#include <iostream>
#include "tolua_fix.h"

static const char *VERSION = "v1.03";
static float VERSION_NUM = 1.03;

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