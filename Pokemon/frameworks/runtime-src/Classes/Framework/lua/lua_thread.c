#include "lua_thread.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

static struct {
#ifdef _WIN32
	CRITICAL_SECTION _lock;
#else
	pthread_mutex_t _lock;
#endif
	BOOL _inited;
} g_lock;

void LuaInitializeLock(lua_State *L)
{
	if (!g_lock._inited)
	{
		/* Create a mutex */
#ifdef _WIN32
		InitializeCriticalSection(&g_lock._lock);
#else
		pthread_mutex_init(&g_lock._lock, NULL);
#endif
		g_lock._inited = TRUE;
	}
}

void LuaDestroyLock(lua_State *L)
{
	if (g_lock._inited)
	{
		/* Destroy the mutex */
#ifdef _WIN32
		DeleteCriticalSection(&g_lock._lock);
#else
		pthread_mutex_destroy(&g_lock._lock);
#endif
		g_lock._inited = FALSE;
	}
}

void LuaLock(lua_State *L)
{
#ifdef _WIN32
	EnterCriticalSection(&g_lock._lock);
#else
	pthread_mutex_lock(&g_lock._lock);
#endif
}

void LuaUnlock(lua_State *L)
{
#ifdef _WIN32
	LeaveCriticalSection(&g_lock._lock);
#else
	pthread_mutex_unlock(&g_lock._lock);
#endif
}