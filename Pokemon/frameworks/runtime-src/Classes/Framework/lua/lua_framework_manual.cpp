#include "lua_framework_manual.hpp"
#include "framework.h"
#include "Framework/threading/Thread.h"
#include "LuaBasicConversions.h"
#include "LuaEngineEx.h"
#include "tolua_fix.h"

using namespace cocos2d;
using namespace framework;

#define KEY_LISTMENU_DELEGATE "ListMenuDelegate"
#define KEY_LISTMENU_DATASOURCE "ListMenuDataSource"

/**********************************
ListMenu extend
**********************************/
class ListMenuScriptDelegate : public Ref, public ListMenuDelegate
{
public:
	ListMenuScriptDelegate() {}
	virtual ~ListMenuScriptDelegate() {}

	virtual void itemSelected(ListMenu *menu, ListMenuItem *item) override
	{
		if (menu && item)
		{
			int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)menu, ScriptHandlerMgr::HandlerType::LISTMENU_ITEMSELECTED);
			if (handler)
			{
				LuaListMenuEventData eventData(item);
				BasicScriptData data(menu, &eventData);
				LuaEngineEx::getInstance()->handleFrameworkEvent(ScriptHandlerMgr::HandlerType::LISTMENU_ITEMSELECTED, (void*)&data);
			}
		}
	}

	virtual void itemFocused(ListMenu *menu, ListMenuItem *item) override
	{
		if (menu && item)
		{
			int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)menu, ScriptHandlerMgr::HandlerType::LISTMENU_ITEMFOCUSED);
			if (handler)
			{
				LuaListMenuEventData eventData(item);
				BasicScriptData data(menu, &eventData);
				LuaEngineEx::getInstance()->handleFrameworkEvent(ScriptHandlerMgr::HandlerType::LISTMENU_ITEMFOCUSED, (void*)&data);
			}
		}
	}

	virtual void itemBlurred(ListMenu *menu, ListMenuItem *item) override
	{
		if (menu && item)
		{
			int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)menu, ScriptHandlerMgr::HandlerType::LISTMENU_ITEMBLURRED);
			if (handler)
			{
				LuaListMenuEventData eventData(item);
				BasicScriptData data(menu, &eventData);
				LuaEngineEx::getInstance()->handleFrameworkEvent(ScriptHandlerMgr::HandlerType::LISTMENU_ITEMBLURRED, (void*)&data);
			}
		}
	}

	virtual void itemWillRecycle(ListMenu *menu, ListMenuItem *item) override
	{
		if (menu && item)
		{
			int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)menu, ScriptHandlerMgr::HandlerType::LISTMENU_ITEMWILLRECYCLE);
			if (handler)
			{
				LuaListMenuEventData eventData(item);
				BasicScriptData data(menu, &eventData);
				LuaEngineEx::getInstance()->handleFrameworkEvent(ScriptHandlerMgr::HandlerType::LISTMENU_ITEMWILLRECYCLE, (void*)&data);
			}
		}
	}
};

static int lua_framework_ListMenu_setScriptDelegate(lua_State *L)
{
	if (nullptr == L)
		return 0;

	int argc = 0;
	ListMenu* self = nullptr;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "pf.ListMenu", 0, &tolua_err)) goto tolua_lerror;
#endif

	self = (ListMenu*)tolua_tousertype(L, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
	{
		tolua_error(L, "invalid 'self' in function 'lua_framework_ListMenu_setScriptDelegate'\n", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (0 == argc)
	{
		ListMenuScriptDelegate* delegate = new ListMenuScriptDelegate();
		if (nullptr == delegate)
			return 0;

		__Dictionary* userDict = static_cast<__Dictionary*>(self->getUserObject());
		if (nullptr == userDict)
		{
			userDict = new __Dictionary();
			if (NULL == userDict)
				return 0;

			self->setUserObject(userDict);
			userDict->release();
		}

		userDict->setObject(delegate, KEY_LISTMENU_DELEGATE);
		self->setDelegate(delegate);
		delegate->release();

		return 0;
	}

	CCLOG("'setScriptDelegate' function of ListMenu wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L, "#ferror in function 'setScriptDelegate'.", &tolua_err);
	return 0;
#endif
}

class ListMenuScriptDataSource : public Ref, public ListMenuDataSource
{
public:
	ListMenuScriptDataSource() {}
	virtual ~ListMenuScriptDataSource() {}

	virtual const Size &itemSizeForMenu(ListMenu *menu) override
	{
		if (nullptr != menu)
		{
			int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)menu, ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_SIZE_FOR_MENU);
			if (0 != handler)
			{
				LuaListMenuEventData eventData;
				BasicScriptData data(menu, &eventData);
				float width = 0.0;
				float height = 0.0;
				LuaEngineEx::getInstance()->handleFrameworkEvent(ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_SIZE_FOR_MENU, (void*)&data, 2, [&](lua_State* L, int numReturn){
					CCASSERT(numReturn == 2, "itemSizeForMenu return count error");
					ValueVector vec;
					height = (float)tolua_tonumber(L, -1, 0);
					lua_pop(L, 1);
					width = (float)tolua_tonumber(L, -1, 0);
					lua_pop(L, 1);
				});

				return Size(width, height);
			}
		}

		return Size::ZERO;
	}

	virtual ListMenuItem *itemAtIndex(ListMenu *menu, ssize_t index) override
	{
		if (nullptr != menu)
		{
			int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)menu, ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_AT_INDEX);
			if (0 != handler)
			{
				LuaListMenuEventData eventData(&index);
				BasicScriptData data(menu, &eventData);
				ListMenuItem* item = nullptr;
				LuaEngineEx::getInstance()->handleFrameworkEvent(ScriptHandlerMgr::HandlerType::LISTMENU_ITEM_AT_INDEX, (void*)&data, 1, [&](lua_State* L, int numReturn){
					CCASSERT(numReturn == 1, "itemAtIndex return count error");
					item = static_cast<ListMenuItem*>(tolua_tousertype(L, -1, nullptr));
					lua_pop(L, 1);
				});

				return item;
			}
		}

		return nullptr;
	}

	virtual ssize_t countOfItemsInMenu(ListMenu *menu) override
	{
		if (nullptr != menu)
		{
			int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)menu, ScriptHandlerMgr::HandlerType::LISTMENU_COUNT_OF_ITEMS);
			if (0 != handler)
			{
				LuaListMenuEventData eventData;
				BasicScriptData data(menu, &eventData);
				ssize_t count = 0;
				LuaEngineEx::getInstance()->handleFrameworkEvent(ScriptHandlerMgr::HandlerType::LISTMENU_COUNT_OF_ITEMS, (void*)&data, 1, [&](lua_State* L, int numReturn){
					CCASSERT(numReturn == 1, "countOfItemsInMenu return count error");
					count = (ssize_t)tolua_tonumber(L, -1, 0);
					lua_pop(L, 1);
				});

				return count;
			}
		}

		return 0;
	}
};

static int lua_framework_ListMenu_setScriptDataSource(lua_State *L)
{
	if (nullptr == L)
		return 0;

	int argc = 0;
	ListMenu* self = nullptr;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "pf.ListMenu", 0, &tolua_err)) goto tolua_lerror;
#endif

	self = (ListMenu*)tolua_tousertype(L, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
	{
		tolua_error(L, "invalid 'self' in function 'lua_framework_ListMenu_setScriptDataSource'\n", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (0 == argc)
	{
		ListMenuScriptDataSource* dataSource = new ListMenuScriptDataSource();
		if (nullptr == dataSource)
			return 0;

		__Dictionary* userDict = static_cast<__Dictionary*>(self->getUserObject());
		if (nullptr == userDict)
		{
			userDict = new __Dictionary();
			if (NULL == userDict)
				return 0;

			self->setUserObject(userDict);
			userDict->release();
		}

		userDict->setObject(dataSource, KEY_LISTMENU_DATASOURCE);
		self->setDataSource(dataSource);
		dataSource->release();

		return 0;
	}

	CCLOG("'setScriptDataSource' function of ListMenu wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L, "#ferror in function 'setScriptDataSource'.", &tolua_err);
	return 0;
#endif
}

static int lua_framework_ListMenu_registerScriptHandler(lua_State *L)
{
	if (nullptr == L)
		return 0;

	int argc = 0;
	ListMenu* self = nullptr;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "pf.ListMenu", 0, &tolua_err)) goto tolua_lerror;
#endif

	self = (ListMenu*)tolua_tousertype(L, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
	{
		tolua_error(L, "invalid 'self' in function 'lua_framework_ListMenu_registerScriptHandler'\n", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (2 == argc)
	{
#if COCOS2D_DEBUG >= 1
		if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err) ||
			!tolua_isnumber(L, 3, 0, &tolua_err))
		{
			goto tolua_lerror;
		}
#endif
		LUA_FUNCTION handler = toluafix_ref_function(L, 2, 0);
		ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType) ((int)tolua_tonumber(L, 3, 0) + (int)ScriptHandlerMgr::HandlerType::LISTMENU_ITEMSELECTED);

		ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, handlerType);

		return 0;
	}

	CCLOG("'registerScriptHandler' function of ListMenu wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L, "#ferror in function 'registerScriptHandler'.", &tolua_err);
	return 0;
#endif
}

static int lua_framework_ListMenu_unregisterScriptHandler(lua_State *L)
{
	if (nullptr == L)
		return 0;

	int argc = 0;
	ListMenu* self = nullptr;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "pf.ListMenu", 0, &tolua_err)) goto tolua_lerror;
#endif

	self = (ListMenu*)tolua_tousertype(L, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
	{
		tolua_error(L, "invalid 'self' in function 'lua_framework_ListMenu_unregisterScriptHandler'\n", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (1 == argc)
	{
#if COCOS2D_DEBUG >= 1
		if (!tolua_isnumber(L, 2, 0, &tolua_err))
			goto tolua_lerror;
#endif
		ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType) ((int)tolua_tonumber(L, 2, 0) + (int)ScriptHandlerMgr::HandlerType::LISTMENU_ITEMSELECTED);

		ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);

		return 0;
	}

	CCLOG("'unregisterScriptHandler' function of ListMenu wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L, "#ferror in function 'unregisterScriptHandler'.", &tolua_err);
	return 0;
#endif
}

static void extendListMenu(lua_State *L)
{
	lua_pushstring(L, "pf.ListMenu");
	lua_rawget(L, LUA_REGISTRYINDEX);
	if (lua_istable(L, -1))
	{
		tolua_function(L, "setScriptDelegate", lua_framework_ListMenu_setScriptDelegate);
		tolua_function(L, "setScriptDataSource", lua_framework_ListMenu_setScriptDataSource);
		tolua_function(L, "registerScriptHandler", lua_framework_ListMenu_registerScriptHandler);
		tolua_function(L, "unregisterScriptHandler", lua_framework_ListMenu_unregisterScriptHandler);
	}
	lua_pop(L, 1);
}

/**********************************
TitleSwitch extend
**********************************/
static int lua_framework_TitleSwitch_create(lua_State* tolua_S)
{
	if (NULL == tolua_S)
		return 0;

	int argc = 0;

	tolua_Error tolua_err;

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "pf.TitleSwitch", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc > 0)
	{
		if (3 == argc && tolua_istable(tolua_S, 3, 0, &tolua_err))
		{
			tolua_Error err;

			// bg
			Node *bg = static_cast<Node*>(tolua_tousertype(tolua_S, 2, 0));
			if (!bg)
			{
				goto tolua_lerror;
			}

			// string vector
			std::vector<std::string> ary;

			size_t len = lua_objlen(tolua_S, 3);
			for (int i = 0; i < len; i++)
			{
				lua_pushnumber(tolua_S, i + 1);		// L: userdata, bg, titles, ttf, i+1
				lua_gettable(tolua_S, 3);

				if (lua_isnil(tolua_S, -1))
				{
					lua_pop(tolua_S, 1);
					continue;
				}

				if (!tolua_isstring(tolua_S, -1, 0, &err))
				{
					goto tolua_lerror;
				}
				std::string title = tolua_tostring(tolua_S, -1, NULL);		// L: userdata, bg, titles, ttf, i+1, string
				ary.push_back(title);

				lua_pop(tolua_S, 1);		// L: userdata, bg, titles, ttf
			}

			// ttf path
			if (!tolua_isstring(tolua_S, 4, 0, &err))
			{
				goto tolua_lerror;
			}
			std::string ttfPath = tolua_tostring(tolua_S, 4, NULL);		// L: userdata, bg, titles, ttf, string

			TitleSwitch *tolua_ret = TitleSwitch::create(bg, ary, ttfPath);

			lua_pop(tolua_S, 1);

			int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
			int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
			toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret, "pf.TitleSwitch");
			return 1;
		}
	}
	CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'create'.", &tolua_err);
	return 0;
#endif
}
static int lua_framework_TitleSwitch_setTitles(lua_State* tolua_S)
{
	int argc = 0;
	framework::TitleSwitch* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "pf.TitleSwitch", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_framework_TitleSwitch_setTitles'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)
	{
		tolua_Error err;

		std::vector<std::string> ary;

		size_t len = lua_objlen(tolua_S, 2);
		for (int i = 0; i < len; i++)
		{
			lua_pushnumber(tolua_S, i + 1);		// L: userdata, titles, i+1
			lua_gettable(tolua_S, 2);

			if (lua_isnil(tolua_S, -1))
			{
				lua_pop(tolua_S, 1);		// L: userdata, titles
				continue;
			}

			if (!tolua_isstring(tolua_S, -1, 0, &err))
			{
				lua_pop(tolua_S, 1);		// L: userdata, titles
				goto tolua_lerror;
			}
			std::string title = tolua_tostring(tolua_S, -1, NULL);		// L: userdata, titles, string
			ary.push_back(title);

			lua_pop(tolua_S, 1);		// L: userdata, titles
		}

		cobj->setTitles(ary);
	}
	CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTitles", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_framework_TitleSwitch_setTitles'.", &tolua_err);
#endif

	return 0;
}

static void extendTitleSwitch(lua_State* tolua_S)
{
	lua_pushstring(tolua_S, "pf.TitleSwitch");
	lua_rawget(tolua_S, LUA_REGISTRYINDEX);
	if (lua_istable(tolua_S, -1))
	{
		lua_pushstring(tolua_S, "create");
		lua_pushcfunction(tolua_S, lua_framework_TitleSwitch_create);
		lua_rawset(tolua_S, -3);
		lua_pushstring(tolua_S, "setTitles");
		lua_pushcfunction(tolua_S, lua_framework_TitleSwitch_setTitles);
		lua_rawset(tolua_S, -3);
	}
	lua_pop(tolua_S, 1);
}

/**********************************
Thread extend
**********************************/
static int lua_framework_Thread_constructor(lua_State* tolua_S)
{
	int argc = 0;
	framework::Thread* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
			return 0;
		cobj = new framework::Thread();
		tolua_pushusertype(tolua_S, (void*)cobj, "pf.Thread");
		tolua_register_gc(tolua_S, lua_gettop(tolua_S));
		return 1;
	}
	CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Thread", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
	tolua_error(tolua_S, "#ferror in function 'lua_framework_Thread_constructor'.", &tolua_err);
#endif

	return 0;
}

static int lua_framework_Thread_run(lua_State *tolua_S)
{
	int argc = 0;
	framework::Thread* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "pf.Thread", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (framework::Thread*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_framework_Thread_run'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc >= 1)
	{
		int numArgs = argc - 1;

		lua_State *L = tolua_S;
		// copy a new lua_State based on original lua_State for the new thread
		lua_State *L2 = lua_newthread(L);

		// save L2 to the registry table, otherwise it will be collected.
		// use L2's address as key
		char szKey[256] = { 0 };
		sprintf(szKey, "0x%x", L2);
		lua_pushvalue(L, -1);		// copy L2 to the top
		lua_setfield(L, LUA_REGISTRYINDEX, szKey);
		char *key = szKey;		// array can't be captured by lambda [=]

		// clean L2
		lua_settop(L2, 0);
		// L should be like: L: Thread, luaHandler, args...
		luaL_argcheck(L, lua_isfunction(L, 2) && !lua_iscfunction(L, 2), 1, "Lua function expected");
		lua_pushvalue(L, 2);  // copy function to top
		lua_xmove(L, L2, 1);  // move function from L to L2
		// copy the params of luaHandler from L to L2
		for (int i = 1; i <= numArgs; ++i)
		{
			lua_pushvalue(L, i + 2);
			lua_xmove(L, L2, 1);
		}
		lua_pop(L, 1);

		// L2: luaHandler, args...
		cobj->run([L, L2, numArgs, key] {
			// get pcall error handler
			lua_getglobal(L2, "__G__TRACKBACK__");		// L2: luaHandler, args..., __G__TRACKBACK__
			lua_insert(L2, 1);		// L2: __G__TRACKBACK__, luaHandler, args...
			int err = lua_pcall(L2, numArgs, 1, 1);
			if (err)
			{
				// L2: __G__TRACKBACK__, msg
				CCLOG("[LUA ERROR] %s", lua_tostring(L2, -1));
				lua_pop(L2, 2);
				return;
			}
			// clean the registry key
			lua_lock(L);
			lua_pushnil(L);
			lua_setfield(L, LUA_REGISTRYINDEX, key);
			lua_unlock(L);
			lua_pop(L2, 1);	// pop out the return value
		});

		return 0;
	}
	CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "run", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_framework_Thread_run'.", &tolua_err);
#endif

	return 0;
}

static int lua_framework_Thread_runAsync(lua_State* tolua_S)
{
	int argc = 0;
	framework::Thread* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "pf.Thread", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (framework::Thread*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_framework_Thread_runAsync'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc >= 1)
	{
		int numArgs = argc - 1;

		lua_State *L = tolua_S;
		// copy a new lua_State based on original lua_State for the new thread
		lua_State *L2 = lua_newthread(L);
		// clean L2
		lua_settop(L2, 0);

		// save L2 to the registry table, otherwise it will be collected.
		// use L2's address as key
		char szKey[256] = { 0 };
		sprintf(szKey, "0x%x", L2);
		lua_pushvalue(L, -1);		// copy L2 to the top
		lua_setfield(L, LUA_REGISTRYINDEX, szKey);
		char *key = szKey;		// array can't be captured by lambda [=]

		// L should be like: L: Thread, luaHandler, args...
		luaL_argcheck(L, lua_isfunction(L, 2) && !lua_iscfunction(L, 2), 1, "Lua function expected");
		lua_pushvalue(L, 2);  // copy function to top
		lua_xmove(L, L2, 1);  // move function from L to L2
		// copy the params of luaHandler from L to L2
		for (int i = 1; i <= numArgs; ++i)
		{
			lua_pushvalue(L, i + 2);
			lua_xmove(L, L2, 1);
		}

		// L2: luaHandler, args...
		static unsigned int counter = 0;
		std::string gKey;
		bool ret = cobj->runAsync([L, L2, numArgs, key, &gKey] {
			// get pcall error handler
			lua_getglobal(L2, "__G__TRACKBACK__");		// L2: luaHandler, args..., __G__TRACKBACK__
			lua_insert(L2, 1);		// L2: __G__TRACKBACK__, luaHandler, args...
			int err = lua_pcall(L2, numArgs, 1, 1);
			if (err)
			{
				// L2: __G__TRACKBACK__, msg
				CCLOG("[LUA ERROR] %s", lua_tostring(L2, -1));
				lua_pop(L2, 2);
				return false;
			}
			// copy the return value to L
			//LuaEngineEx::getInstance()->copyBetweenLuaStates(L2, L);
			// use shared _G instead
			char buffer[256] = { 0 };
			counter++;
			sprintf((char*)buffer, "__FRAMEWORK_GLOBAL_THREAD_RET_VAL_%d__", counter);
			// transfer the return value by _G
			CCLOG("!!%d", lua_gettop(L2));
			lua_setglobal(L2, buffer);
			gKey = buffer;
			// clean the registry key
			lua_lock(L);
			lua_pushnil(L);
			lua_setfield(L, LUA_REGISTRYINDEX, key);
			lua_unlock(L);
			lua_pop(L2, 1);
			return true;
		});
		if (ret)
		{
			// why no use?
			lua_getglobal(tolua_S, gKey.c_str());
			return 1;
		}
		return 0;
	}
	CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "join", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_framework_Thread_runAsync'.", &tolua_err);
#endif

	return 0;
}

static int lua_framework_Thread_join(lua_State* tolua_S)
{
	int argc = 0;
	framework::Thread* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "pf.Thread", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (framework::Thread*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_framework_Thread_join'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
			return 0;
		bool ret = cobj->join();
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "join", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_framework_Thread_join'.", &tolua_err);
#endif

	return 0;
}

static int lua_framework_Thread_detach(lua_State* tolua_S)
{
	int argc = 0;
	framework::Thread* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "pf.Thread", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (framework::Thread*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_framework_Thread_detach'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
			return 0;
		cobj->detach();
		return 0;
	}
	CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "detach", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_framework_Thread_detach'.", &tolua_err);
#endif

	return 0;
}

static void extendThread(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "pf.Thread");
	tolua_cclass(tolua_S, "Thread", "pf.Thread", "cc.Ref", nullptr);

	tolua_beginmodule(tolua_S, "Thread");
	tolua_function(tolua_S, "new", lua_framework_Thread_constructor);
	tolua_function(tolua_S, "run", lua_framework_Thread_run);
	tolua_function(tolua_S, "runAsync", lua_framework_Thread_runAsync);
	tolua_function(tolua_S, "join", lua_framework_Thread_join);
	tolua_function(tolua_S, "detach", lua_framework_Thread_detach);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(framework::Thread).name();
	g_luaType[typeName] = "pf.Thread";
	g_typeCast["Thread"] = "pf.Thread";
}

/**********************************
Win32EventListenerKeyboard extend
**********************************/
static int lua_framework_Win32EventListenerKeyboard_unregisterScriptWin32Handler(lua_State* tolua_S)
{
	int argc = 0;
	framework::Win32EventListenerKeyboard* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "pf.Win32EventListenerKeyboard", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (framework::Win32EventListenerKeyboard*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_framework_Win32EventListenerKeyboard_unregisterScriptWin32Handler'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)
	{
		int arg0;

		ok &= luaval_to_int32(tolua_S, 2, (int *)&arg0);
		if (!ok)
			return 0;
		cobj->unregisterScriptWin32Handler(arg0);
		return 0;
	}
	CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unregisterScriptWin32Handler", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_framework_Win32EventListenerKeyboard_unregisterScriptWin32Handler'.", &tolua_err);
#endif

	return 0;
}
static int lua_framework_Win32EventListenerKeyboard_registerScriptWin32Handler(lua_State* tolua_S)
{
	int argc = 0;
	framework::Win32EventListenerKeyboard* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "pf.Win32EventListenerKeyboard", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (framework::Win32EventListenerKeyboard*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_framework_Win32EventListenerKeyboard_registerScriptWin32Handler'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 2)
	{
		LUA_FUNCTION arg0 = toluafix_ref_function(tolua_S, 2, 0);;
		int arg1;

		ok &= luaval_to_int32(tolua_S, 3, (int *)&arg1);
		if (!ok)
			return 0;
		cobj->registerScriptWin32Handler(arg0, arg1);
		return 0;
	}
	CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "registerScriptWin32Handler", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_framework_Win32EventListenerKeyboard_registerScriptWin32Handler'.", &tolua_err);
#endif

	return 0;
}

static void extendWin32EventListenerKeyboard(lua_State* tolua_S)
{
	lua_pushstring(tolua_S, "pf.Win32EventListenerKeyboard");
	lua_rawget(tolua_S, LUA_REGISTRYINDEX);
	if (lua_istable(tolua_S, -1))
	{
		lua_pushstring(tolua_S, "registerScriptWin32Handler");
		lua_pushcfunction(tolua_S, lua_framework_Win32EventListenerKeyboard_registerScriptWin32Handler);
		lua_rawset(tolua_S, -3);
		lua_pushstring(tolua_S, "unregisterScriptWin32Handler");
		lua_pushcfunction(tolua_S, lua_framework_Win32EventListenerKeyboard_unregisterScriptWin32Handler);
		lua_rawset(tolua_S, -3);
	}
	lua_pop(tolua_S, 1);
}

int register_all_psframework_manual(lua_State* tolua_S)
{
	extendListMenu(tolua_S);
	extendTitleSwitch(tolua_S);
	extendThread(tolua_S);
	extendWin32EventListenerKeyboard(tolua_S);

	return 0;
}