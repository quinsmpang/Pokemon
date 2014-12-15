#ifndef __LUA_THREAD__
#define __LUA_THREAD__

#define LUA_MULTI_THREADING_SUPPORTED 1

#if LUA_MULTI_THREADING_SUPPORTED
#include "lua.h"

/* To make lua state support multi-thread */
#define lua_lock(L) LuaLock(L)
#define lua_unlock(L) LuaUnlock(L)
#define luai_userstateopen(L) LuaInitializeLock(L)
#define luai_userstatethread(L, L1) LuaInitializeLock(L1)  // Lua 5.1
#define luai_userstateclose(L) LuaDestroyLock(L)		// can be closed only after the version of 5.1
#define luai_threadyield(L) ((void)NULL)

void LuaInitializeLock(lua_State *L);
void LuaDestroyLock(lua_State *L);
void LuaLock(lua_State *L);
void LuaUnlock(lua_State *L);
//void LuaThreadYield(lua_State *L);

#endif
#endif