/******************************
 Description: Lua decryption loader.
 Author: M.Wan
 Date: 01/13/2015
 ******************************/

#ifndef __LUA_DECRYPTION_LOADER__
#define __LUA_DECRYPTION_LOADER__

#define LUA_DECIPHER_KEY "~!@#$%^&*()_+"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
    
    int framework_decipher_loader(lua_State *L);
}

#endif /* defined(__LUA_DECRYPTION_LOADER__) */
