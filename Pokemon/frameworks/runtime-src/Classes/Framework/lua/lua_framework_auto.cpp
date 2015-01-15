#include "lua_framework_auto.hpp"
#include "framework.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_psframework_RefString_getCString(lua_State* tolua_S)
{
    int argc = 0;
    framework::RefString* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.RefString",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::RefString*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_RefString_getCString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const char* ret = cobj->getCString();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefString_getCString'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_RefString_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.RefString",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        framework::RefString* ret = framework::RefString::create(arg0);
        object_to_luaval<framework::RefString>(tolua_S, "pf.RefString",(framework::RefString*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefString_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_RefString_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::RefString* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj = new framework::RefString(arg0);
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.RefString");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "RefString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefString_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_RefString_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RefString)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"RefString",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::RefString* self = (framework::RefString*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_RefString(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.RefString");
    tolua_cclass(tolua_S,"RefString","pf.RefString","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"RefString");
        tolua_function(tolua_S,"getCString",lua_psframework_RefString_getCString);
        tolua_function(tolua_S,"new",lua_psframework_RefString_constructor);
        tolua_function(tolua_S,"create", lua_psframework_RefString_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::RefString).name();
    g_luaType[typeName] = "pf.RefString";
    g_typeCast["RefString"] = "pf.RefString";
    return 1;
}

int lua_psframework_RefInteger_getNumber(lua_State* tolua_S)
{
    int argc = 0;
    framework::RefInteger* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.RefInteger",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::RefInteger*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_RefInteger_getNumber'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getNumber();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getNumber",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefInteger_getNumber'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_RefInteger_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.RefInteger",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::RefInteger* ret = framework::RefInteger::create();
        object_to_luaval<framework::RefInteger>(tolua_S, "pf.RefInteger",(framework::RefInteger*)ret);
        return 1;
    }
    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        framework::RefInteger* ret = framework::RefInteger::create(arg0);
        object_to_luaval<framework::RefInteger>(tolua_S, "pf.RefInteger",(framework::RefInteger*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefInteger_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_RefInteger_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::RefInteger* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj = new framework::RefInteger(arg0);
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.RefInteger");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "RefInteger",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefInteger_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_RefInteger_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RefInteger)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"RefInteger",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::RefInteger* self = (framework::RefInteger*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_RefInteger(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.RefInteger");
    tolua_cclass(tolua_S,"RefInteger","pf.RefInteger","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"RefInteger");
        tolua_function(tolua_S,"getNumber",lua_psframework_RefInteger_getNumber);
        tolua_function(tolua_S,"new",lua_psframework_RefInteger_constructor);
        tolua_function(tolua_S,"create", lua_psframework_RefInteger_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::RefInteger).name();
    g_luaType[typeName] = "pf.RefInteger";
    g_typeCast["RefInteger"] = "pf.RefInteger";
    return 1;
}

int lua_psframework_RefDouble_getNumber(lua_State* tolua_S)
{
    int argc = 0;
    framework::RefDouble* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.RefDouble",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::RefDouble*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_RefDouble_getNumber'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getNumber();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getNumber",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefDouble_getNumber'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_RefDouble_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.RefDouble",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        framework::RefDouble* ret = framework::RefDouble::create(arg0);
        object_to_luaval<framework::RefDouble>(tolua_S, "pf.RefDouble",(framework::RefDouble*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefDouble_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_RefDouble_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::RefDouble* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj = new framework::RefDouble(arg0);
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.RefDouble");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "RefDouble",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefDouble_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_RefDouble_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RefDouble)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"RefDouble",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::RefDouble* self = (framework::RefDouble*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_RefDouble(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.RefDouble");
    tolua_cclass(tolua_S,"RefDouble","pf.RefDouble","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"RefDouble");
        tolua_function(tolua_S,"getNumber",lua_psframework_RefDouble_getNumber);
        tolua_function(tolua_S,"new",lua_psframework_RefDouble_constructor);
        tolua_function(tolua_S,"create", lua_psframework_RefDouble_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::RefDouble).name();
    g_luaType[typeName] = "pf.RefDouble";
    g_typeCast["RefDouble"] = "pf.RefDouble";
    return 1;
}

int lua_psframework_RefBoolean_getBoolean(lua_State* tolua_S)
{
    int argc = 0;
    framework::RefBoolean* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.RefBoolean",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::RefBoolean*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_RefBoolean_getBoolean'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getBoolean();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBoolean",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefBoolean_getBoolean'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_RefBoolean_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.RefBoolean",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        framework::RefBoolean* ret = framework::RefBoolean::create(arg0);
        object_to_luaval<framework::RefBoolean>(tolua_S, "pf.RefBoolean",(framework::RefBoolean*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefBoolean_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_RefBoolean_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::RefBoolean* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj = new framework::RefBoolean(arg0);
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.RefBoolean");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "RefBoolean",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RefBoolean_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_RefBoolean_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RefBoolean)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"RefBoolean",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::RefBoolean* self = (framework::RefBoolean*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_RefBoolean(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.RefBoolean");
    tolua_cclass(tolua_S,"RefBoolean","pf.RefBoolean","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"RefBoolean");
        tolua_function(tolua_S,"getBoolean",lua_psframework_RefBoolean_getBoolean);
        tolua_function(tolua_S,"new",lua_psframework_RefBoolean_constructor);
        tolua_function(tolua_S,"create", lua_psframework_RefBoolean_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::RefBoolean).name();
    g_luaType[typeName] = "pf.RefBoolean";
    g_typeCast["RefBoolean"] = "pf.RefBoolean";
    return 1;
}

int lua_psframework_BinaryData_getSize(lua_State* tolua_S)
{
    int argc = 0;
    framework::BinaryData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.BinaryData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::BinaryData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_BinaryData_getSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        unsigned long ret = cobj->getSize();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_BinaryData_getSize'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_BinaryData_getData(lua_State* tolua_S)
{
    int argc = 0;
    framework::BinaryData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.BinaryData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::BinaryData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_BinaryData_getData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        unsigned char* ret = cobj->getData();
        #pragma warning NO CONVERSION FROM NATIVE FOR unsigned char*;
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_BinaryData_getData'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_BinaryData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.BinaryData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        unsigned char* arg0;
        unsigned long arg1;
        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*;
        ok &= luaval_to_ulong(tolua_S, 3, &arg1);
        if(!ok)
            return 0;
        framework::BinaryData* ret = framework::BinaryData::create(arg0, arg1);
        object_to_luaval<framework::BinaryData>(tolua_S, "pf.BinaryData",(framework::BinaryData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_BinaryData_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_BinaryData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BinaryData)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"BinaryData",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::BinaryData* self = (framework::BinaryData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_BinaryData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.BinaryData");
    tolua_cclass(tolua_S,"BinaryData","pf.BinaryData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"BinaryData");
        tolua_function(tolua_S,"getSize",lua_psframework_BinaryData_getSize);
        tolua_function(tolua_S,"getData",lua_psframework_BinaryData_getData);
        tolua_function(tolua_S,"create", lua_psframework_BinaryData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::BinaryData).name();
    g_luaType[typeName] = "pf.BinaryData";
    g_typeCast["BinaryData"] = "pf.BinaryData";
    return 1;
}

int lua_psframework_Queue_getLength(lua_State* tolua_S)
{
    int argc = 0;
    framework::Queue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Queue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Queue_getLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Queue_getLength'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Queue_dequeue(lua_State* tolua_S)
{
    int argc = 0;
    framework::Queue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Queue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Queue_dequeue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->dequeue();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "dequeue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Queue_dequeue'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Queue_clear(lua_State* tolua_S)
{
    int argc = 0;
    framework::Queue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Queue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Queue_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clear();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Queue_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Queue_enqueue(lua_State* tolua_S)
{
    int argc = 0;
    framework::Queue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Queue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Queue_enqueue'", nullptr);
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
        cobj->enqueue(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "enqueue",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Queue_enqueue'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Queue_isEmpty(lua_State* tolua_S)
{
    int argc = 0;
    framework::Queue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Queue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Queue_isEmpty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isEmpty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isEmpty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Queue_isEmpty'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Queue_front(lua_State* tolua_S)
{
    int argc = 0;
    framework::Queue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Queue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Queue_front'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Ref* ret = cobj->front();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "front",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Queue_front'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Queue_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::Queue* ret = framework::Queue::create();
        object_to_luaval<framework::Queue>(tolua_S, "pf.Queue",(framework::Queue*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Queue_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_Queue_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::Queue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::Queue();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.Queue");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Queue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Queue_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_Queue_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Queue)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Queue",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::Queue* self = (framework::Queue*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_Queue(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.Queue");
    tolua_cclass(tolua_S,"Queue","pf.Queue","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Queue");
        tolua_function(tolua_S,"getLength",lua_psframework_Queue_getLength);
        tolua_function(tolua_S,"dequeue",lua_psframework_Queue_dequeue);
        tolua_function(tolua_S,"clear",lua_psframework_Queue_clear);
        tolua_function(tolua_S,"enqueue",lua_psframework_Queue_enqueue);
        tolua_function(tolua_S,"isEmpty",lua_psframework_Queue_isEmpty);
        tolua_function(tolua_S,"front",lua_psframework_Queue_front);
        tolua_function(tolua_S,"new",lua_psframework_Queue_constructor);
        tolua_function(tolua_S,"create", lua_psframework_Queue_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::Queue).name();
    g_luaType[typeName] = "pf.Queue";
    g_typeCast["Queue"] = "pf.Queue";
    return 1;
}

int lua_psframework_Stack_getLength(lua_State* tolua_S)
{
    int argc = 0;
    framework::Stack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Stack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Stack_getLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Stack_getLength'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Stack_top(lua_State* tolua_S)
{
    int argc = 0;
    framework::Stack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Stack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Stack_top'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Ref* ret = cobj->top();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "top",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Stack_top'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Stack_pop(lua_State* tolua_S)
{
    int argc = 0;
    framework::Stack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Stack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Stack_pop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->pop();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "pop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Stack_pop'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Stack_isEmpty(lua_State* tolua_S)
{
    int argc = 0;
    framework::Stack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Stack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Stack_isEmpty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isEmpty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isEmpty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Stack_isEmpty'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Stack_push(lua_State* tolua_S)
{
    int argc = 0;
    framework::Stack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Stack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Stack_push'", nullptr);
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
        cobj->push(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "push",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Stack_push'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Stack_clear(lua_State* tolua_S)
{
    int argc = 0;
    framework::Stack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Stack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Stack_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clear();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Stack_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Stack_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::Stack* ret = framework::Stack::create();
        object_to_luaval<framework::Stack>(tolua_S, "pf.Stack",(framework::Stack*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Stack_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_Stack_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::Stack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::Stack();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.Stack");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Stack",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Stack_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_Stack_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Stack)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Stack",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::Stack* self = (framework::Stack*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_Stack(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.Stack");
    tolua_cclass(tolua_S,"Stack","pf.Stack","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Stack");
        tolua_function(tolua_S,"getLength",lua_psframework_Stack_getLength);
        tolua_function(tolua_S,"top",lua_psframework_Stack_top);
        tolua_function(tolua_S,"pop",lua_psframework_Stack_pop);
        tolua_function(tolua_S,"isEmpty",lua_psframework_Stack_isEmpty);
        tolua_function(tolua_S,"push",lua_psframework_Stack_push);
        tolua_function(tolua_S,"clear",lua_psframework_Stack_clear);
        tolua_function(tolua_S,"new",lua_psframework_Stack_constructor);
        tolua_function(tolua_S,"create", lua_psframework_Stack_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::Stack).name();
    g_luaType[typeName] = "pf.Stack";
    g_typeCast["Stack"] = "pf.Stack";
    return 1;
}

int lua_psframework_Vector_addObject(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_addObject'", nullptr);
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
        cobj->addObject(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_addObject'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_addDouble(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_addDouble'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->addDouble(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addDouble",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_addDouble'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_getLength(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_getLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_getLength'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_clear(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clear();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_removeAt(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_removeAt'", nullptr);
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
        cobj->removeAt(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_removeAt'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_setObjectAt(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_setObjectAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Ref* arg0;
        int arg1;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->setObjectAt(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setObjectAt",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_setObjectAt'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_objectAt(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_objectAt'", nullptr);
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
        cocos2d::Ref* ret = cobj->objectAt(arg0);
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "objectAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_objectAt'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_isEmpty(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_isEmpty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isEmpty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isEmpty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_isEmpty'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_removeObject(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_removeObject'", nullptr);
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
        cobj->removeObject(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_removeObject'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_addString(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_addString'", nullptr);
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
        cobj->addString(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_addString'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_addInteger(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Vector*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Vector_addInteger'", nullptr);
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
        cobj->addInteger(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addInteger",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_addInteger'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Vector_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.Vector",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::Vector* ret = framework::Vector::create();
        object_to_luaval<framework::Vector>(tolua_S, "pf.Vector",(framework::Vector*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_Vector_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::Vector* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::Vector();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.Vector");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Vector",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Vector_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_Vector_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Vector)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Vector",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::Vector* self = (framework::Vector*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_Vector(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.Vector");
    tolua_cclass(tolua_S,"Vector","pf.Vector","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Vector");
        tolua_function(tolua_S,"addObject",lua_psframework_Vector_addObject);
        tolua_function(tolua_S,"addDouble",lua_psframework_Vector_addDouble);
        tolua_function(tolua_S,"getLength",lua_psframework_Vector_getLength);
        tolua_function(tolua_S,"clear",lua_psframework_Vector_clear);
        tolua_function(tolua_S,"removeAt",lua_psframework_Vector_removeAt);
        tolua_function(tolua_S,"setObjectAt",lua_psframework_Vector_setObjectAt);
        tolua_function(tolua_S,"objectAt",lua_psframework_Vector_objectAt);
        tolua_function(tolua_S,"isEmpty",lua_psframework_Vector_isEmpty);
        tolua_function(tolua_S,"removeObject",lua_psframework_Vector_removeObject);
        tolua_function(tolua_S,"addString",lua_psframework_Vector_addString);
        tolua_function(tolua_S,"addInteger",lua_psframework_Vector_addInteger);
        tolua_function(tolua_S,"new",lua_psframework_Vector_constructor);
        tolua_function(tolua_S,"create", lua_psframework_Vector_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::Vector).name();
    g_luaType[typeName] = "pf.Vector";
    g_typeCast["Vector"] = "pf.Vector";
    return 1;
}

int lua_psframework_Map_setIntegerForKey(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Map*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Map_setIntegerForKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        std::string arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->setIntegerForKey(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setIntegerForKey",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_setIntegerForKey'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Map_removeObjectForKey(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Map*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Map_removeObjectForKey'", nullptr);
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
        cobj->removeObjectForKey(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeObjectForKey",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_removeObjectForKey'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Map_clear(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Map*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Map_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clear();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Map_setObjectForKey(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Map*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Map_setObjectForKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Ref* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->setObjectForKey(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setObjectForKey",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_setObjectForKey'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Map_objectForKey(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Map*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Map_objectForKey'", nullptr);
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
        cocos2d::Ref* ret = cobj->objectForKey(arg0);
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "objectForKey",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_objectForKey'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Map_getLength(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Map*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Map_getLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_getLength'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Map_setDoubleForKey(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Map*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Map_setDoubleForKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        std::string arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->setDoubleForKey(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDoubleForKey",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_setDoubleForKey'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Map_setStringForKey(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Map*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Map_setStringForKey'", nullptr);
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
        cobj->setStringForKey(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setStringForKey",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_setStringForKey'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Map_allKeys(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Map*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Map_allKeys'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::Vector* ret = cobj->allKeys();
        object_to_luaval<framework::Vector>(tolua_S, "pf.Vector",(framework::Vector*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "allKeys",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_allKeys'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Map_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.Map",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::Map* ret = framework::Map::create();
        object_to_luaval<framework::Map>(tolua_S, "pf.Map",(framework::Map*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_Map_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::Map* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::Map();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.Map");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Map",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Map_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_Map_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Map)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Map",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::Map* self = (framework::Map*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_Map(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.Map");
    tolua_cclass(tolua_S,"Map","pf.Map","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Map");
        tolua_function(tolua_S,"setIntegerForKey",lua_psframework_Map_setIntegerForKey);
        tolua_function(tolua_S,"removeObjectForKey",lua_psframework_Map_removeObjectForKey);
        tolua_function(tolua_S,"clear",lua_psframework_Map_clear);
        tolua_function(tolua_S,"setObjectForKey",lua_psframework_Map_setObjectForKey);
        tolua_function(tolua_S,"objectForKey",lua_psframework_Map_objectForKey);
        tolua_function(tolua_S,"getLength",lua_psframework_Map_getLength);
        tolua_function(tolua_S,"setDoubleForKey",lua_psframework_Map_setDoubleForKey);
        tolua_function(tolua_S,"setStringForKey",lua_psframework_Map_setStringForKey);
        tolua_function(tolua_S,"allKeys",lua_psframework_Map_allKeys);
        tolua_function(tolua_S,"new",lua_psframework_Map_constructor);
        tolua_function(tolua_S,"create", lua_psframework_Map_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::Map).name();
    g_luaType[typeName] = "pf.Map";
    g_typeCast["Map"] = "pf.Map";
    return 1;
}

int lua_psframework_SqliteDb_updateTable(lua_State* tolua_S)
{
    int argc = 0;
    framework::SqliteDb* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (framework::SqliteDb*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SqliteDb_updateTable'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 4) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            framework::Map* arg1;
            ok &= luaval_to_object<framework::Map>(tolua_S, 3, "pf.Map",&arg1);

            if (!ok) { break; }
            std::string arg2;
            ok &= luaval_to_std_string(tolua_S, 4,&arg2);

            if (!ok) { break; }
            std::string arg3;
            ok &= luaval_to_std_string(tolua_S, 5,&arg3);

            if (!ok) { break; }
            bool ret = cobj->updateTable(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            framework::Map* arg1;
            ok &= luaval_to_object<framework::Map>(tolua_S, 3, "pf.Map",&arg1);

            if (!ok) { break; }
            bool ret = cobj->updateTable(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            framework::Map* arg1;
            ok &= luaval_to_object<framework::Map>(tolua_S, 3, "pf.Map",&arg1);

            if (!ok) { break; }
            framework::Map* arg2;
            ok &= luaval_to_object<framework::Map>(tolua_S, 4, "pf.Map",&arg2);

            if (!ok) { break; }
            bool ret = cobj->updateTable(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "updateTable",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_updateTable'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SqliteDb_dropTable(lua_State* tolua_S)
{
    int argc = 0;
    framework::SqliteDb* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SqliteDb*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SqliteDb_dropTable'", nullptr);
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
        bool ret = cobj->dropTable(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "dropTable",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_dropTable'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SqliteDb_clearTable(lua_State* tolua_S)
{
    int argc = 0;
    framework::SqliteDb* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SqliteDb*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SqliteDb_clearTable'", nullptr);
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
        bool ret = cobj->clearTable(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clearTable",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_clearTable'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SqliteDb_deleteFromTable(lua_State* tolua_S)
{
    int argc = 0;
    framework::SqliteDb* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (framework::SqliteDb*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SqliteDb_deleteFromTable'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1);

            if (!ok) { break; }
            std::string arg2;
            ok &= luaval_to_std_string(tolua_S, 4,&arg2);

            if (!ok) { break; }
            bool ret = cobj->deleteFromTable(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            framework::Map* arg1;
            ok &= luaval_to_object<framework::Map>(tolua_S, 3, "pf.Map",&arg1);

            if (!ok) { break; }
            bool ret = cobj->deleteFromTable(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "deleteFromTable",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_deleteFromTable'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SqliteDb_insertTable(lua_State* tolua_S)
{
    int argc = 0;
    framework::SqliteDb* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SqliteDb*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SqliteDb_insertTable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        framework::Map* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_object<framework::Map>(tolua_S, 3, "pf.Map",&arg1);
        if(!ok)
            return 0;
        bool ret = cobj->insertTable(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "insertTable",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_insertTable'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SqliteDb_createTable(lua_State* tolua_S)
{
    int argc = 0;
    framework::SqliteDb* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SqliteDb*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SqliteDb_createTable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        framework::Vector* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_object<framework::Vector>(tolua_S, 3, "pf.Vector",&arg1);
        if(!ok)
            return 0;
        bool ret = cobj->createTable(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "createTable",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_createTable'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SqliteDb_getRecordCount(lua_State* tolua_S)
{
    int argc = 0;
    framework::SqliteDb* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SqliteDb*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SqliteDb_getRecordCount'", nullptr);
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
        int ret = cobj->getRecordCount(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRecordCount",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_getRecordCount'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SqliteDb_getValueTypeName(lua_State* tolua_S)
{
    int argc = 0;
    framework::SqliteDb* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SqliteDb*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SqliteDb_getValueTypeName'", nullptr);
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
        const char* ret = cobj->getValueTypeName(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getValueTypeName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_getValueTypeName'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SqliteDb_selectTable(lua_State* tolua_S)
{
    int argc = 0;
    framework::SqliteDb* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (framework::SqliteDb*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SqliteDb_selectTable'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1);

            if (!ok) { break; }
            std::string arg2;
            ok &= luaval_to_std_string(tolua_S, 4,&arg2);

            if (!ok) { break; }
            framework::Vector* ret = cobj->selectTable(arg0, arg1, arg2);
            object_to_luaval<framework::Vector>(tolua_S, "pf.Vector",(framework::Vector*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            framework::Vector* ret = cobj->selectTable(arg0);
            object_to_luaval<framework::Vector>(tolua_S, "pf.Vector",(framework::Vector*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            framework::Map* arg1;
            ok &= luaval_to_object<framework::Map>(tolua_S, 3, "pf.Map",&arg1);

            if (!ok) { break; }
            framework::Vector* ret = cobj->selectTable(arg0, arg1);
            object_to_luaval<framework::Vector>(tolua_S, "pf.Vector",(framework::Vector*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1);

            if (!ok) { break; }
            framework::Vector* arg2;
            ok &= luaval_to_object<framework::Vector>(tolua_S, 4, "pf.Vector",&arg2);

            if (!ok) { break; }
            framework::Vector* ret = cobj->selectTable(arg0, arg1, arg2);
            object_to_luaval<framework::Vector>(tolua_S, "pf.Vector",(framework::Vector*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1);

            if (!ok) { break; }
            framework::Vector* ret = cobj->selectTable(arg0, arg1);
            object_to_luaval<framework::Vector>(tolua_S, "pf.Vector",(framework::Vector*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "selectTable",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_selectTable'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SqliteDb_openSqlite(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        framework::SqliteDb* ret = framework::SqliteDb::openSqlite(arg0);
        object_to_luaval<framework::SqliteDb>(tolua_S, "pf.SqliteDb",(framework::SqliteDb*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "openSqlite",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_openSqlite'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_SqliteDb_clearConnectionCache(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::SqliteDb::clearConnectionCache();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "clearConnectionCache",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SqliteDb_clearConnectionCache'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_SqliteDb_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SqliteDb)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"SqliteDb",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::SqliteDb* self = (framework::SqliteDb*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_SqliteDb(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.SqliteDb");
    tolua_cclass(tolua_S,"SqliteDb","pf.SqliteDb","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"SqliteDb");
        tolua_function(tolua_S,"updateTable",lua_psframework_SqliteDb_updateTable);
        tolua_function(tolua_S,"dropTable",lua_psframework_SqliteDb_dropTable);
        tolua_function(tolua_S,"clearTable",lua_psframework_SqliteDb_clearTable);
        tolua_function(tolua_S,"deleteFromTable",lua_psframework_SqliteDb_deleteFromTable);
        tolua_function(tolua_S,"insertTable",lua_psframework_SqliteDb_insertTable);
        tolua_function(tolua_S,"createTable",lua_psframework_SqliteDb_createTable);
        tolua_function(tolua_S,"getRecordCount",lua_psframework_SqliteDb_getRecordCount);
        tolua_function(tolua_S,"getValueTypeName",lua_psframework_SqliteDb_getValueTypeName);
        tolua_function(tolua_S,"selectTable",lua_psframework_SqliteDb_selectTable);
        tolua_function(tolua_S,"openSqlite", lua_psframework_SqliteDb_openSqlite);
        tolua_function(tolua_S,"clearConnectionCache", lua_psframework_SqliteDb_clearConnectionCache);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::SqliteDb).name();
    g_luaType[typeName] = "pf.SqliteDb";
    g_typeCast["SqliteDb"] = "pf.SqliteDb";
    return 1;
}

int lua_psframework_ViewController_load(lua_State* tolua_S)
{
    int argc = 0;
    framework::ViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ViewController_load'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ViewController_load'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ViewController_setScene(lua_State* tolua_S)
{
    int argc = 0;
    framework::ViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ViewController_setScene'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::GameScene* arg0;

        ok &= luaval_to_object<framework::GameScene>(tolua_S, 2, "pf.GameScene",&arg0);
        if(!ok)
            return 0;
        cobj->setScene(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setScene",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ViewController_setScene'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ViewController_getScene(lua_State* tolua_S)
{
    int argc = 0;
    framework::ViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ViewController_getScene'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::GameScene* ret = cobj->getScene();
        object_to_luaval<framework::GameScene>(tolua_S, "pf.GameScene",(framework::GameScene*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getScene",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ViewController_getScene'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ViewController_unload(lua_State* tolua_S)
{
    int argc = 0;
    framework::ViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ViewController_unload'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ViewController_unload'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ViewController_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::ViewController* ret = framework::ViewController::create();
        object_to_luaval<framework::ViewController>(tolua_S, "pf.ViewController",(framework::ViewController*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ViewController_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_ViewController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ViewController)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"ViewController",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::ViewController* self = (framework::ViewController*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_ViewController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.ViewController");
    tolua_cclass(tolua_S,"ViewController","pf.ViewController","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ViewController");
        tolua_function(tolua_S,"load",lua_psframework_ViewController_load);
        tolua_function(tolua_S,"setScene",lua_psframework_ViewController_setScene);
        tolua_function(tolua_S,"getScene",lua_psframework_ViewController_getScene);
        tolua_function(tolua_S,"unload",lua_psframework_ViewController_unload);
        tolua_function(tolua_S,"create", lua_psframework_ViewController_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ViewController).name();
    g_luaType[typeName] = "pf.ViewController";
    g_typeCast["ViewController"] = "pf.ViewController";
    return 1;
}

int lua_psframework_GameLayer_getComeInWhenPushAction(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_getComeInWhenPushAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::ActionInterval* ret = cobj->getComeInWhenPushAction();
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getComeInWhenPushAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_getComeInWhenPushAction'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_isShown(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_isShown'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isShown();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isShown",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_isShown'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_setGoOutWhenPushAction(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_setGoOutWhenPushAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0);
        if(!ok)
            return 0;
        cobj->setGoOutWhenPushAction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setGoOutWhenPushAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_setGoOutWhenPushAction'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_setComeInWhenPushAction(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_setComeInWhenPushAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0);
        if(!ok)
            return 0;
        cobj->setComeInWhenPushAction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setComeInWhenPushAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_setComeInWhenPushAction'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_getGoOutWhenPushAction(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_getGoOutWhenPushAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::ActionInterval* ret = cobj->getGoOutWhenPushAction();
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getGoOutWhenPushAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_getGoOutWhenPushAction'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_getComeInWhenPopAction(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_getComeInWhenPopAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::ActionInterval* ret = cobj->getComeInWhenPopAction();
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getComeInWhenPopAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_getComeInWhenPopAction'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_getGoOutWhenPopAction(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_getGoOutWhenPopAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::ActionInterval* ret = cobj->getGoOutWhenPopAction();
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getGoOutWhenPopAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_getGoOutWhenPopAction'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_setComeInWhenPopAction(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_setComeInWhenPopAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0);
        if(!ok)
            return 0;
        cobj->setComeInWhenPopAction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setComeInWhenPopAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_setComeInWhenPopAction'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_setGoOutWhenPopAction(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_setGoOutWhenPopAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0);
        if(!ok)
            return 0;
        cobj->setGoOutWhenPopAction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setGoOutWhenPopAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_setGoOutWhenPopAction'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_createWithTransitions(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        cocos2d::ActionInterval* arg0;
        cocos2d::ActionInterval* arg1;
        cocos2d::ActionInterval* arg2;
        cocos2d::ActionInterval* arg3;
        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0);
        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 3, "cc.ActionInterval",&arg1);
        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 4, "cc.ActionInterval",&arg2);
        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 5, "cc.ActionInterval",&arg3);
        if(!ok)
            return 0;
        framework::GameLayer* ret = framework::GameLayer::createWithTransitions(arg0, arg1, arg2, arg3);
        object_to_luaval<framework::GameLayer>(tolua_S, "pf.GameLayer",(framework::GameLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createWithTransitions",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_createWithTransitions'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_GameLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.GameLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::GameLayer* ret = framework::GameLayer::create();
        object_to_luaval<framework::GameLayer>(tolua_S, "pf.GameLayer",(framework::GameLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_GameLayer_constructor(lua_State* tolua_S)
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
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.GameLayer");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_GameLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameLayer)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"GameLayer",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::GameLayer* self = (framework::GameLayer*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_GameLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.GameLayer");
    tolua_cclass(tolua_S,"GameLayer","pf.GameLayer","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"GameLayer");
        tolua_function(tolua_S,"getComeInWhenPushAction",lua_psframework_GameLayer_getComeInWhenPushAction);
        tolua_function(tolua_S,"isShown",lua_psframework_GameLayer_isShown);
        tolua_function(tolua_S,"setGoOutWhenPushAction",lua_psframework_GameLayer_setGoOutWhenPushAction);
        tolua_function(tolua_S,"setComeInWhenPushAction",lua_psframework_GameLayer_setComeInWhenPushAction);
        tolua_function(tolua_S,"getGoOutWhenPushAction",lua_psframework_GameLayer_getGoOutWhenPushAction);
        tolua_function(tolua_S,"getComeInWhenPopAction",lua_psframework_GameLayer_getComeInWhenPopAction);
        tolua_function(tolua_S,"getGoOutWhenPopAction",lua_psframework_GameLayer_getGoOutWhenPopAction);
        tolua_function(tolua_S,"setComeInWhenPopAction",lua_psframework_GameLayer_setComeInWhenPopAction);
        tolua_function(tolua_S,"setGoOutWhenPopAction",lua_psframework_GameLayer_setGoOutWhenPopAction);
        tolua_function(tolua_S,"new",lua_psframework_GameLayer_constructor);
        tolua_function(tolua_S,"createWithTransitions", lua_psframework_GameLayer_createWithTransitions);
        tolua_function(tolua_S,"create", lua_psframework_GameLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::GameLayer).name();
    g_luaType[typeName] = "pf.GameLayer";
    g_typeCast["GameLayer"] = "pf.GameLayer";
    return 1;
}

int lua_psframework_CoreLayer_popLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::CoreLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.CoreLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::CoreLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_CoreLayer_popLayer'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_CoreLayer_popLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_CoreLayer_pushLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::CoreLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.CoreLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::CoreLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_CoreLayer_pushLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::GameLayer* arg0;

        ok &= luaval_to_object<framework::GameLayer>(tolua_S, 2, "pf.GameLayer",&arg0);
        if(!ok)
            return 0;
        cobj->pushLayer(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "pushLayer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_CoreLayer_pushLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_CoreLayer_getTopLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::CoreLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.CoreLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::CoreLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_CoreLayer_getTopLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::GameLayer* ret = cobj->getTopLayer();
        object_to_luaval<framework::GameLayer>(tolua_S, "pf.GameLayer",(framework::GameLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTopLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_CoreLayer_getTopLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_CoreLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.CoreLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::CoreLayer* ret = framework::CoreLayer::create();
        object_to_luaval<framework::CoreLayer>(tolua_S, "pf.CoreLayer",(framework::CoreLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_CoreLayer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_CoreLayer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::CoreLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::CoreLayer();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.CoreLayer");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "CoreLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_CoreLayer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_CoreLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CoreLayer)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"CoreLayer",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::CoreLayer* self = (framework::CoreLayer*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_CoreLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.CoreLayer");
    tolua_cclass(tolua_S,"CoreLayer","pf.CoreLayer","pf.GameLayer",nullptr);

    tolua_beginmodule(tolua_S,"CoreLayer");
        tolua_function(tolua_S,"popLayer",lua_psframework_CoreLayer_popLayer);
        tolua_function(tolua_S,"pushLayer",lua_psframework_CoreLayer_pushLayer);
        tolua_function(tolua_S,"getTopLayer",lua_psframework_CoreLayer_getTopLayer);
        tolua_function(tolua_S,"new",lua_psframework_CoreLayer_constructor);
        tolua_function(tolua_S,"create", lua_psframework_CoreLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::CoreLayer).name();
    g_luaType[typeName] = "pf.CoreLayer";
    g_typeCast["CoreLayer"] = "pf.CoreLayer";
    return 1;
}

int lua_psframework_GameScene_getCoreLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_getCoreLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::CoreLayer* ret = cobj->getCoreLayer();
        object_to_luaval<framework::CoreLayer>(tolua_S, "pf.CoreLayer",(framework::CoreLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCoreLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_getCoreLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_loadViewController(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_loadViewController'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::ViewController* arg0;

        ok &= luaval_to_object<framework::ViewController>(tolua_S, 2, "pf.ViewController",&arg0);
        if(!ok)
            return 0;
        cobj->loadViewController(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "loadViewController",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_loadViewController'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_putIntAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_putIntAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_putIntAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_getRefAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_getRefAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_getRefAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_putBoolAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_putBoolAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_putBoolAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_getDoubleAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_getDoubleAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_getDoubleAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_setCoreLayer(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_setCoreLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::CoreLayer* arg0;

        ok &= luaval_to_object<framework::CoreLayer>(tolua_S, 2, "pf.CoreLayer",&arg0);
        if(!ok)
            return 0;
        cobj->setCoreLayer(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setCoreLayer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_setCoreLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_unloadViewController(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_unloadViewController'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::ViewController* arg0;

        ok &= luaval_to_object<framework::ViewController>(tolua_S, 2, "pf.ViewController",&arg0);
        if(!ok)
            return 0;
        cobj->unloadViewController(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unloadViewController",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_unloadViewController'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_unloadAllViewControllers(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_unloadAllViewControllers'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_unloadAllViewControllers'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_putDoubleAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_putDoubleAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_putDoubleAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_putRefAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_putRefAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_putRefAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_getIntAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_getIntAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_getIntAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_getBoolAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_getBoolAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_getBoolAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_putStringAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_putStringAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_putStringAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_getStringAttribute(lua_State* tolua_S)
{
    int argc = 0;
    framework::GameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::GameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_getStringAttribute'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_getStringAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameScene_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            framework::Map* arg0;
            ok &= luaval_to_object<framework::Map>(tolua_S, 2, "pf.Map",&arg0);
            if (!ok) { break; }
            framework::GameScene* ret = framework::GameScene::create(arg0);
            object_to_luaval<framework::GameScene>(tolua_S, "pf.GameScene",(framework::GameScene*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            framework::GameScene* ret = framework::GameScene::create();
            object_to_luaval<framework::GameScene>(tolua_S, "pf.GameScene",(framework::GameScene*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_GameScene_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameScene)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"GameScene",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::GameScene* self = (framework::GameScene*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_GameScene(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.GameScene");
    tolua_cclass(tolua_S,"GameScene","pf.GameScene","cc.Scene",nullptr);

    tolua_beginmodule(tolua_S,"GameScene");
        tolua_function(tolua_S,"getCoreLayer",lua_psframework_GameScene_getCoreLayer);
        tolua_function(tolua_S,"loadViewController",lua_psframework_GameScene_loadViewController);
        tolua_function(tolua_S,"putIntAttribute",lua_psframework_GameScene_putIntAttribute);
        tolua_function(tolua_S,"getRefAttribute",lua_psframework_GameScene_getRefAttribute);
        tolua_function(tolua_S,"putBoolAttribute",lua_psframework_GameScene_putBoolAttribute);
        tolua_function(tolua_S,"getDoubleAttribute",lua_psframework_GameScene_getDoubleAttribute);
        tolua_function(tolua_S,"setCoreLayer",lua_psframework_GameScene_setCoreLayer);
        tolua_function(tolua_S,"unloadViewController",lua_psframework_GameScene_unloadViewController);
        tolua_function(tolua_S,"unloadAllViewControllers",lua_psframework_GameScene_unloadAllViewControllers);
        tolua_function(tolua_S,"putDoubleAttribute",lua_psframework_GameScene_putDoubleAttribute);
        tolua_function(tolua_S,"putRefAttribute",lua_psframework_GameScene_putRefAttribute);
        tolua_function(tolua_S,"getIntAttribute",lua_psframework_GameScene_getIntAttribute);
        tolua_function(tolua_S,"getBoolAttribute",lua_psframework_GameScene_getBoolAttribute);
        tolua_function(tolua_S,"putStringAttribute",lua_psframework_GameScene_putStringAttribute);
        tolua_function(tolua_S,"getStringAttribute",lua_psframework_GameScene_getStringAttribute);
        tolua_function(tolua_S,"create", lua_psframework_GameScene_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::GameScene).name();
    g_luaType[typeName] = "pf.GameScene";
    g_typeCast["GameScene"] = "pf.GameScene";
    return 1;
}

int lua_psframework_MaskLayer_onEventPenetrated(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayer_onEventPenetrated'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->onEventPenetrated(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onEventPenetrated",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_onEventPenetrated'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_MaskLayer_setArea(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayer_setArea'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_setArea'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_MaskLayer_setColor(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayer_setColor'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_setColor'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_MaskLayer_getArea(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayer_getArea'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_getArea'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_MaskLayer_setOpacity(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayer_setOpacity'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_setOpacity'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_MaskLayer_isInterceptAllEvents(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayer_isInterceptAllEvents'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_isInterceptAllEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_MaskLayer_forceInterceptAllEvents(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayer_forceInterceptAllEvents'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_forceInterceptAllEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_MaskLayer_onEventIntercepted(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayer_onEventIntercepted'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->onEventIntercepted(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onEventIntercepted",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_onEventIntercepted'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_MaskLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.MaskLayer",0,&tolua_err)) goto tolua_lerror;
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
            object_to_luaval<framework::MaskLayer>(tolua_S, "pf.MaskLayer",(framework::MaskLayer*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            framework::MaskLayer* ret = framework::MaskLayer::create();
            object_to_luaval<framework::MaskLayer>(tolua_S, "pf.MaskLayer",(framework::MaskLayer*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_MaskLayer_constructor(lua_State* tolua_S)
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
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.MaskLayer");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "MaskLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_MaskLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MaskLayer)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"MaskLayer",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::MaskLayer* self = (framework::MaskLayer*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_MaskLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.MaskLayer");
    tolua_cclass(tolua_S,"MaskLayer","pf.MaskLayer","cc.LayerColor",nullptr);

    tolua_beginmodule(tolua_S,"MaskLayer");
        tolua_function(tolua_S,"onEventPenetrated",lua_psframework_MaskLayer_onEventPenetrated);
        tolua_function(tolua_S,"setArea",lua_psframework_MaskLayer_setArea);
        tolua_function(tolua_S,"setColor",lua_psframework_MaskLayer_setColor);
        tolua_function(tolua_S,"getArea",lua_psframework_MaskLayer_getArea);
        tolua_function(tolua_S,"setOpacity",lua_psframework_MaskLayer_setOpacity);
        tolua_function(tolua_S,"isInterceptAllEvents",lua_psframework_MaskLayer_isInterceptAllEvents);
        tolua_function(tolua_S,"forceInterceptAllEvents",lua_psframework_MaskLayer_forceInterceptAllEvents);
        tolua_function(tolua_S,"onEventIntercepted",lua_psframework_MaskLayer_onEventIntercepted);
        tolua_function(tolua_S,"new",lua_psframework_MaskLayer_constructor);
        tolua_function(tolua_S,"create", lua_psframework_MaskLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::MaskLayer).name();
    g_luaType[typeName] = "pf.MaskLayer";
    g_typeCast["MaskLayer"] = "pf.MaskLayer";
    return 1;
}

int lua_psframework_ModalLayer_onModalTouchMoved(lua_State* tolua_S)
{
    int argc = 0;
    framework::ModalLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ModalLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ModalLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ModalLayer_onModalTouchMoved'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->onModalTouchMoved(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onModalTouchMoved",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ModalLayer_onModalTouchMoved'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ModalLayer_onModalTouchBegan(lua_State* tolua_S)
{
    int argc = 0;
    framework::ModalLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ModalLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ModalLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ModalLayer_onModalTouchBegan'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->onModalTouchBegan(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onModalTouchBegan",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ModalLayer_onModalTouchBegan'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ModalLayer_onGoOut(lua_State* tolua_S)
{
    int argc = 0;
    framework::ModalLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ModalLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ModalLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ModalLayer_onGoOut'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->onGoOut();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onGoOut",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ModalLayer_onGoOut'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ModalLayer_onModalTouchEnded(lua_State* tolua_S)
{
    int argc = 0;
    framework::ModalLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ModalLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ModalLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ModalLayer_onModalTouchEnded'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->onModalTouchEnded(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onModalTouchEnded",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ModalLayer_onModalTouchEnded'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ModalLayer_onModalTouchCancelled(lua_State* tolua_S)
{
    int argc = 0;
    framework::ModalLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ModalLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ModalLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ModalLayer_onModalTouchCancelled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->onModalTouchCancelled(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onModalTouchCancelled",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ModalLayer_onModalTouchCancelled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ModalLayer_onComeIn(lua_State* tolua_S)
{
    int argc = 0;
    framework::ModalLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ModalLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ModalLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ModalLayer_onComeIn'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->onComeIn();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onComeIn",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ModalLayer_onComeIn'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ModalLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.ModalLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::ModalLayer* ret = framework::ModalLayer::create();
        object_to_luaval<framework::ModalLayer>(tolua_S, "pf.ModalLayer",(framework::ModalLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ModalLayer_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_ModalLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ModalLayer)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"ModalLayer",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::ModalLayer* self = (framework::ModalLayer*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_ModalLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.ModalLayer");
    tolua_cclass(tolua_S,"ModalLayer","pf.ModalLayer","cc.LayerColor",nullptr);

    tolua_beginmodule(tolua_S,"ModalLayer");
        tolua_function(tolua_S,"onModalTouchMoved",lua_psframework_ModalLayer_onModalTouchMoved);
        tolua_function(tolua_S,"onModalTouchBegan",lua_psframework_ModalLayer_onModalTouchBegan);
        tolua_function(tolua_S,"onGoOut",lua_psframework_ModalLayer_onGoOut);
        tolua_function(tolua_S,"onModalTouchEnded",lua_psframework_ModalLayer_onModalTouchEnded);
        tolua_function(tolua_S,"onModalTouchCancelled",lua_psframework_ModalLayer_onModalTouchCancelled);
        tolua_function(tolua_S,"onComeIn",lua_psframework_ModalLayer_onComeIn);
        tolua_function(tolua_S,"create", lua_psframework_ModalLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ModalLayer).name();
    g_luaType[typeName] = "pf.ModalLayer";
    g_typeCast["ModalLayer"] = "pf.ModalLayer";
    return 1;
}

int lua_psframework_EncryptedTMXLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.EncryptedTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        cocos2d::TMXTilesetInfo* arg0;
        cocos2d::TMXLayerInfo* arg1;
        cocos2d::TMXMapInfo* arg2;
        std::string arg3;
        ok &= luaval_to_object<cocos2d::TMXTilesetInfo>(tolua_S, 2, "cc.TMXTilesetInfo",&arg0);
        ok &= luaval_to_object<cocos2d::TMXLayerInfo>(tolua_S, 3, "cc.TMXLayerInfo",&arg1);
        ok &= luaval_to_object<cocos2d::TMXMapInfo>(tolua_S, 4, "cc.TMXMapInfo",&arg2);
        ok &= luaval_to_std_string(tolua_S, 5,&arg3);
        if(!ok)
            return 0;
        framework::EncryptedTMXLayer* ret = framework::EncryptedTMXLayer::create(arg0, arg1, arg2, arg3);
        object_to_luaval<framework::EncryptedTMXLayer>(tolua_S, "pf.EncryptedTMXLayer",(framework::EncryptedTMXLayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_EncryptedTMXLayer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_EncryptedTMXLayer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::EncryptedTMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::EncryptedTMXLayer();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.EncryptedTMXLayer");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "EncryptedTMXLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_EncryptedTMXLayer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_EncryptedTMXLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EncryptedTMXLayer)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"EncryptedTMXLayer",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::EncryptedTMXLayer* self = (framework::EncryptedTMXLayer*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_EncryptedTMXLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.EncryptedTMXLayer");
    tolua_cclass(tolua_S,"EncryptedTMXLayer","pf.EncryptedTMXLayer","cc.TMXLayer",nullptr);

    tolua_beginmodule(tolua_S,"EncryptedTMXLayer");
        tolua_function(tolua_S,"create", lua_psframework_EncryptedTMXLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::EncryptedTMXLayer).name();
    g_luaType[typeName] = "pf.EncryptedTMXLayer";
    g_typeCast["EncryptedTMXLayer"] = "pf.EncryptedTMXLayer";
    return 1;
}

int lua_psframework_EncryptedTMXTiledMap_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.EncryptedTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
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
        framework::EncryptedTMXTiledMap* ret = framework::EncryptedTMXTiledMap::create(arg0, arg1);
        object_to_luaval<framework::EncryptedTMXTiledMap>(tolua_S, "pf.EncryptedTMXTiledMap",(framework::EncryptedTMXTiledMap*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_EncryptedTMXTiledMap_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_EncryptedTMXTiledMap_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::EncryptedTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::EncryptedTMXTiledMap();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.EncryptedTMXTiledMap");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "EncryptedTMXTiledMap",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_EncryptedTMXTiledMap_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_EncryptedTMXTiledMap_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EncryptedTMXTiledMap)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"EncryptedTMXTiledMap",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::EncryptedTMXTiledMap* self = (framework::EncryptedTMXTiledMap*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_EncryptedTMXTiledMap(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.EncryptedTMXTiledMap");
    tolua_cclass(tolua_S,"EncryptedTMXTiledMap","pf.EncryptedTMXTiledMap","cc.TMXTiledMap",nullptr);

    tolua_beginmodule(tolua_S,"EncryptedTMXTiledMap");
        tolua_function(tolua_S,"create", lua_psframework_EncryptedTMXTiledMap_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::EncryptedTMXTiledMap).name();
    g_luaType[typeName] = "pf.EncryptedTMXTiledMap";
    g_typeCast["EncryptedTMXTiledMap"] = "pf.EncryptedTMXTiledMap";
    return 1;
}

int lua_psframework_ListMenuItem_reset(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenuItem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenuItem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenuItem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenuItem_reset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->reset();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "reset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenuItem_reset'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenuItem_setShowIndex(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenuItem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenuItem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenuItem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenuItem_setShowIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setShowIndex(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setShowIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenuItem_setShowIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenuItem_getShowIndex(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenuItem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenuItem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenuItem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenuItem_getShowIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        ssize_t ret = cobj->getShowIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getShowIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenuItem_getShowIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenuItem_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.ListMenuItem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::ListMenuItem* ret = framework::ListMenuItem::create();
        object_to_luaval<framework::ListMenuItem>(tolua_S, "pf.ListMenuItem",(framework::ListMenuItem*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenuItem_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_ListMenuItem_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenuItem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::ListMenuItem();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.ListMenuItem");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ListMenuItem",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenuItem_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_ListMenuItem_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ListMenuItem)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"ListMenuItem",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::ListMenuItem* self = (framework::ListMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_ListMenuItem(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.ListMenuItem");
    tolua_cclass(tolua_S,"ListMenuItem","pf.ListMenuItem","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"ListMenuItem");
        tolua_function(tolua_S,"reset",lua_psframework_ListMenuItem_reset);
        tolua_function(tolua_S,"setShowIndex",lua_psframework_ListMenuItem_setShowIndex);
        tolua_function(tolua_S,"getShowIndex",lua_psframework_ListMenuItem_getShowIndex);
        tolua_function(tolua_S,"new",lua_psframework_ListMenuItem_constructor);
        tolua_function(tolua_S,"create", lua_psframework_ListMenuItem_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ListMenuItem).name();
    g_luaType[typeName] = "pf.ListMenuItem";
    g_typeCast["ListMenuItem"] = "pf.ListMenuItem";
    return 1;
}

int lua_psframework_ListMenu_dequeueItem(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_dequeueItem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::ListMenuItem* ret = cobj->dequeueItem();
        object_to_luaval<framework::ListMenuItem>(tolua_S, "pf.ListMenuItem",(framework::ListMenuItem*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "dequeueItem",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_dequeueItem'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_setResponseKeyCodes(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_setResponseKeyCodes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        int arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);
        if(!ok)
            return 0;
        cobj->setResponseKeyCodes(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setResponseKeyCodes",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_setResponseKeyCodes'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_getIndexInAllItems(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_getIndexInAllItems'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        ssize_t ret = cobj->getIndexInAllItems();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIndexInAllItems",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_getIndexInAllItems'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_getTopGlobalIndex(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_getTopGlobalIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        ssize_t ret = cobj->getTopGlobalIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTopGlobalIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_getTopGlobalIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_setMenuEnabled(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_setMenuEnabled'", nullptr);
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
        cobj->setMenuEnabled(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setMenuEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_setMenuEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_getCurrentShowIndex(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_getCurrentShowIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        ssize_t ret = cobj->getCurrentShowIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCurrentShowIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_getCurrentShowIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_isBottomOverflowed(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_isBottomOverflowed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isBottomOverflowed();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isBottomOverflowed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_isBottomOverflowed'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_onKeyPressed(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_onKeyPressed'", nullptr);
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
        cobj->onKeyPressed(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onKeyPressed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_onKeyPressed'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_getItemAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_getItemAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        framework::ListMenuItem* ret = cobj->getItemAtIndex(arg0);
        object_to_luaval<framework::ListMenuItem>(tolua_S, "pf.ListMenuItem",(framework::ListMenuItem*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getItemAtIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_getItemAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_isMenuEnabled(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_isMenuEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isMenuEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isMenuEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_isMenuEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_setEventsSwallowed(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_setEventsSwallowed'", nullptr);
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
        cobj->setEventsSwallowed(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setEventsSwallowed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_setEventsSwallowed'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_isTopOverflowed(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_isTopOverflowed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isTopOverflowed();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isTopOverflowed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_isTopOverflowed'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_onKeyReleased(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_onKeyReleased'", nullptr);
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
        cobj->onKeyReleased(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onKeyReleased",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_onKeyReleased'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_reloadData(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_reloadData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->reloadData();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "reloadData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_reloadData'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_select(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ListMenu*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ListMenu_select'", nullptr);
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
        cobj->select(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->select(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "select",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_select'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ListMenu_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.ListMenu",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            framework::ListMenuDataSource* arg0;
            ok &= luaval_to_object<framework::ListMenuDataSource>(tolua_S, 2, "pf.ListMenuDataSource",&arg0);
            if (!ok) { break; }
            ssize_t arg1;
            ok &= luaval_to_ssize(tolua_S, 3, &arg1);
            if (!ok) { break; }
            framework::ListMenu* ret = framework::ListMenu::create(arg0, arg1);
            object_to_luaval<framework::ListMenu>(tolua_S, "pf.ListMenu",(framework::ListMenu*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            ssize_t arg0;
            ok &= luaval_to_ssize(tolua_S, 2, &arg0);
            if (!ok) { break; }
            framework::ListMenu* ret = framework::ListMenu::create(arg0);
            object_to_luaval<framework::ListMenu>(tolua_S, "pf.ListMenu",(framework::ListMenu*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_ListMenu_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::ListMenu* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::ListMenu();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.ListMenu");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ListMenu",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ListMenu_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_ListMenu_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ListMenu)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"ListMenu",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::ListMenu* self = (framework::ListMenu*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_ListMenu(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.ListMenu");
    tolua_cclass(tolua_S,"ListMenu","pf.ListMenu","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"ListMenu");
        tolua_function(tolua_S,"dequeueItem",lua_psframework_ListMenu_dequeueItem);
        tolua_function(tolua_S,"setResponseKeyCodes",lua_psframework_ListMenu_setResponseKeyCodes);
        tolua_function(tolua_S,"getIndexInAllItems",lua_psframework_ListMenu_getIndexInAllItems);
        tolua_function(tolua_S,"getTopGlobalIndex",lua_psframework_ListMenu_getTopGlobalIndex);
        tolua_function(tolua_S,"setMenuEnabled",lua_psframework_ListMenu_setMenuEnabled);
        tolua_function(tolua_S,"getCurrentShowIndex",lua_psframework_ListMenu_getCurrentShowIndex);
        tolua_function(tolua_S,"isBottomOverflowed",lua_psframework_ListMenu_isBottomOverflowed);
        tolua_function(tolua_S,"onKeyPressed",lua_psframework_ListMenu_onKeyPressed);
        tolua_function(tolua_S,"getItemAtIndex",lua_psframework_ListMenu_getItemAtIndex);
        tolua_function(tolua_S,"isMenuEnabled",lua_psframework_ListMenu_isMenuEnabled);
        tolua_function(tolua_S,"setEventsSwallowed",lua_psframework_ListMenu_setEventsSwallowed);
        tolua_function(tolua_S,"isTopOverflowed",lua_psframework_ListMenu_isTopOverflowed);
        tolua_function(tolua_S,"onKeyReleased",lua_psframework_ListMenu_onKeyReleased);
        tolua_function(tolua_S,"reloadData",lua_psframework_ListMenu_reloadData);
        tolua_function(tolua_S,"select",lua_psframework_ListMenu_select);
        tolua_function(tolua_S,"new",lua_psframework_ListMenu_constructor);
        tolua_function(tolua_S,"create", lua_psframework_ListMenu_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ListMenu).name();
    g_luaType[typeName] = "pf.ListMenu";
    g_typeCast["ListMenu"] = "pf.ListMenu";
    return 1;
}

int lua_psframework_TitleSwitch_setBackgroundNode(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_setBackgroundNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
            return 0;
        cobj->setBackgroundNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setBackgroundNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_setBackgroundNode'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_setAllowLoop(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_setAllowLoop'", nullptr);
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
        cobj->setAllowLoop(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAllowLoop",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_setAllowLoop'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_setTitleFontSize(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_setTitleFontSize'", nullptr);
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
        cobj->setTitleFontSize(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTitleFontSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_setTitleFontSize'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_setTitleFontName(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_setTitleFontName'", nullptr);
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
        cobj->setTitleFontName(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTitleFontName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_setTitleFontName'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_onKeyPressed(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_onKeyPressed'", nullptr);
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
        cobj->onKeyPressed(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onKeyPressed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_onKeyPressed'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_setEventsSwallowed(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_setEventsSwallowed'", nullptr);
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
        cobj->setEventsSwallowed(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setEventsSwallowed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_setEventsSwallowed'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_setCurrentIndex(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_setCurrentIndex'", nullptr);
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
        cobj->setCurrentIndex(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setCurrentIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_setCurrentIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_getCurrentIndex(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_getCurrentIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getCurrentIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCurrentIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_getCurrentIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_setDuration(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_setDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setDuration(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDuration",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_setDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_setResponseKeys(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_setResponseKeys'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->setResponseKeys(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setResponseKeys",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_setResponseKeys'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_setTitleColor(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.TitleSwitch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::TitleSwitch*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_TitleSwitch_setTitleColor'", nullptr);
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
        cobj->setTitleColor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTitleColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_setTitleColor'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_TitleSwitch_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::TitleSwitch* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::TitleSwitch();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.TitleSwitch");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "TitleSwitch",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_TitleSwitch_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_TitleSwitch_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TitleSwitch)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"TitleSwitch",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::TitleSwitch* self = (framework::TitleSwitch*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_TitleSwitch(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.TitleSwitch");
    tolua_cclass(tolua_S,"TitleSwitch","pf.TitleSwitch","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"TitleSwitch");
        tolua_function(tolua_S,"setBackgroundNode",lua_psframework_TitleSwitch_setBackgroundNode);
        tolua_function(tolua_S,"setAllowLoop",lua_psframework_TitleSwitch_setAllowLoop);
        tolua_function(tolua_S,"setTitleFontSize",lua_psframework_TitleSwitch_setTitleFontSize);
        tolua_function(tolua_S,"setTitleFontName",lua_psframework_TitleSwitch_setTitleFontName);
        tolua_function(tolua_S,"onKeyPressed",lua_psframework_TitleSwitch_onKeyPressed);
        tolua_function(tolua_S,"setEventsSwallowed",lua_psframework_TitleSwitch_setEventsSwallowed);
        tolua_function(tolua_S,"setCurrentIndex",lua_psframework_TitleSwitch_setCurrentIndex);
        tolua_function(tolua_S,"getCurrentIndex",lua_psframework_TitleSwitch_getCurrentIndex);
        tolua_function(tolua_S,"setDuration",lua_psframework_TitleSwitch_setDuration);
        tolua_function(tolua_S,"setResponseKeys",lua_psframework_TitleSwitch_setResponseKeys);
        tolua_function(tolua_S,"setTitleColor",lua_psframework_TitleSwitch_setTitleColor);
        tolua_function(tolua_S,"new",lua_psframework_TitleSwitch_constructor);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::TitleSwitch).name();
    g_luaType[typeName] = "pf.TitleSwitch";
    g_typeCast["TitleSwitch"] = "pf.TitleSwitch";
    return 1;
}

int lua_psframework_DirectionController_setEnabled(lua_State* tolua_S)
{
    int argc = 0;
    framework::DirectionController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.DirectionController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::DirectionController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_DirectionController_setEnabled'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_DirectionController_setEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_DirectionController_onTouchEnded(lua_State* tolua_S)
{
    int argc = 0;
    framework::DirectionController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.DirectionController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::DirectionController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_DirectionController_onTouchEnded'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_DirectionController_onTouchEnded'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_DirectionController_onTouchMoved(lua_State* tolua_S)
{
    int argc = 0;
    framework::DirectionController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.DirectionController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::DirectionController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_DirectionController_onTouchMoved'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_DirectionController_onTouchMoved'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_DirectionController_setTouchRadius(lua_State* tolua_S)
{
    int argc = 0;
    framework::DirectionController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.DirectionController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::DirectionController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_DirectionController_setTouchRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setTouchRadius(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTouchRadius",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_DirectionController_setTouchRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_DirectionController_isEnabled(lua_State* tolua_S)
{
    int argc = 0;
    framework::DirectionController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.DirectionController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::DirectionController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_DirectionController_isEnabled'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_DirectionController_isEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_DirectionController_onTouchCancelled(lua_State* tolua_S)
{
    int argc = 0;
    framework::DirectionController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.DirectionController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::DirectionController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_DirectionController_onTouchCancelled'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_DirectionController_onTouchCancelled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_DirectionController_onTouchBegan(lua_State* tolua_S)
{
    int argc = 0;
    framework::DirectionController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.DirectionController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::DirectionController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_DirectionController_onTouchBegan'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_DirectionController_onTouchBegan'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_DirectionController_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.DirectionController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            cocos2d::Node* arg1;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
            if (!ok) { break; }
            framework::DirectionController* ret = framework::DirectionController::create(arg0, arg1);
            object_to_luaval<framework::DirectionController>(tolua_S, "pf.DirectionController",(framework::DirectionController*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1);
            if (!ok) { break; }
            framework::DirectionController* ret = framework::DirectionController::create(arg0, arg1);
            object_to_luaval<framework::DirectionController>(tolua_S, "pf.DirectionController",(framework::DirectionController*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_DirectionController_create'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_DirectionController_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::DirectionController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::DirectionController();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.DirectionController");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "DirectionController",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_DirectionController_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_DirectionController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (DirectionController)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"DirectionController",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::DirectionController* self = (framework::DirectionController*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_DirectionController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.DirectionController");
    tolua_cclass(tolua_S,"DirectionController","pf.DirectionController","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"DirectionController");
        tolua_function(tolua_S,"setEnabled",lua_psframework_DirectionController_setEnabled);
        tolua_function(tolua_S,"onTouchEnded",lua_psframework_DirectionController_onTouchEnded);
        tolua_function(tolua_S,"onTouchMoved",lua_psframework_DirectionController_onTouchMoved);
        tolua_function(tolua_S,"setTouchRadius",lua_psframework_DirectionController_setTouchRadius);
        tolua_function(tolua_S,"isEnabled",lua_psframework_DirectionController_isEnabled);
        tolua_function(tolua_S,"onTouchCancelled",lua_psframework_DirectionController_onTouchCancelled);
        tolua_function(tolua_S,"onTouchBegan",lua_psframework_DirectionController_onTouchBegan);
        tolua_function(tolua_S,"new",lua_psframework_DirectionController_constructor);
        tolua_function(tolua_S,"create", lua_psframework_DirectionController_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::DirectionController).name();
    g_luaType[typeName] = "pf.DirectionController";
    g_typeCast["DirectionController"] = "pf.DirectionController";
    return 1;
}

int lua_psframework_ScriptCCBReader_readCCB(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.ScriptCCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        cocos2d::Ref* arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 3, "cc.Ref",&arg1);
        if(!ok)
            return 0;
        cocos2d::Node* ret = framework::ScriptCCBReader::readCCB(arg0, arg1);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "readCCB",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ScriptCCBReader_readCCB'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_ScriptCCBReader_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ScriptCCBReader)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"ScriptCCBReader",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::ScriptCCBReader* self = (framework::ScriptCCBReader*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_ScriptCCBReader(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.ScriptCCBReader");
    tolua_cclass(tolua_S,"ScriptCCBReader","pf.ScriptCCBReader","",nullptr);

    tolua_beginmodule(tolua_S,"ScriptCCBReader");
        tolua_function(tolua_S,"readCCB", lua_psframework_ScriptCCBReader_readCCB);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ScriptCCBReader).name();
    g_luaType[typeName] = "pf.ScriptCCBReader";
    g_typeCast["ScriptCCBReader"] = "pf.ScriptCCBReader";
    return 1;
}

int lua_psframework_IOUtils_fileExists(lua_State* tolua_S)
{
    int argc = 0;
    framework::IOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::IOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_IOUtils_fileExists'", nullptr);
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
        bool ret = cobj->fileExists(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "fileExists",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_IOUtils_fileExists'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_IOUtils_copyFile(lua_State* tolua_S)
{
    int argc = 0;
    framework::IOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::IOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_IOUtils_copyFile'", nullptr);
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
        bool ret = cobj->copyFile(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "copyFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_IOUtils_copyFile'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_IOUtils_writeDataToFile(lua_State* tolua_S)
{
    int argc = 0;
    framework::IOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::IOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_IOUtils_writeDataToFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        const unsigned char* arg0;
        unsigned long arg1;
        std::string arg2;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*;

        ok &= luaval_to_ulong(tolua_S, 3, &arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        bool ret = cobj->writeDataToFile(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 4) 
    {
        const unsigned char* arg0;
        unsigned long arg1;
        std::string arg2;
        bool arg3;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*;

        ok &= luaval_to_ulong(tolua_S, 3, &arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2);

        ok &= luaval_to_boolean(tolua_S, 5,&arg3);
        if(!ok)
            return 0;
        bool ret = cobj->writeDataToFile(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "writeDataToFile",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_IOUtils_writeDataToFile'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_IOUtils_directoryExists(lua_State* tolua_S)
{
    int argc = 0;
    framework::IOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::IOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_IOUtils_directoryExists'", nullptr);
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
        bool ret = cobj->directoryExists(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "directoryExists",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_IOUtils_directoryExists'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_IOUtils_removeFile(lua_State* tolua_S)
{
    int argc = 0;
    framework::IOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::IOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_IOUtils_removeFile'", nullptr);
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
        bool ret = cobj->removeFile(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_IOUtils_removeFile'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_IOUtils_moveFile(lua_State* tolua_S)
{
    int argc = 0;
    framework::IOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::IOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_IOUtils_moveFile'", nullptr);
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
        bool ret = cobj->moveFile(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "moveFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_IOUtils_moveFile'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_IOUtils_createDirectory(lua_State* tolua_S)
{
    int argc = 0;
    framework::IOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::IOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_IOUtils_createDirectory'", nullptr);
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
        bool ret = cobj->createDirectory(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "createDirectory",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_IOUtils_createDirectory'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_IOUtils_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::IOUtils* ret = framework::IOUtils::getInstance();
        object_to_luaval<framework::IOUtils>(tolua_S, "pf.IOUtils",(framework::IOUtils*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_IOUtils_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_IOUtils_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (IOUtils)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"IOUtils",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::IOUtils* self = (framework::IOUtils*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_IOUtils(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.IOUtils");
    tolua_cclass(tolua_S,"IOUtils","pf.IOUtils","",nullptr);

    tolua_beginmodule(tolua_S,"IOUtils");
        tolua_function(tolua_S,"fileExists",lua_psframework_IOUtils_fileExists);
        tolua_function(tolua_S,"copyFile",lua_psframework_IOUtils_copyFile);
        tolua_function(tolua_S,"writeDataToFile",lua_psframework_IOUtils_writeDataToFile);
        tolua_function(tolua_S,"directoryExists",lua_psframework_IOUtils_directoryExists);
        tolua_function(tolua_S,"removeFile",lua_psframework_IOUtils_removeFile);
        tolua_function(tolua_S,"moveFile",lua_psframework_IOUtils_moveFile);
        tolua_function(tolua_S,"createDirectory",lua_psframework_IOUtils_createDirectory);
        tolua_function(tolua_S,"getInstance", lua_psframework_IOUtils_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::IOUtils).name();
    g_luaType[typeName] = "pf.IOUtils";
    g_typeCast["IOUtils"] = "pf.IOUtils";
    return 1;
}

int lua_psframework_RecordHelper_setEncryptionKey(lua_State* tolua_S)
{
    int argc = 0;
    framework::RecordHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.RecordHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::RecordHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_RecordHelper_setEncryptionKey'", nullptr);
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
        cobj->setEncryptionKey(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setEncryptionKey",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RecordHelper_setEncryptionKey'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_RecordHelper_writeRecord(lua_State* tolua_S)
{
    int argc = 0;
    framework::RecordHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.RecordHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::RecordHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_RecordHelper_writeRecord'", nullptr);
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
        bool ret = cobj->writeRecord(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "writeRecord",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RecordHelper_writeRecord'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_RecordHelper_readRecord(lua_State* tolua_S)
{
    int argc = 0;
    framework::RecordHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.RecordHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::RecordHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_RecordHelper_readRecord'", nullptr);
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
        const char* ret = cobj->readRecord(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "readRecord",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RecordHelper_readRecord'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_RecordHelper_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.RecordHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::RecordHelper* ret = framework::RecordHelper::getInstance();
        object_to_luaval<framework::RecordHelper>(tolua_S, "pf.RecordHelper",(framework::RecordHelper*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RecordHelper_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_RecordHelper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RecordHelper)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"RecordHelper",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::RecordHelper* self = (framework::RecordHelper*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_RecordHelper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.RecordHelper");
    tolua_cclass(tolua_S,"RecordHelper","pf.RecordHelper","",nullptr);

    tolua_beginmodule(tolua_S,"RecordHelper");
        tolua_function(tolua_S,"setEncryptionKey",lua_psframework_RecordHelper_setEncryptionKey);
        tolua_function(tolua_S,"writeRecord",lua_psframework_RecordHelper_writeRecord);
        tolua_function(tolua_S,"readRecord",lua_psframework_RecordHelper_readRecord);
        tolua_function(tolua_S,"getInstance", lua_psframework_RecordHelper_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::RecordHelper).name();
    g_luaType[typeName] = "pf.RecordHelper";
    g_typeCast["RecordHelper"] = "pf.RecordHelper";
    return 1;
}

int lua_psframework_ImageUtils_createAnimationByGifImage(lua_State* tolua_S)
{
    int argc = 0;
    framework::ImageUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ImageUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ImageUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ImageUtils_createAnimationByGifImage'", nullptr);
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
        cocos2d::Animate* ret = cobj->createAnimationByGifImage(arg0, arg1);
        object_to_luaval<cocos2d::Animate>(tolua_S, "cc.Animate",(cocos2d::Animate*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "createAnimationByGifImage",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ImageUtils_createAnimationByGifImage'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ImageUtils_createSpriteWithBinaryData(lua_State* tolua_S)
{
    int argc = 0;
    framework::ImageUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ImageUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ImageUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ImageUtils_createSpriteWithBinaryData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::BinaryData* arg0;

        ok &= luaval_to_object<framework::BinaryData>(tolua_S, 2, "pf.BinaryData",&arg0);
        if(!ok)
            return 0;
        cocos2d::Sprite* ret = cobj->createSpriteWithBinaryData(arg0);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "createSpriteWithBinaryData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ImageUtils_createSpriteWithBinaryData'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ImageUtils_getGifFrames(lua_State* tolua_S)
{
    int argc = 0;
    framework::ImageUtils* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ImageUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (framework::ImageUtils*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ImageUtils_getGifFrames'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            framework::BinaryData* arg0;
            ok &= luaval_to_object<framework::BinaryData>(tolua_S, 2, "pf.BinaryData",&arg0);

            if (!ok) { break; }
            framework::Vector* ret = cobj->getGifFrames(arg0);
            object_to_luaval<framework::Vector>(tolua_S, "pf.Vector",(framework::Vector*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            framework::Vector* ret = cobj->getGifFrames(arg0);
            object_to_luaval<framework::Vector>(tolua_S, "pf.Vector",(framework::Vector*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getGifFrames",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ImageUtils_getGifFrames'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ImageUtils_createAnimationByFrames(lua_State* tolua_S)
{
    int argc = 0;
    framework::ImageUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ImageUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ImageUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ImageUtils_createAnimationByFrames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        framework::Vector* arg0;
        double arg1;

        ok &= luaval_to_object<framework::Vector>(tolua_S, 2, "pf.Vector",&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cocos2d::Animate* ret = cobj->createAnimationByFrames(arg0, arg1);
        object_to_luaval<cocos2d::Animate>(tolua_S, "cc.Animate",(cocos2d::Animate*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "createAnimationByFrames",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ImageUtils_createAnimationByFrames'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ImageUtils_createSpriteFrameWithBinaryData(lua_State* tolua_S)
{
    int argc = 0;
    framework::ImageUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ImageUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ImageUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ImageUtils_createSpriteFrameWithBinaryData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::BinaryData* arg0;

        ok &= luaval_to_object<framework::BinaryData>(tolua_S, 2, "pf.BinaryData",&arg0);
        if(!ok)
            return 0;
        cocos2d::SpriteFrame* ret = cobj->createSpriteFrameWithBinaryData(arg0);
        object_to_luaval<cocos2d::SpriteFrame>(tolua_S, "cc.SpriteFrame",(cocos2d::SpriteFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "createSpriteFrameWithBinaryData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ImageUtils_createSpriteFrameWithBinaryData'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ImageUtils_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.ImageUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::ImageUtils* ret = framework::ImageUtils::getInstance();
        object_to_luaval<framework::ImageUtils>(tolua_S, "pf.ImageUtils",(framework::ImageUtils*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ImageUtils_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_ImageUtils_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ImageUtils)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"ImageUtils",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::ImageUtils* self = (framework::ImageUtils*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_ImageUtils(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.ImageUtils");
    tolua_cclass(tolua_S,"ImageUtils","pf.ImageUtils","",nullptr);

    tolua_beginmodule(tolua_S,"ImageUtils");
        tolua_function(tolua_S,"createAnimationByGifImage",lua_psframework_ImageUtils_createAnimationByGifImage);
        tolua_function(tolua_S,"createSpriteWithBinaryData",lua_psframework_ImageUtils_createSpriteWithBinaryData);
        tolua_function(tolua_S,"getGifFrames",lua_psframework_ImageUtils_getGifFrames);
        tolua_function(tolua_S,"createAnimationByFrames",lua_psframework_ImageUtils_createAnimationByFrames);
        tolua_function(tolua_S,"createSpriteFrameWithBinaryData",lua_psframework_ImageUtils_createSpriteFrameWithBinaryData);
        tolua_function(tolua_S,"getInstance", lua_psframework_ImageUtils_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ImageUtils).name();
    g_luaType[typeName] = "pf.ImageUtils";
    g_typeCast["ImageUtils"] = "pf.ImageUtils";
    return 1;
}

int lua_psframework_ZipHelper_zipOneFile(lua_State* tolua_S)
{
    int argc = 0;
    framework::ZipHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ZipHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ZipHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ZipHelper_zipOneFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        std::string arg0;
        std::string arg1;
        unsigned char* arg2;
        unsigned long arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*;

        ok &= luaval_to_ulong(tolua_S, 5, &arg3);
        if(!ok)
            return 0;
        bool ret = cobj->zipOneFile(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 5) 
    {
        std::string arg0;
        std::string arg1;
        unsigned char* arg2;
        unsigned long arg3;
        bool arg4;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*;

        ok &= luaval_to_ulong(tolua_S, 5, &arg3);

        ok &= luaval_to_boolean(tolua_S, 6,&arg4);
        if(!ok)
            return 0;
        bool ret = cobj->zipOneFile(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 6) 
    {
        std::string arg0;
        std::string arg1;
        unsigned char* arg2;
        unsigned long arg3;
        bool arg4;
        std::string arg5;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*;

        ok &= luaval_to_ulong(tolua_S, 5, &arg3);

        ok &= luaval_to_boolean(tolua_S, 6,&arg4);

        ok &= luaval_to_std_string(tolua_S, 7,&arg5);
        if(!ok)
            return 0;
        bool ret = cobj->zipOneFile(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "zipOneFile",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ZipHelper_zipOneFile'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ZipHelper_getFileDataInZip(lua_State* tolua_S)
{
    int argc = 0;
    framework::ZipHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ZipHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ZipHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ZipHelper_getFileDataInZip'", nullptr);
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
        framework::BinaryData* ret = cobj->getFileDataInZip(arg0, arg1);
        object_to_luaval<framework::BinaryData>(tolua_S, "pf.BinaryData",(framework::BinaryData*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        framework::BinaryData* ret = cobj->getFileDataInZip(arg0, arg1, arg2);
        object_to_luaval<framework::BinaryData>(tolua_S, "pf.BinaryData",(framework::BinaryData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFileDataInZip",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ZipHelper_getFileDataInZip'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ZipHelper_zipMultipleFiles(lua_State* tolua_S)
{
    int argc = 0;
    framework::ZipHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.ZipHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::ZipHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ZipHelper_zipMultipleFiles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        framework::Map* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_object<framework::Map>(tolua_S, 3, "pf.Map",&arg1);
        if(!ok)
            return 0;
        bool ret = cobj->zipMultipleFiles(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        framework::Map* arg1;
        bool arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_object<framework::Map>(tolua_S, 3, "pf.Map",&arg1);

        ok &= luaval_to_boolean(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        bool ret = cobj->zipMultipleFiles(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 4) 
    {
        std::string arg0;
        framework::Map* arg1;
        bool arg2;
        std::string arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_object<framework::Map>(tolua_S, 3, "pf.Map",&arg1);

        ok &= luaval_to_boolean(tolua_S, 4,&arg2);

        ok &= luaval_to_std_string(tolua_S, 5,&arg3);
        if(!ok)
            return 0;
        bool ret = cobj->zipMultipleFiles(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "zipMultipleFiles",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ZipHelper_zipMultipleFiles'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_ZipHelper_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.ZipHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::ZipHelper* ret = framework::ZipHelper::getInstance();
        object_to_luaval<framework::ZipHelper>(tolua_S, "pf.ZipHelper",(framework::ZipHelper*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ZipHelper_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_ZipHelper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ZipHelper)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"ZipHelper",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::ZipHelper* self = (framework::ZipHelper*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_ZipHelper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.ZipHelper");
    tolua_cclass(tolua_S,"ZipHelper","pf.ZipHelper","",nullptr);

    tolua_beginmodule(tolua_S,"ZipHelper");
        tolua_function(tolua_S,"zipOneFile",lua_psframework_ZipHelper_zipOneFile);
        tolua_function(tolua_S,"getFileDataInZip",lua_psframework_ZipHelper_getFileDataInZip);
        tolua_function(tolua_S,"zipMultipleFiles",lua_psframework_ZipHelper_zipMultipleFiles);
        tolua_function(tolua_S,"getInstance", lua_psframework_ZipHelper_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ZipHelper).name();
    g_luaType[typeName] = "pf.ZipHelper";
    g_typeCast["ZipHelper"] = "pf.ZipHelper";
    return 1;
}

int lua_psframework_SaveData_getPrefix(lua_State* tolua_S)
{
    int argc = 0;
    framework::SaveData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SaveData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SaveData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SaveData_getPrefix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getPrefix();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPrefix",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SaveData_getPrefix'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SaveData_serializeToFile(lua_State* tolua_S)
{
    int argc = 0;
    framework::SaveData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SaveData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SaveData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SaveData_serializeToFile'", nullptr);
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
        bool ret = cobj->serializeToFile(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "serializeToFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SaveData_serializeToFile'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SaveData_getVersion(lua_State* tolua_S)
{
    int argc = 0;
    framework::SaveData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SaveData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SaveData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SaveData_getVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getVersion();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SaveData_getVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SaveData_getData(lua_State* tolua_S)
{
    int argc = 0;
    framework::SaveData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SaveData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SaveData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SaveData_getData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getData();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SaveData_getData'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SaveData_setPrefix(lua_State* tolua_S)
{
    int argc = 0;
    framework::SaveData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SaveData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SaveData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SaveData_setPrefix'", nullptr);
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
        cobj->setPrefix(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setPrefix",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SaveData_setPrefix'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SaveData_setVersion(lua_State* tolua_S)
{
    int argc = 0;
    framework::SaveData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.SaveData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::SaveData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_SaveData_setVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setVersion(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setVersion",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SaveData_setVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_SaveData_createWithData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.SaveData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        framework::SaveData* ret = framework::SaveData::createWithData(arg0);
        object_to_luaval<framework::SaveData>(tolua_S, "pf.SaveData",(framework::SaveData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createWithData",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SaveData_createWithData'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_SaveData_deserializeFromFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.SaveData",0,&tolua_err)) goto tolua_lerror;
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
        framework::SaveData* ret = framework::SaveData::deserializeFromFile(arg0, arg1);
        object_to_luaval<framework::SaveData>(tolua_S, "pf.SaveData",(framework::SaveData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "deserializeFromFile",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SaveData_deserializeFromFile'.",&tolua_err);
#endif
    return 0;
}
int lua_psframework_SaveData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::SaveData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::SaveData();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.SaveData");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "SaveData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_SaveData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_SaveData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SaveData)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"SaveData",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::SaveData* self = (framework::SaveData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_SaveData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.SaveData");
    tolua_cclass(tolua_S,"SaveData","pf.SaveData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"SaveData");
        tolua_function(tolua_S,"getPrefix",lua_psframework_SaveData_getPrefix);
        tolua_function(tolua_S,"serializeToFile",lua_psframework_SaveData_serializeToFile);
        tolua_function(tolua_S,"getVersion",lua_psframework_SaveData_getVersion);
        tolua_function(tolua_S,"getData",lua_psframework_SaveData_getData);
        tolua_function(tolua_S,"setPrefix",lua_psframework_SaveData_setPrefix);
        tolua_function(tolua_S,"setVersion",lua_psframework_SaveData_setVersion);
        tolua_function(tolua_S,"new",lua_psframework_SaveData_constructor);
        tolua_function(tolua_S,"createWithData", lua_psframework_SaveData_createWithData);
        tolua_function(tolua_S,"deserializeFromFile", lua_psframework_SaveData_deserializeFromFile);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::SaveData).name();
    g_luaType[typeName] = "pf.SaveData";
    g_typeCast["SaveData"] = "pf.SaveData";
    return 1;
}

int lua_psframework_Mutex_lock(lua_State* tolua_S)
{
    int argc = 0;
    framework::Mutex* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Mutex",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Mutex*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Mutex_lock'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->lock();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "lock",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Mutex_lock'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Mutex_unlock(lua_State* tolua_S)
{
    int argc = 0;
    framework::Mutex* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Mutex",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Mutex*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Mutex_unlock'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->unlock();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unlock",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Mutex_unlock'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Mutex_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::Mutex* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::Mutex();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.Mutex");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Mutex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Mutex_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_Mutex_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Mutex)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Mutex",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::Mutex* self = (framework::Mutex*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_Mutex(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.Mutex");
    tolua_cclass(tolua_S,"Mutex","pf.Mutex","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Mutex");
        tolua_function(tolua_S,"lock",lua_psframework_Mutex_lock);
        tolua_function(tolua_S,"unlock",lua_psframework_Mutex_unlock);
        tolua_function(tolua_S,"new",lua_psframework_Mutex_constructor);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::Mutex).name();
    g_luaType[typeName] = "pf.Mutex";
    g_typeCast["Mutex"] = "pf.Mutex";
    return 1;
}

int lua_psframework_RecursiveMutex_lock(lua_State* tolua_S)
{
    int argc = 0;
    framework::RecursiveMutex* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.RecursiveMutex",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::RecursiveMutex*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_RecursiveMutex_lock'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->lock();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "lock",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RecursiveMutex_lock'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_RecursiveMutex_unlock(lua_State* tolua_S)
{
    int argc = 0;
    framework::RecursiveMutex* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.RecursiveMutex",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::RecursiveMutex*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_RecursiveMutex_unlock'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->unlock();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unlock",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RecursiveMutex_unlock'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_RecursiveMutex_constructor(lua_State* tolua_S)
{
    int argc = 0;
    framework::RecursiveMutex* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new framework::RecursiveMutex();
        tolua_pushusertype(tolua_S,(void*)cobj,"pf.RecursiveMutex");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "RecursiveMutex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_RecursiveMutex_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_psframework_RecursiveMutex_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RecursiveMutex)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"RecursiveMutex",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::RecursiveMutex* self = (framework::RecursiveMutex*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_RecursiveMutex(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.RecursiveMutex");
    tolua_cclass(tolua_S,"RecursiveMutex","pf.RecursiveMutex","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"RecursiveMutex");
        tolua_function(tolua_S,"lock",lua_psframework_RecursiveMutex_lock);
        tolua_function(tolua_S,"unlock",lua_psframework_RecursiveMutex_unlock);
        tolua_function(tolua_S,"new",lua_psframework_RecursiveMutex_constructor);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::RecursiveMutex).name();
    g_luaType[typeName] = "pf.RecursiveMutex";
    g_typeCast["RecursiveMutex"] = "pf.RecursiveMutex";
    return 1;
}

int lua_psframework_NetRequest_getProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetRequest_getProtocolId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getProtocolId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getProtocolId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetRequest_getProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetRequest_setBody(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetRequest_setBody'", nullptr);
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
        cobj->setBody(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setBody",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetRequest_setBody'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetRequest_setProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetRequest_setProtocolId'", nullptr);
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
        cobj->setProtocolId(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setProtocolId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetRequest_setProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetRequest_getBody(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetRequest_getBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getBody();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBody",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetRequest_getBody'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetRequest_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.NetRequest",0,&tolua_err)) goto tolua_lerror;
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
        framework::NetRequest* ret = framework::NetRequest::create(arg0, arg1);
        object_to_luaval<framework::NetRequest>(tolua_S, "pf.NetRequest",(framework::NetRequest*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetRequest_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_NetRequest_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NetRequest)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"NetRequest",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::NetRequest* self = (framework::NetRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_NetRequest(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.NetRequest");
    tolua_cclass(tolua_S,"NetRequest","pf.NetRequest","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"NetRequest");
        tolua_function(tolua_S,"getProtocolId",lua_psframework_NetRequest_getProtocolId);
        tolua_function(tolua_S,"setBody",lua_psframework_NetRequest_setBody);
        tolua_function(tolua_S,"setProtocolId",lua_psframework_NetRequest_setProtocolId);
        tolua_function(tolua_S,"getBody",lua_psframework_NetRequest_getBody);
        tolua_function(tolua_S,"create", lua_psframework_NetRequest_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::NetRequest).name();
    g_luaType[typeName] = "pf.NetRequest";
    g_typeCast["NetRequest"] = "pf.NetRequest";
    return 1;
}

int lua_psframework_NetResponse_getRelatedRequest(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetResponse_getRelatedRequest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::NetRequest* ret = cobj->getRelatedRequest();
        object_to_luaval<framework::NetRequest>(tolua_S, "pf.NetRequest",(framework::NetRequest*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRelatedRequest",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetResponse_getRelatedRequest'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetResponse_getProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetResponse_getProtocolId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getProtocolId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getProtocolId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetResponse_getProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetResponse_setBody(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetResponse_setBody'", nullptr);
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
        cobj->setBody(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setBody",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetResponse_setBody'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetResponse_setProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetResponse_setProtocolId'", nullptr);
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
        cobj->setProtocolId(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setProtocolId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetResponse_setProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetResponse_getBody(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetResponse_getBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getBody();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBody",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetResponse_getBody'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetResponse_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        framework::NetRequest* arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        ok &= luaval_to_object<framework::NetRequest>(tolua_S, 4, "pf.NetRequest",&arg2);
        if(!ok)
            return 0;
        framework::NetResponse* ret = framework::NetResponse::create(arg0, arg1, arg2);
        object_to_luaval<framework::NetResponse>(tolua_S, "pf.NetResponse",(framework::NetResponse*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetResponse_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_NetResponse_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NetResponse)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"NetResponse",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::NetResponse* self = (framework::NetResponse*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_NetResponse(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.NetResponse");
    tolua_cclass(tolua_S,"NetResponse","pf.NetResponse","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"NetResponse");
        tolua_function(tolua_S,"getRelatedRequest",lua_psframework_NetResponse_getRelatedRequest);
        tolua_function(tolua_S,"getProtocolId",lua_psframework_NetResponse_getProtocolId);
        tolua_function(tolua_S,"setBody",lua_psframework_NetResponse_setBody);
        tolua_function(tolua_S,"setProtocolId",lua_psframework_NetResponse_setProtocolId);
        tolua_function(tolua_S,"getBody",lua_psframework_NetResponse_getBody);
        tolua_function(tolua_S,"create", lua_psframework_NetResponse_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::NetResponse).name();
    g_luaType[typeName] = "pf.NetResponse";
    g_typeCast["NetResponse"] = "pf.NetResponse";
    return 1;
}

int lua_psframework_NetHandler_handleFailedMessage(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetHandler* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetHandler",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetHandler*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetHandler_handleFailedMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::NetResponse* arg0;

        ok &= luaval_to_object<framework::NetResponse>(tolua_S, 2, "pf.NetResponse",&arg0);
        if(!ok)
            return 0;
        cobj->handleFailedMessage(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "handleFailedMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetHandler_handleFailedMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetHandler_handleSuccessfulMessage(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetHandler* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetHandler",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetHandler*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetHandler_handleSuccessfulMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::NetResponse* arg0;

        ok &= luaval_to_object<framework::NetResponse>(tolua_S, 2, "pf.NetResponse",&arg0);
        if(!ok)
            return 0;
        cobj->handleSuccessfulMessage(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "handleSuccessfulMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetHandler_handleSuccessfulMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetHandler_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.NetHandler",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::NetHandler* ret = framework::NetHandler::create();
        object_to_luaval<framework::NetHandler>(tolua_S, "pf.NetHandler",(framework::NetHandler*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetHandler_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_NetHandler_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NetHandler)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"NetHandler",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::NetHandler* self = (framework::NetHandler*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_NetHandler(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.NetHandler");
    tolua_cclass(tolua_S,"NetHandler","pf.NetHandler","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"NetHandler");
        tolua_function(tolua_S,"handleFailedMessage",lua_psframework_NetHandler_handleFailedMessage);
        tolua_function(tolua_S,"handleSuccessfulMessage",lua_psframework_NetHandler_handleSuccessfulMessage);
        tolua_function(tolua_S,"create", lua_psframework_NetHandler_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::NetHandler).name();
    g_luaType[typeName] = "pf.NetHandler";
    g_typeCast["NetHandler"] = "pf.NetHandler";
    return 1;
}

int lua_psframework_NetFilter_filterSuccessfulMessage(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetFilter_filterSuccessfulMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::NetResponse* arg0;

        ok &= luaval_to_object<framework::NetResponse>(tolua_S, 2, "pf.NetResponse",&arg0);
        if(!ok)
            return 0;
        framework::NetResponse* ret = cobj->filterSuccessfulMessage(arg0);
        object_to_luaval<framework::NetResponse>(tolua_S, "pf.NetResponse",(framework::NetResponse*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "filterSuccessfulMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetFilter_filterSuccessfulMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetFilter_filterFailedMessage(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetFilter_filterFailedMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::NetResponse* arg0;

        ok &= luaval_to_object<framework::NetResponse>(tolua_S, 2, "pf.NetResponse",&arg0);
        if(!ok)
            return 0;
        framework::NetResponse* ret = cobj->filterFailedMessage(arg0);
        object_to_luaval<framework::NetResponse>(tolua_S, "pf.NetResponse",(framework::NetResponse*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "filterFailedMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetFilter_filterFailedMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.NetFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::NetFilter* ret = framework::NetFilter::create();
        object_to_luaval<framework::NetFilter>(tolua_S, "pf.NetFilter",(framework::NetFilter*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetFilter_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_NetFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NetFilter)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"NetFilter",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::NetFilter* self = (framework::NetFilter*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_NetFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.NetFilter");
    tolua_cclass(tolua_S,"NetFilter","pf.NetFilter","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"NetFilter");
        tolua_function(tolua_S,"filterSuccessfulMessage",lua_psframework_NetFilter_filterSuccessfulMessage);
        tolua_function(tolua_S,"filterFailedMessage",lua_psframework_NetFilter_filterFailedMessage);
        tolua_function(tolua_S,"create", lua_psframework_NetFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::NetFilter).name();
    g_luaType[typeName] = "pf.NetFilter";
    g_typeCast["NetFilter"] = "pf.NetFilter";
    return 1;
}

int lua_psframework_NetProtocol_getProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetProtocol_getProtocolId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getProtocolId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getProtocolId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetProtocol_getProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetProtocol_getServiceId(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetProtocol_getServiceId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getServiceId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getServiceId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetProtocol_getServiceId'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetProtocol_getRelatedHandler(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetProtocol_getRelatedHandler'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        framework::NetHandler* ret = cobj->getRelatedHandler();
        object_to_luaval<framework::NetHandler>(tolua_S, "pf.NetHandler",(framework::NetHandler*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRelatedHandler",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetProtocol_getRelatedHandler'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetProtocol_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        framework::NetHandler* arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        ok &= luaval_to_object<framework::NetHandler>(tolua_S, 4, "pf.NetHandler",&arg2);
        if(!ok)
            return 0;
        framework::NetProtocol* ret = framework::NetProtocol::create(arg0, arg1, arg2);
        object_to_luaval<framework::NetProtocol>(tolua_S, "pf.NetProtocol",(framework::NetProtocol*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetProtocol_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_NetProtocol_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NetProtocol)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"NetProtocol",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::NetProtocol* self = (framework::NetProtocol*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_NetProtocol(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.NetProtocol");
    tolua_cclass(tolua_S,"NetProtocol","pf.NetProtocol","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"NetProtocol");
        tolua_function(tolua_S,"getProtocolId",lua_psframework_NetProtocol_getProtocolId);
        tolua_function(tolua_S,"getServiceId",lua_psframework_NetProtocol_getServiceId);
        tolua_function(tolua_S,"getRelatedHandler",lua_psframework_NetProtocol_getRelatedHandler);
        tolua_function(tolua_S,"create", lua_psframework_NetProtocol_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::NetProtocol).name();
    g_luaType[typeName] = "pf.NetProtocol";
    g_typeCast["NetProtocol"] = "pf.NetProtocol";
    return 1;
}

int lua_psframework_NetCenter_addNetService(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_addNetService'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        framework::NetService* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_object<framework::NetService>(tolua_S, 3, "pf.NetService",&arg1);
        if(!ok)
            return 0;
        cobj->addNetService(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addNetService",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_addNetService'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_removeAllNetFilters(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_removeAllNetFilters'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->removeAllNetFilters();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeAllNetFilters",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_removeAllNetFilters'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_addNetFilter(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_addNetFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::NetFilter* arg0;

        ok &= luaval_to_object<framework::NetFilter>(tolua_S, 2, "pf.NetFilter",&arg0);
        if(!ok)
            return 0;
        cobj->addNetFilter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addNetFilter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_addNetFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_removeNetProtocol(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_removeNetProtocol'", nullptr);
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
        cobj->removeNetProtocol(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeNetProtocol",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_removeNetProtocol'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_removeNetFilter(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_removeNetFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::NetFilter* arg0;

        ok &= luaval_to_object<framework::NetFilter>(tolua_S, 2, "pf.NetFilter",&arg0);
        if(!ok)
            return 0;
        cobj->removeNetFilter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeNetFilter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_removeNetFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_removeNetService(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_removeNetService'", nullptr);
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
        cobj->removeNetService(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeNetService",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_removeNetService'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_sendMessage(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_sendMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::NetRequest* arg0;

        ok &= luaval_to_object<framework::NetRequest>(tolua_S, 2, "pf.NetRequest",&arg0);
        if(!ok)
            return 0;
        cobj->sendMessage(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "sendMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_sendMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_addNetProtocol(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_addNetProtocol'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            framework::NetProtocol* arg0;
            ok &= luaval_to_object<framework::NetProtocol>(tolua_S, 2, "pf.NetProtocol",&arg0);

            if (!ok) { break; }
            cobj->addNetProtocol(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1);

            if (!ok) { break; }
            framework::NetHandler* arg2;
            ok &= luaval_to_object<framework::NetHandler>(tolua_S, 4, "pf.NetHandler",&arg2);

            if (!ok) { break; }
            cobj->addNetProtocol(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addNetProtocol",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_addNetProtocol'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_dispatchFailedMessage(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_dispatchFailedMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::NetResponse* arg0;

        ok &= luaval_to_object<framework::NetResponse>(tolua_S, 2, "pf.NetResponse",&arg0);
        if(!ok)
            return 0;
        cobj->dispatchFailedMessage(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "dispatchFailedMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_dispatchFailedMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_dispatchSuccessfulMessage(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_dispatchSuccessfulMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::NetResponse* arg0;

        ok &= luaval_to_object<framework::NetResponse>(tolua_S, 2, "pf.NetResponse",&arg0);
        if(!ok)
            return 0;
        cobj->dispatchSuccessfulMessage(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "dispatchSuccessfulMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_dispatchSuccessfulMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_sendCommand(lua_State* tolua_S)
{
    int argc = 0;
    framework::NetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::NetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_NetCenter_sendCommand'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        cocos2d::Ref* arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 4, "cc.Ref",&arg2);
        if(!ok)
            return 0;
        cobj->sendCommand(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "sendCommand",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_sendCommand'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_NetCenter_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::NetCenter* ret = framework::NetCenter::getInstance();
        object_to_luaval<framework::NetCenter>(tolua_S, "pf.NetCenter",(framework::NetCenter*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_NetCenter_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_NetCenter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NetCenter)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"NetCenter",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::NetCenter* self = (framework::NetCenter*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_NetCenter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.NetCenter");
    tolua_cclass(tolua_S,"NetCenter","pf.NetCenter","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"NetCenter");
        tolua_function(tolua_S,"addNetService",lua_psframework_NetCenter_addNetService);
        tolua_function(tolua_S,"removeAllNetFilters",lua_psframework_NetCenter_removeAllNetFilters);
        tolua_function(tolua_S,"addNetFilter",lua_psframework_NetCenter_addNetFilter);
        tolua_function(tolua_S,"removeNetProtocol",lua_psframework_NetCenter_removeNetProtocol);
        tolua_function(tolua_S,"removeNetFilter",lua_psframework_NetCenter_removeNetFilter);
        tolua_function(tolua_S,"removeNetService",lua_psframework_NetCenter_removeNetService);
        tolua_function(tolua_S,"sendMessage",lua_psframework_NetCenter_sendMessage);
        tolua_function(tolua_S,"addNetProtocol",lua_psframework_NetCenter_addNetProtocol);
        tolua_function(tolua_S,"dispatchFailedMessage",lua_psframework_NetCenter_dispatchFailedMessage);
        tolua_function(tolua_S,"dispatchSuccessfulMessage",lua_psframework_NetCenter_dispatchSuccessfulMessage);
        tolua_function(tolua_S,"sendCommand",lua_psframework_NetCenter_sendCommand);
        tolua_function(tolua_S,"getInstance", lua_psframework_NetCenter_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::NetCenter).name();
    g_luaType[typeName] = "pf.NetCenter";
    g_typeCast["NetCenter"] = "pf.NetCenter";
    return 1;
}

int lua_psframework_Win32EventListener_setEnabled(lua_State* tolua_S)
{
    int argc = 0;
    framework::Win32EventListener* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Win32EventListener",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Win32EventListener*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Win32EventListener_setEnabled'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Win32EventListener_setEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Win32EventListener_isEnabled(lua_State* tolua_S)
{
    int argc = 0;
    framework::Win32EventListener* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Win32EventListener",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Win32EventListener*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Win32EventListener_isEnabled'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Win32EventListener_isEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Win32EventListener_setEventsSwallowed(lua_State* tolua_S)
{
    int argc = 0;
    framework::Win32EventListener* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Win32EventListener",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Win32EventListener*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Win32EventListener_setEventsSwallowed'", nullptr);
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
        cobj->setEventsSwallowed(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setEventsSwallowed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Win32EventListener_setEventsSwallowed'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Win32EventListener_isEventsSwallowed(lua_State* tolua_S)
{
    int argc = 0;
    framework::Win32EventListener* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Win32EventListener",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Win32EventListener*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Win32EventListener_isEventsSwallowed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isEventsSwallowed();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isEventsSwallowed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Win32EventListener_isEventsSwallowed'.",&tolua_err);
#endif

    return 0;
}
static int lua_psframework_Win32EventListener_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Win32EventListener)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Win32EventListener",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::Win32EventListener* self = (framework::Win32EventListener*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_Win32EventListener(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.Win32EventListener");
    tolua_cclass(tolua_S,"Win32EventListener","pf.Win32EventListener","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Win32EventListener");
        tolua_function(tolua_S,"setEnabled",lua_psframework_Win32EventListener_setEnabled);
        tolua_function(tolua_S,"isEnabled",lua_psframework_Win32EventListener_isEnabled);
        tolua_function(tolua_S,"setEventsSwallowed",lua_psframework_Win32EventListener_setEventsSwallowed);
        tolua_function(tolua_S,"isEventsSwallowed",lua_psframework_Win32EventListener_isEventsSwallowed);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::Win32EventListener).name();
    g_luaType[typeName] = "pf.Win32EventListener";
    g_typeCast["Win32EventListener"] = "pf.Win32EventListener";
    return 1;
}

int lua_psframework_Win32EventListenerKeyboard_createWithTarget(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.Win32EventListenerKeyboard",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
            return 0;
        framework::Win32EventListenerKeyboard* ret = framework::Win32EventListenerKeyboard::createWithTarget(arg0);
        object_to_luaval<framework::Win32EventListenerKeyboard>(tolua_S, "pf.Win32EventListenerKeyboard",(framework::Win32EventListenerKeyboard*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createWithTarget",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Win32EventListenerKeyboard_createWithTarget'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_Win32EventListenerKeyboard_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Win32EventListenerKeyboard)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Win32EventListenerKeyboard",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::Win32EventListenerKeyboard* self = (framework::Win32EventListenerKeyboard*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_Win32EventListenerKeyboard(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.Win32EventListenerKeyboard");
    tolua_cclass(tolua_S,"Win32EventListenerKeyboard","pf.Win32EventListenerKeyboard","pf.Win32EventListener",nullptr);

    tolua_beginmodule(tolua_S,"Win32EventListenerKeyboard");
        tolua_function(tolua_S,"createWithTarget", lua_psframework_Win32EventListenerKeyboard_createWithTarget);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::Win32EventListenerKeyboard).name();
    g_luaType[typeName] = "pf.Win32EventListenerKeyboard";
    g_typeCast["Win32EventListenerKeyboard"] = "pf.Win32EventListenerKeyboard";
    return 1;
}

int lua_psframework_Win32Notifier_removeEventListener(lua_State* tolua_S)
{
    int argc = 0;
    framework::Win32Notifier* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Win32Notifier",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Win32Notifier*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Win32Notifier_removeEventListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::Win32EventListener* arg0;

        ok &= luaval_to_object<framework::Win32EventListener>(tolua_S, 2, "pf.Win32EventListener",&arg0);
        if(!ok)
            return 0;
        cobj->removeEventListener(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeEventListener",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Win32Notifier_removeEventListener'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Win32Notifier_notify(lua_State* tolua_S)
{
    int argc = 0;
    framework::Win32Notifier* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Win32Notifier",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Win32Notifier*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Win32Notifier_notify'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        framework::Win32EventListener::Win32EventListenerType arg0;
        framework::Win32EventArgs* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_object<framework::Win32EventArgs>(tolua_S, 3, "pf.Win32EventArgs",&arg1);
        if(!ok)
            return 0;
        cobj->notify(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "notify",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Win32Notifier_notify'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Win32Notifier_addEventListener(lua_State* tolua_S)
{
    int argc = 0;
    framework::Win32Notifier* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.Win32Notifier",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::Win32Notifier*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_Win32Notifier_addEventListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        framework::Win32EventListener* arg0;

        ok &= luaval_to_object<framework::Win32EventListener>(tolua_S, 2, "pf.Win32EventListener",&arg0);
        if(!ok)
            return 0;
        cobj->addEventListener(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addEventListener",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Win32Notifier_addEventListener'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_Win32Notifier_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.Win32Notifier",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::Win32Notifier* ret = framework::Win32Notifier::getInstance();
        object_to_luaval<framework::Win32Notifier>(tolua_S, "pf.Win32Notifier",(framework::Win32Notifier*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_Win32Notifier_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_Win32Notifier_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Win32Notifier)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Win32Notifier",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::Win32Notifier* self = (framework::Win32Notifier*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_Win32Notifier(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.Win32Notifier");
    tolua_cclass(tolua_S,"Win32Notifier","pf.Win32Notifier","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Win32Notifier");
        tolua_function(tolua_S,"removeEventListener",lua_psframework_Win32Notifier_removeEventListener);
        tolua_function(tolua_S,"notify",lua_psframework_Win32Notifier_notify);
        tolua_function(tolua_S,"addEventListener",lua_psframework_Win32Notifier_addEventListener);
        tolua_function(tolua_S,"getInstance", lua_psframework_Win32Notifier_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::Win32Notifier).name();
    g_luaType[typeName] = "pf.Win32Notifier";
    g_typeCast["Win32Notifier"] = "pf.Win32Notifier";
    return 1;
}

int lua_psframework_KeyboardHelper_hookOn(lua_State* tolua_S)
{
    int argc = 0;
    framework::KeyboardHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.KeyboardHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::KeyboardHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_KeyboardHelper_hookOn'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->hookOn();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "hookOn",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_KeyboardHelper_hookOn'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_KeyboardHelper_isKeyPressed(lua_State* tolua_S)
{
    int argc = 0;
    framework::KeyboardHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.KeyboardHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::KeyboardHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_KeyboardHelper_isKeyPressed'", nullptr);
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
        bool ret = cobj->isKeyPressed(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isKeyPressed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_KeyboardHelper_isKeyPressed'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_KeyboardHelper_hookOff(lua_State* tolua_S)
{
    int argc = 0;
    framework::KeyboardHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.KeyboardHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::KeyboardHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_KeyboardHelper_hookOff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->hookOff();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "hookOff",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_KeyboardHelper_hookOff'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_KeyboardHelper_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"pf.KeyboardHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        framework::KeyboardHelper* ret = framework::KeyboardHelper::getInstance();
        object_to_luaval<framework::KeyboardHelper>(tolua_S, "pf.KeyboardHelper",(framework::KeyboardHelper*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_KeyboardHelper_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_psframework_KeyboardHelper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (KeyboardHelper)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"KeyboardHelper",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        framework::KeyboardHelper* self = (framework::KeyboardHelper*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_psframework_KeyboardHelper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.KeyboardHelper");
    tolua_cclass(tolua_S,"KeyboardHelper","pf.KeyboardHelper","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"KeyboardHelper");
        tolua_function(tolua_S,"hookOn",lua_psframework_KeyboardHelper_hookOn);
        tolua_function(tolua_S,"isKeyPressed",lua_psframework_KeyboardHelper_isKeyPressed);
        tolua_function(tolua_S,"hookOff",lua_psframework_KeyboardHelper_hookOff);
        tolua_function(tolua_S,"getInstance", lua_psframework_KeyboardHelper_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::KeyboardHelper).name();
    g_luaType[typeName] = "pf.KeyboardHelper";
    g_typeCast["KeyboardHelper"] = "pf.KeyboardHelper";
    return 1;
}
TOLUA_API int register_all_psframework(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_psframework_ZipHelper(tolua_S);
	lua_register_psframework_NetResponse(tolua_S);
	lua_register_psframework_ViewController(tolua_S);
	lua_register_psframework_EncryptedTMXTiledMap(tolua_S);
	lua_register_psframework_RecordHelper(tolua_S);
	lua_register_psframework_ListMenuItem(tolua_S);
	lua_register_psframework_RefInteger(tolua_S);
	lua_register_psframework_ListMenu(tolua_S);
	lua_register_psframework_NetHandler(tolua_S);
	lua_register_psframework_Map(tolua_S);
	lua_register_psframework_DirectionController(tolua_S);
	lua_register_psframework_NetRequest(tolua_S);
	lua_register_psframework_KeyboardHelper(tolua_S);
	lua_register_psframework_BinaryData(tolua_S);
	lua_register_psframework_SaveData(tolua_S);
	lua_register_psframework_RefBoolean(tolua_S);
	lua_register_psframework_Stack(tolua_S);
	lua_register_psframework_NetFilter(tolua_S);
	lua_register_psframework_GameScene(tolua_S);
	lua_register_psframework_Win32EventListener(tolua_S);
	lua_register_psframework_RecursiveMutex(tolua_S);
	lua_register_psframework_ScriptCCBReader(tolua_S);
	lua_register_psframework_ImageUtils(tolua_S);
	lua_register_psframework_Win32Notifier(tolua_S);
	lua_register_psframework_EncryptedTMXLayer(tolua_S);
	lua_register_psframework_Queue(tolua_S);
	lua_register_psframework_SqliteDb(tolua_S);
	lua_register_psframework_Vector(tolua_S);
	lua_register_psframework_GameLayer(tolua_S);
	lua_register_psframework_TitleSwitch(tolua_S);
	lua_register_psframework_CoreLayer(tolua_S);
	lua_register_psframework_Win32EventListenerKeyboard(tolua_S);
	lua_register_psframework_IOUtils(tolua_S);
	lua_register_psframework_NetCenter(tolua_S);
	lua_register_psframework_NetProtocol(tolua_S);
	lua_register_psframework_MaskLayer(tolua_S);
	lua_register_psframework_RefDouble(tolua_S);
	lua_register_psframework_RefString(tolua_S);
	lua_register_psframework_Mutex(tolua_S);
	lua_register_psframework_ModalLayer(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

