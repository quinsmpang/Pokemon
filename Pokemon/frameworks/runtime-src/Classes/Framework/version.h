#ifndef __VERSION_H__
#define __VERSION_H__

/***********************************************
UPDATE LOG:
v1.00	Add cocos2d-x lua based essential components to the framework
v1.01	Add some UI and utilities for the project
v1.02	Add some encrytion mechanism to the framework
v1.03	Add ListMenu to the framework
v1.04	Add ImageUtils to deal with gif images
v1.05	Add ZipHelper to handle zip compression
v1.06	Add win32 keyboard support into the framework
v1.07	Add AES encryption and standard save data support
v1.08	Add TitleSwitch control to the framework
***********************************************/

#include <iostream>
#include "tolua_fix.h"

static const char *VERSION = "v1.08";
static float VERSION_NUM = 1.08;

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