#include "lua_framework_manual.hpp"
#include "framework.h"
#include "LuaBasicConversions.h"
#include "LuaEngineEx.h"
#include "tolua_fix.h"


using namespace cocos2d;
using namespace framework;

#define KEY_LISTMENU_DELEGATE "ListMenuDelegate"
#define KEY_LISTMENU_DATASOURCE "ListMenuDataSource"

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
	if (!tolua_isusertype(L,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

	self = (ListMenu*)  tolua_tousertype(L,1,0);

#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
	{
		tolua_error(L,"invalid 'self' in function 'lua_framework_ListMenu_setScriptDelegate'\n", nullptr);
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
	tolua_error(L,"#ferror in function 'setScriptDelegate'.",&tolua_err);
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
					height  = (float)tolua_tonumber(L, -1, 0);
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
	if (!tolua_isusertype(L,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

	self = (ListMenu*)  tolua_tousertype(L,1,0);

#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
	{
		tolua_error(L,"invalid 'self' in function 'lua_framework_ListMenu_setScriptDataSource'\n", nullptr);
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
	tolua_error(L,"#ferror in function 'setScriptDataSource'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

	self = (ListMenu*)  tolua_tousertype(L,1,0);

#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
	{
		tolua_error(L,"invalid 'self' in function 'lua_framework_ListMenu_registerScriptHandler'\n", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (2 == argc)
	{
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(L, 3, 0, &tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
		LUA_FUNCTION handler = toluafix_ref_function(L,2,0);
		ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType) ((int)tolua_tonumber(L,3,0) + (int)ScriptHandlerMgr::HandlerType::LISTMENU_ITEMSELECTED);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, handlerType);

		return 0;
	}

	CCLOG("'registerScriptHandler' function of ListMenu wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L,"#ferror in function 'registerScriptHandler'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

	self = (ListMenu*)  tolua_tousertype(L,1,0);

#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
	{
		tolua_error(L,"invalid 'self' in function 'lua_framework_ListMenu_unregisterScriptHandler'\n", nullptr);
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
		ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType) ((int)tolua_tonumber(L,2,0) + (int)ScriptHandlerMgr::HandlerType::LISTMENU_ITEMSELECTED);
        
		ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);

		return 0;
	}

	CCLOG("'unregisterScriptHandler' function of ListMenu wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
	return 0;
#endif
}

static void register_framework_ListMenu_manual(lua_State *L)
{
	lua_pushstring(L, "pf.ListMenu");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
		tolua_function(L, "setScriptDelegate", lua_framework_ListMenu_setScriptDelegate);
		tolua_function(L, "setScriptDataSource", lua_framework_ListMenu_setScriptDataSource);
		tolua_function(L, "registerScriptHandler", lua_framework_ListMenu_registerScriptHandler);
		tolua_function(L, "unregisterScriptHandler", lua_framework_ListMenu_unregisterScriptHandler);
    }
    lua_pop(L, 1);
}

int register_all_psframework_manual(lua_State* tolua_S)
{
	register_framework_ListMenu_manual(tolua_S);

	return 0;
}