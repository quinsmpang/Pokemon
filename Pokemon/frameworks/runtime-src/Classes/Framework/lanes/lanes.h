#ifndef __LANES_H__
#define __LANES_H__

extern "C" {
#include "src/lanes.h"
}

/****************
Embbed lanes
****************/

static int load_lanes_lua(lua_State *L)
{
	// retrieve lanes
	luaL_dofile(L, "src/framework/lanes/lanes.lua");

	return 0;
}

void lua_register_lanes(lua_State *L)
{
	luaopen_lanes_embedded(L, load_lanes_lua);
	lua_pop(L, 1);
}

#endif