#ifndef __VERSION_H__
#define __VERSION_H__

/***********************************************
UPDATE LOG:
v1.00	Add cocos2d-x lua based essential components to the framework.
v1.01	Add some UI and utilities for the project.
v1.02	Add some encrytion mechanism to the framework.
v1.03	Add ListMenu to the framework.
v1.04	Add ImageUtils to deal with gif images.
v1.05	Add ZipHelper to handle zip compression.
v1.06	Add win32 keyboard support into the framework.
v1.07	Add AES encryption and standard save data support.
v1.08	Add TitleSwitch control to the framework.
v1.09	Integrate lanes lib to the framework.
v1.10	Add gif decode method in other platform excluding win32, fix zip on ios issue.
v1.11	Add simple threading to the framework, threading features will be expanded in the future.
v1.12   Add net service base to the framework, to expand net services in the future.
v1.13	Add DirectionController control.
v1.14   Add http service and json elements.
v1.15	Add xml elements without xpath, which may be completed in the future.
v1.16   Add CheckedButton control.
***********************************************/

#include <iostream>
#include "tolua_fix.h"

static const char *VERSION = "v1.16";
static float VERSION_NUM = 1.16;

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