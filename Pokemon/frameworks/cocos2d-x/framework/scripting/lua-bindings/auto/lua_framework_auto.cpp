#include "lua_framework_auto.hpp"
#include "framework.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_framework_ViewController_load(lua_State* tolua_S)
{
    int argc = 0;
    framework::ViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_ViewController_load'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->load();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "load",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_ViewController_load'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_ViewController_setScene(lua_State* tolua_S)
{
    int argc = 0;
    framework::ViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_ViewController_setScene'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::GameScene* arg0;

        ok &= luaval_to_object<framework::GameScene>(tolua_S, 2, "ps.GameScene",&arg0);
        if(!ok)
            return 0;
        cobj->setScene(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setScene",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_ViewController_setScene'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_ViewController_init(lua_State* tolua_S)
{
    int argc = 0;
    framework::ViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_ViewController_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_ViewController_init'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_ViewController_getScene(lua_State* tolua_S)
{
    int argc = 0;
    framework::ViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_ViewController_getScene'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::GameScene* ret = cobj->getScene();
        object_to_luaval<framework::GameScene>(tolua_S, "ps.GameScene",(framework::GameScene*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getScene",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_ViewController_getScene'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_ViewController_unload(lua_State* tolua_S)
{
    int argc = 0;
    framework::ViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_ViewController_unload'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->unload();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unload",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_ViewController_unload'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_ViewController_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ps.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::ViewController* ret = framework::ViewController::create();
        object_to_luaval<framework::ViewController>(tolua_S, "ps.ViewController",(framework::ViewController*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_ViewController_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_framework_ViewController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ViewController)");
    return 0;
}

int lua_register_framework_ViewController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ps.ViewController");
    tolua_cclass(tolua_S,"ViewController","ps.ViewController","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ViewController");
        tolua_function(tolua_S,"load",lua_framework_ViewController_load);
        tolua_function(tolua_S,"setScene",lua_framework_ViewController_setScene);
        tolua_function(tolua_S,"init",lua_framework_ViewController_init);
        tolua_function(tolua_S,"getScene",lua_framework_ViewController_getScene);
        tolua_function(tolua_S,"unload",lua_framework_ViewController_unload);
        tolua_function(tolua_S,"create", lua_framework_ViewController_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ViewController).name();
    g_luaType[typeName] = "ps.ViewController";
    g_typeCast["ViewController"] = "ps.ViewController";
    return 1;
}

int lua_framework_GameScene_loadViewController(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_loadViewController'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::ViewController* arg0;

        ok &= luaval_to_object<framework::ViewController>(tolua_S, 2, "ps.ViewController",&arg0);
        if(!ok)
            return 0;
        cobj->loadViewController(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "loadViewController",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_loadViewController'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_putIntAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_putIntAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->putIntAttribute(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "putIntAttribute",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_putIntAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_getRefAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_getRefAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cocos2d::Ref* ret = cobj->getRefAttribute(arg0);
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRefAttribute",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_getRefAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_putBoolAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_putBoolAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_boolean(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->putBoolAttribute(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "putBoolAttribute",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_putBoolAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_getDoubleAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_getDoubleAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        double ret = cobj->getDoubleAttribute(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDoubleAttribute",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_getDoubleAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_unloadViewController(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_unloadViewController'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::ViewController* arg0;

        ok &= luaval_to_object<framework::ViewController>(tolua_S, 2, "ps.ViewController",&arg0);
        if(!ok)
            return 0;
        cobj->unloadViewController(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unloadViewController",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_unloadViewController'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_unloadAllViewControllers(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_unloadAllViewControllers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->unloadAllViewControllers();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unloadAllViewControllers",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_unloadAllViewControllers'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_init(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_init'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_putDoubleAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_putDoubleAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        double arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->putDoubleAttribute(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "putDoubleAttribute",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_putDoubleAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_putStringAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_putStringAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->putStringAttribute(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "putStringAttribute",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_putStringAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_putRefAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_putRefAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocos2d::Ref* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 3, "cc.Ref",&arg1);
        if(!ok)
            return 0;
        cobj->putRefAttribute(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "putRefAttribute",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_putRefAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_getIntAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_getIntAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        int ret = cobj->getIntAttribute(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIntAttribute",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_getIntAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_getBoolAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_getBoolAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->getBoolAttribute(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBoolAttribute",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_getBoolAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_getStringAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameScene_getStringAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        const char* ret = cobj->getStringAttribute(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getStringAttribute",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_getStringAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameScene_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ps.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            cocos2d::__Dictionary* arg0;
            ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 2, "cc.__Dictionary",&arg0);
            if (!ok) { break; }
            framework::GameScene* ret = framework::GameScene::create(arg0);
            object_to_luaval<framework::GameScene>(tolua_S, "ps.GameScene",(framework::GameScene*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            framework::GameScene* ret = framework::GameScene::create();
            object_to_luaval<framework::GameScene>(tolua_S, "ps.GameScene",(framework::GameScene*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameScene_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_framework_GameScene_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameScene)");
    return 0;
}

int lua_register_framework_GameScene(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ps.GameScene");
    tolua_cclass(tolua_S,"GameScene","ps.GameScene","cc.Scene",nullptr);

    tolua_beginmodule(tolua_S,"GameScene");
        tolua_function(tolua_S,"loadViewController",lua_framework_GameScene_loadViewController);
        tolua_function(tolua_S,"putIntAttribute",lua_framework_GameScene_putIntAttribute);
        tolua_function(tolua_S,"getRefAttribute",lua_framework_GameScene_getRefAttribute);
        tolua_function(tolua_S,"putBoolAttribute",lua_framework_GameScene_putBoolAttribute);
        tolua_function(tolua_S,"getDoubleAttribute",lua_framework_GameScene_getDoubleAttribute);
        tolua_function(tolua_S,"unloadViewController",lua_framework_GameScene_unloadViewController);
        tolua_function(tolua_S,"unloadAllViewControllers",lua_framework_GameScene_unloadAllViewControllers);
        tolua_function(tolua_S,"init",lua_framework_GameScene_init);
        tolua_function(tolua_S,"putDoubleAttribute",lua_framework_GameScene_putDoubleAttribute);
        tolua_function(tolua_S,"putStringAttribute",lua_framework_GameScene_putStringAttribute);
        tolua_function(tolua_S,"putRefAttribute",lua_framework_GameScene_putRefAttribute);
        tolua_function(tolua_S,"getIntAttribute",lua_framework_GameScene_getIntAttribute);
        tolua_function(tolua_S,"getBoolAttribute",lua_framework_GameScene_getBoolAttribute);
        tolua_function(tolua_S,"getStringAttribute",lua_framework_GameScene_getStringAttribute);
        tolua_function(tolua_S,"create", lua_framework_GameScene_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::GameScene).name();
    g_luaType[typeName] = "ps.GameScene";
    g_typeCast["GameScene"] = "ps.GameScene";
    return 1;
}

int lua_framework_EventNode_setEnabled(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventNode_setEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setEnabled(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventNode_setEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventNode_setSelected(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventNode_setSelected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setSelected(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSelected",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventNode_setSelected'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventNode_isEnabled(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventNode_isEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventNode_isEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventNode_focus(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventNode_focus'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->focus();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "focus",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventNode_focus'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventNode_setTouchCallback(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventNode_setTouchCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (cocos2d::Ref *)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        cobj->setTouchCallback(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTouchCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventNode_setTouchCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventNode_isSelected(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventNode_isSelected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isSelected();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isSelected",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventNode_isSelected'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventNode_blur(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventNode_blur'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->blur();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "blur",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventNode_blur'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventNode_setKeyboardCallback(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventNode_setKeyboardCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        cobj->setKeyboardCallback(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setKeyboardCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventNode_setKeyboardCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventNode_rect(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventNode_rect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Rect ret = cobj->rect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "rect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventNode_rect'.",&tolua_err);
#endif

    return 0;
}
static int lua_framework_EventNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventNode)");
    return 0;
}

int lua_register_framework_EventNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ps.EventNode");
    tolua_cclass(tolua_S,"EventNode","ps.EventNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"EventNode");
        tolua_function(tolua_S,"setEnabled",lua_framework_EventNode_setEnabled);
        tolua_function(tolua_S,"setSelected",lua_framework_EventNode_setSelected);
        tolua_function(tolua_S,"isEnabled",lua_framework_EventNode_isEnabled);
        tolua_function(tolua_S,"focus",lua_framework_EventNode_focus);
        tolua_function(tolua_S,"setTouchCallback",lua_framework_EventNode_setTouchCallback);
        tolua_function(tolua_S,"isSelected",lua_framework_EventNode_isSelected);
        tolua_function(tolua_S,"blur",lua_framework_EventNode_blur);
        tolua_function(tolua_S,"setKeyboardCallback",lua_framework_EventNode_setKeyboardCallback);
        tolua_function(tolua_S,"rect",lua_framework_EventNode_rect);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::EventNode).name();
    g_luaType[typeName] = "ps.EventNode";
    g_typeCast["EventNode"] = "ps.EventNode";
    return 1;
}

int lua_framework_EventLayer_onTouchMoved(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventLayer_onTouchMoved'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1);
        if(!ok)
            return 0;
        cobj->onTouchMoved(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onTouchMoved",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventLayer_onTouchMoved'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventLayer_onTouchEnded(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventLayer_onTouchEnded'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1);
        if(!ok)
            return 0;
        cobj->onTouchEnded(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onTouchEnded",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventLayer_onTouchEnded'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventLayer_enableTouch(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventLayer_enableTouch'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->enableTouch();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "enableTouch",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventLayer_enableTouch'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventLayer_onTouchCancelled(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventLayer_onTouchCancelled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1);
        if(!ok)
            return 0;
        cobj->onTouchCancelled(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onTouchCancelled",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventLayer_onTouchCancelled'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventLayer_onTouchBegan(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventLayer_onTouchBegan'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1);
        if(!ok)
            return 0;
        bool ret = cobj->onTouchBegan(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onTouchBegan",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventLayer_onTouchBegan'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventLayer_init(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventLayer_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventLayer_init'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventLayer_disableTouch(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.EventLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::EventLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_EventLayer_disableTouch'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->disableTouch();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "disableTouch",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventLayer_disableTouch'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_EventLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ps.EventLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::EventLayer* ret = framework::EventLayer::create();
        object_to_luaval<framework::EventLayer>(tolua_S, "ps.EventLayer",(framework::EventLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventLayer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_framework_EventLayer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::EventLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::EventLayer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ps.EventLayer");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "EventLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_framework_EventLayer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_framework_EventLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventLayer)");
    return 0;
}

int lua_register_framework_EventLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ps.EventLayer");
    tolua_cclass(tolua_S,"EventLayer","ps.EventLayer","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"EventLayer");
        tolua_function(tolua_S,"onTouchMoved",lua_framework_EventLayer_onTouchMoved);
        tolua_function(tolua_S,"onTouchEnded",lua_framework_EventLayer_onTouchEnded);
        tolua_function(tolua_S,"enableTouch",lua_framework_EventLayer_enableTouch);
        tolua_function(tolua_S,"onTouchCancelled",lua_framework_EventLayer_onTouchCancelled);
        tolua_function(tolua_S,"onTouchBegan",lua_framework_EventLayer_onTouchBegan);
        tolua_function(tolua_S,"init",lua_framework_EventLayer_init);
        tolua_function(tolua_S,"disableTouch",lua_framework_EventLayer_disableTouch);
        tolua_function(tolua_S,"new",lua_framework_EventLayer_constructor);
        tolua_function(tolua_S,"create", lua_framework_EventLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::EventLayer).name();
    g_luaType[typeName] = "ps.EventLayer";
    g_typeCast["EventLayer"] = "ps.EventLayer";
    return 1;
}

int lua_framework_GameLayer_getCoreLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_getCoreLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::GameLayer* ret = cobj->getCoreLayer();
        object_to_luaval<framework::GameLayer>(tolua_S, "ps.GameLayer",(framework::GameLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCoreLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_getCoreLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_setFocusNode(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_setFocusNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::EventNode* arg0;

        ok &= luaval_to_object<framework::EventNode>(tolua_S, 2, "ps.EventNode",&arg0);
        if(!ok)
            return 0;
        cobj->setFocusNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFocusNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_setFocusNode'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_setEventLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_setEventLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::EventLayer* arg0;

        ok &= luaval_to_object<framework::EventLayer>(tolua_S, 2, "ps.EventLayer",&arg0);
        if(!ok)
            return 0;
        cobj->setEventLayer(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setEventLayer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_setEventLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_isCoreLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_isCoreLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isCoreLayer();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isCoreLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_isCoreLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_getParentLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_getParentLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::GameLayer* ret = cobj->getParentLayer();
        object_to_luaval<framework::GameLayer>(tolua_S, "ps.GameLayer",(framework::GameLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getParentLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_getParentLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_removeControl(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_removeControl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::EventNode* arg0;

        ok &= luaval_to_object<framework::EventNode>(tolua_S, 2, "ps.EventNode",&arg0);
        if(!ok)
            return 0;
        cobj->removeControl(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeControl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_removeControl'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_pushLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_pushLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::GameLayer* arg0;

        ok &= luaval_to_object<framework::GameLayer>(tolua_S, 2, "ps.GameLayer",&arg0);
        if(!ok)
            return 0;
        cobj->pushLayer(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "pushLayer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_pushLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_removeControlByTag(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_removeControlByTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->removeControlByTag(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        int arg0;
        bool arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_boolean(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->removeControlByTag(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeControlByTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_removeControlByTag'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_popLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_popLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->popLayer();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "popLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_popLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_init(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_init'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_registerTouchEvents(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_registerTouchEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->registerTouchEvents();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "registerTouchEvents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_registerTouchEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_addControlByTag(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_addControlByTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        framework::EventNode* arg0;
        int arg1;

        ok &= luaval_to_object<framework::EventNode>(tolua_S, 2, "ps.EventNode",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->addControlByTag(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addControlByTag",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_addControlByTag'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_addControl(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_addControl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::EventNode* arg0;

        ok &= luaval_to_object<framework::EventNode>(tolua_S, 2, "ps.EventNode",&arg0);
        if(!ok)
            return 0;
        cobj->addControl(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addControl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_addControl'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_unregisterTouchEvents(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_GameLayer_unregisterTouchEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->unregisterTouchEvents();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unregisterTouchEvents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_unregisterTouchEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_GameLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ps.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::GameLayer* ret = framework::GameLayer::create();
        object_to_luaval<framework::GameLayer>(tolua_S, "ps.GameLayer",(framework::GameLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_framework_GameLayer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::GameLayer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ps.GameLayer");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_framework_GameLayer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_framework_GameLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameLayer)");
    return 0;
}

int lua_register_framework_GameLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ps.GameLayer");
    tolua_cclass(tolua_S,"GameLayer","ps.GameLayer","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"GameLayer");
        tolua_function(tolua_S,"getCoreLayer",lua_framework_GameLayer_getCoreLayer);
        tolua_function(tolua_S,"setFocusNode",lua_framework_GameLayer_setFocusNode);
        tolua_function(tolua_S,"setEventLayer",lua_framework_GameLayer_setEventLayer);
        tolua_function(tolua_S,"isCoreLayer",lua_framework_GameLayer_isCoreLayer);
        tolua_function(tolua_S,"getParentLayer",lua_framework_GameLayer_getParentLayer);
        tolua_function(tolua_S,"removeControl",lua_framework_GameLayer_removeControl);
        tolua_function(tolua_S,"pushLayer",lua_framework_GameLayer_pushLayer);
        tolua_function(tolua_S,"removeControlByTag",lua_framework_GameLayer_removeControlByTag);
        tolua_function(tolua_S,"popLayer",lua_framework_GameLayer_popLayer);
        tolua_function(tolua_S,"init",lua_framework_GameLayer_init);
        tolua_function(tolua_S,"registerTouchEvents",lua_framework_GameLayer_registerTouchEvents);
        tolua_function(tolua_S,"addControlByTag",lua_framework_GameLayer_addControlByTag);
        tolua_function(tolua_S,"addControl",lua_framework_GameLayer_addControl);
        tolua_function(tolua_S,"unregisterTouchEvents",lua_framework_GameLayer_unregisterTouchEvents);
        tolua_function(tolua_S,"new",lua_framework_GameLayer_constructor);
        tolua_function(tolua_S,"create", lua_framework_GameLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::GameLayer).name();
    g_luaType[typeName] = "ps.GameLayer";
    g_typeCast["GameLayer"] = "ps.GameLayer";
    return 1;
}

int lua_framework_MaskLayer_getDelegate(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_getDelegate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::MaskLayerDelegate* ret = cobj->getDelegate();
        object_to_luaval<framework::MaskLayerDelegate>(tolua_S, "ps.MaskLayerDelegate",(framework::MaskLayerDelegate*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDelegate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_getDelegate'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_setArea(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_setArea'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setArea(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setArea",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_setArea'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_setColor(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setColor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_setColor'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_getScriptDelegate(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_getScriptDelegate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Ref* ret = cobj->getScriptDelegate();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getScriptDelegate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_getScriptDelegate'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_getArea(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_getArea'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Rect ret = cobj->getArea();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getArea",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_getArea'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_setOpacity(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_setOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setOpacity(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setOpacity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_setOpacity'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_isInterceptAllEvents(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_isInterceptAllEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isInterceptAllEvents();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isInterceptAllEvents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_isInterceptAllEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_setDelegate(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_setDelegate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::MaskLayerDelegate* arg0;

        ok &= luaval_to_object<framework::MaskLayerDelegate>(tolua_S, 2, "ps.MaskLayerDelegate",&arg0);
        if(!ok)
            return 0;
        cobj->setDelegate(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDelegate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_setDelegate'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_forceInterceptAllEvents(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_forceInterceptAllEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->forceInterceptAllEvents(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "forceInterceptAllEvents",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_forceInterceptAllEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_setScriptDelegate(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_MaskLayer_setScriptDelegate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
            return 0;
        cobj->setScriptDelegate(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setScriptDelegate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_setScriptDelegate'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_MaskLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ps.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0);
            if (!ok) { break; }
            framework::MaskLayer* ret = framework::MaskLayer::create(arg0);
            object_to_luaval<framework::MaskLayer>(tolua_S, "ps.MaskLayer",(framework::MaskLayer*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            framework::MaskLayer* ret = framework::MaskLayer::create();
            object_to_luaval<framework::MaskLayer>(tolua_S, "ps.MaskLayer",(framework::MaskLayer*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_framework_MaskLayer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::MaskLayer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ps.MaskLayer");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "MaskLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_framework_MaskLayer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_framework_MaskLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MaskLayer)");
    return 0;
}

int lua_register_framework_MaskLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ps.MaskLayer");
    tolua_cclass(tolua_S,"MaskLayer","ps.MaskLayer","cc.LayerColor",nullptr);

    tolua_beginmodule(tolua_S,"MaskLayer");
        tolua_function(tolua_S,"getDelegate",lua_framework_MaskLayer_getDelegate);
        tolua_function(tolua_S,"setArea",lua_framework_MaskLayer_setArea);
        tolua_function(tolua_S,"setColor",lua_framework_MaskLayer_setColor);
        tolua_function(tolua_S,"getScriptDelegate",lua_framework_MaskLayer_getScriptDelegate);
        tolua_function(tolua_S,"getArea",lua_framework_MaskLayer_getArea);
        tolua_function(tolua_S,"setOpacity",lua_framework_MaskLayer_setOpacity);
        tolua_function(tolua_S,"isInterceptAllEvents",lua_framework_MaskLayer_isInterceptAllEvents);
        tolua_function(tolua_S,"setDelegate",lua_framework_MaskLayer_setDelegate);
        tolua_function(tolua_S,"forceInterceptAllEvents",lua_framework_MaskLayer_forceInterceptAllEvents);
        tolua_function(tolua_S,"setScriptDelegate",lua_framework_MaskLayer_setScriptDelegate);
        tolua_function(tolua_S,"new",lua_framework_MaskLayer_constructor);
        tolua_function(tolua_S,"create", lua_framework_MaskLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::MaskLayer).name();
    g_luaType[typeName] = "ps.MaskLayer";
    g_typeCast["MaskLayer"] = "ps.MaskLayer";
    return 1;
}

int lua_framework_Button_initWithNodes(lua_State* tolua_S)
{
    int argc = 0;
    framework::Button* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Button*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_Button_initWithNodes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        cocos2d::Node* arg0;
        cocos2d::Node* arg1;
        cocos2d::Node* arg2;
        std::function<void (cocos2d::Ref *)> arg3;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 4, "cc.Node",&arg2);

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        bool ret = cobj->initWithNodes(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 5) 
    {
        cocos2d::Node* arg0;
        cocos2d::Node* arg1;
        cocos2d::Node* arg2;
        std::function<void (cocos2d::Ref *)> arg3;
        std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg4;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 4, "cc.Node",&arg2);

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        bool ret = cobj->initWithNodes(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initWithNodes",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_Button_initWithNodes'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_Button_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ps.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2, arg3);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2, arg3);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg4;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            cocos2d::Node* arg1;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            cocos2d::Node* arg1;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2, arg3);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            cocos2d::Node* arg1;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
            if (!ok) { break; }
            cocos2d::Node* arg2;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 4, "cc.Node",&arg2);
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2, arg3);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            cocos2d::Node* arg1;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
            if (!ok) { break; }
            cocos2d::Node* arg2;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 4, "cc.Node",&arg2);
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg4;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::Button* ret = framework::Button::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<framework::Button>(tolua_S, "ps.Button",(framework::Button*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_Button_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_framework_Button_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Button)");
    return 0;
}

int lua_register_framework_Button(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ps.Button");
    tolua_cclass(tolua_S,"Button","ps.Button","ps.EventNode",nullptr);

    tolua_beginmodule(tolua_S,"Button");
        tolua_function(tolua_S,"initWithNodes",lua_framework_Button_initWithNodes);
        tolua_function(tolua_S,"create", lua_framework_Button_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::Button).name();
    g_luaType[typeName] = "ps.Button";
    g_typeCast["Button"] = "ps.Button";
    return 1;
}

int lua_framework_TextBlock_initWithString(lua_State* tolua_S)
{
    int argc = 0;
    framework::TextBlock* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.TextBlock",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TextBlock*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_TextBlock_initWithString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        std::string arg0;
        std::string arg1;
        int arg2;
        std::function<void (cocos2d::Ref *)> arg3;
        std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg4;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initWithString",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_TextBlock_initWithString'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_TextBlock_setSelectedColor(lua_State* tolua_S)
{
    int argc = 0;
    framework::TextBlock* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.TextBlock",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TextBlock*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_TextBlock_setSelectedColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setSelectedColor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSelectedColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_TextBlock_setSelectedColor'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_TextBlock_setDisabledColor(lua_State* tolua_S)
{
    int argc = 0;
    framework::TextBlock* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.TextBlock",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TextBlock*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_TextBlock_setDisabledColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setDisabledColor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDisabledColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_TextBlock_setDisabledColor'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_TextBlock_setDefaultColor(lua_State* tolua_S)
{
    int argc = 0;
    framework::TextBlock* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.TextBlock",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TextBlock*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_TextBlock_setDefaultColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setDefaultColor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDefaultColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_TextBlock_setDefaultColor'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_TextBlock_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ps.TextBlock",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        framework::TextBlock* ret = framework::TextBlock::create(arg0, arg1);
        object_to_luaval<framework::TextBlock>(tolua_S, "ps.TextBlock",(framework::TextBlock*)ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        int arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);
        if(!ok)
            return 0;
        framework::TextBlock* ret = framework::TextBlock::create(arg0, arg1, arg2);
        object_to_luaval<framework::TextBlock>(tolua_S, "ps.TextBlock",(framework::TextBlock*)ret);
        return 1;
    }
    if (argc == 4)
    {
        std::string arg0;
        std::string arg1;
        int arg2;
        std::function<void (cocos2d::Ref *)> arg3;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        framework::TextBlock* ret = framework::TextBlock::create(arg0, arg1, arg2, arg3);
        object_to_luaval<framework::TextBlock>(tolua_S, "ps.TextBlock",(framework::TextBlock*)ret);
        return 1;
    }
    if (argc == 5)
    {
        std::string arg0;
        std::string arg1;
        int arg2;
        std::function<void (cocos2d::Ref *)> arg3;
        std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg4;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        framework::TextBlock* ret = framework::TextBlock::create(arg0, arg1, arg2, arg3, arg4);
        object_to_luaval<framework::TextBlock>(tolua_S, "ps.TextBlock",(framework::TextBlock*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_TextBlock_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_framework_TextBlock_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TextBlock)");
    return 0;
}

int lua_register_framework_TextBlock(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ps.TextBlock");
    tolua_cclass(tolua_S,"TextBlock","ps.TextBlock","ps.EventNode",nullptr);

    tolua_beginmodule(tolua_S,"TextBlock");
        tolua_function(tolua_S,"initWithString",lua_framework_TextBlock_initWithString);
        tolua_function(tolua_S,"setSelectedColor",lua_framework_TextBlock_setSelectedColor);
        tolua_function(tolua_S,"setDisabledColor",lua_framework_TextBlock_setDisabledColor);
        tolua_function(tolua_S,"setDefaultColor",lua_framework_TextBlock_setDefaultColor);
        tolua_function(tolua_S,"create", lua_framework_TextBlock_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::TextBlock).name();
    g_luaType[typeName] = "ps.TextBlock";
    g_typeCast["TextBlock"] = "ps.TextBlock";
    return 1;
}

int lua_framework_ActiveSprite_initWithSprite(lua_State* tolua_S)
{
    int argc = 0;
    framework::ActiveSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ps.ActiveSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ActiveSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_framework_ActiveSprite_initWithSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Node* arg0;
        std::function<void (cocos2d::Ref *)> arg1;
        std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg2;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        bool ret = cobj->initWithSprite(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initWithSprite",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_ActiveSprite_initWithSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_framework_ActiveSprite_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ps.ActiveSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            framework::ActiveSprite* ret = framework::ActiveSprite::create(arg0);
            object_to_luaval<framework::ActiveSprite>(tolua_S, "ps.ActiveSprite",(framework::ActiveSprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::ActiveSprite* ret = framework::ActiveSprite::create(arg0, arg1);
            object_to_luaval<framework::ActiveSprite>(tolua_S, "ps.ActiveSprite",(framework::ActiveSprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::ActiveSprite* ret = framework::ActiveSprite::create(arg0, arg1, arg2);
            object_to_luaval<framework::ActiveSprite>(tolua_S, "ps.ActiveSprite",(framework::ActiveSprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            framework::ActiveSprite* ret = framework::ActiveSprite::create(arg0);
            object_to_luaval<framework::ActiveSprite>(tolua_S, "ps.ActiveSprite",(framework::ActiveSprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::ActiveSprite* ret = framework::ActiveSprite::create(arg0, arg1);
            object_to_luaval<framework::ActiveSprite>(tolua_S, "ps.ActiveSprite",(framework::ActiveSprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            std::function<void (cocos2d::Ref *, cocos2d::EventKeyboard::KeyCode)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            framework::ActiveSprite* ret = framework::ActiveSprite::create(arg0, arg1, arg2);
            object_to_luaval<framework::ActiveSprite>(tolua_S, "ps.ActiveSprite",(framework::ActiveSprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_framework_ActiveSprite_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_framework_ActiveSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActiveSprite)");
    return 0;
}

int lua_register_framework_ActiveSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ps.ActiveSprite");
    tolua_cclass(tolua_S,"ActiveSprite","ps.ActiveSprite","ps.EventNode",nullptr);

    tolua_beginmodule(tolua_S,"ActiveSprite");
        tolua_function(tolua_S,"initWithSprite",lua_framework_ActiveSprite_initWithSprite);
        tolua_function(tolua_S,"create", lua_framework_ActiveSprite_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ActiveSprite).name();
    g_luaType[typeName] = "ps.ActiveSprite";
    g_typeCast["ActiveSprite"] = "ps.ActiveSprite";
    return 1;
}
TOLUA_API int register_all_framework(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"sp",0);
	tolua_beginmodule(tolua_S,"sp");

	lua_register_framework_EventLayer(tolua_S);
	lua_register_framework_ViewController(tolua_S);
	lua_register_framework_EventNode(tolua_S);
	lua_register_framework_Button(tolua_S);
	lua_register_framework_GameLayer(tolua_S);
	lua_register_framework_TextBlock(tolua_S);
	lua_register_framework_MaskLayer(tolua_S);
	lua_register_framework_ActiveSprite(tolua_S);
	lua_register_framework_GameScene(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

