#include "lua_framework_auto.hpp"
#include "framework.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "version.h"


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
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"pf.Queue");
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
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"pf.Stack");
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
            cocos2d::__Dictionary* arg1;
            ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 3, "cc.__Dictionary",&arg1);

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
            cocos2d::__Dictionary* arg1;
            ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 3, "cc.__Dictionary",&arg1);

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
            cocos2d::__Dictionary* arg1;
            ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 3, "cc.__Dictionary",&arg1);

            if (!ok) { break; }
            cocos2d::__Dictionary* arg2;
            ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 4, "cc.__Dictionary",&arg2);

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
            cocos2d::__Dictionary* arg1;
            ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 3, "cc.__Dictionary",&arg1);

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
        cocos2d::__Dictionary* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 3, "cc.__Dictionary",&arg1);
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
        cocos2d::__Array* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_object<cocos2d::__Array>(tolua_S, 3, "cc.__Array",&arg1);
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
            cocos2d::__Array* ret = cobj->selectTable(arg0, arg1, arg2);
            object_to_luaval<cocos2d::__Array>(tolua_S, "cc.__Array",(cocos2d::__Array*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            cocos2d::__Array* ret = cobj->selectTable(arg0);
            object_to_luaval<cocos2d::__Array>(tolua_S, "cc.__Array",(cocos2d::__Array*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            cocos2d::__Dictionary* arg1;
            ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 3, "cc.__Dictionary",&arg1);

            if (!ok) { break; }
            cocos2d::__Array* ret = cobj->selectTable(arg0, arg1);
            object_to_luaval<cocos2d::__Array>(tolua_S, "cc.__Array",(cocos2d::__Array*)ret);
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
            cocos2d::__Array* arg2;
            ok &= luaval_to_object<cocos2d::__Array>(tolua_S, 4, "cc.__Array",&arg2);

            if (!ok) { break; }
            cocos2d::__Array* ret = cobj->selectTable(arg0, arg1, arg2);
            object_to_luaval<cocos2d::__Array>(tolua_S, "cc.__Array",(cocos2d::__Array*)ret);
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
            cocos2d::__Array* ret = cobj->selectTable(arg0, arg1);
            object_to_luaval<cocos2d::__Array>(tolua_S, "cc.__Array",(cocos2d::__Array*)ret);
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
int lua_psframework_ViewController_init(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_ViewController_init'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_ViewController_init'.",&tolua_err);
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
    return 0;
}

int lua_register_psframework_ViewController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.ViewController");
    tolua_cclass(tolua_S,"ViewController","pf.ViewController","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ViewController");
        tolua_function(tolua_S,"load",lua_psframework_ViewController_load);
        tolua_function(tolua_S,"setScene",lua_psframework_ViewController_setScene);
        tolua_function(tolua_S,"init",lua_psframework_ViewController_init);
        tolua_function(tolua_S,"getScene",lua_psframework_ViewController_getScene);
        tolua_function(tolua_S,"unload",lua_psframework_ViewController_unload);
        tolua_function(tolua_S,"create", lua_psframework_ViewController_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::ViewController).name();
    g_luaType[typeName] = "pf.ViewController";
    g_typeCast["ViewController"] = "pf.ViewController";
    return 1;
}

int lua_psframework_GameLayer_setEnabled(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_setEnabled'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_setEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_onTouchEnded(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_onTouchEnded'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_onTouchEnded'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_onTouchMoved(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_onTouchMoved'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_onTouchMoved'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_isEnabled(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_isEnabled'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_isEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_onTouchCancelled(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_onTouchCancelled'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_onTouchCancelled'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_GameLayer_onTouchBegan(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameLayer_onTouchBegan'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameLayer_onTouchBegan'.",&tolua_err);
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
static int lua_psframework_GameLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameLayer)");
    return 0;
}

int lua_register_psframework_GameLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.GameLayer");
    tolua_cclass(tolua_S,"GameLayer","pf.GameLayer","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"GameLayer");
        tolua_function(tolua_S,"setEnabled",lua_psframework_GameLayer_setEnabled);
        tolua_function(tolua_S,"onTouchEnded",lua_psframework_GameLayer_onTouchEnded);
        tolua_function(tolua_S,"onTouchMoved",lua_psframework_GameLayer_onTouchMoved);
        tolua_function(tolua_S,"isEnabled",lua_psframework_GameLayer_isEnabled);
        tolua_function(tolua_S,"onTouchCancelled",lua_psframework_GameLayer_onTouchCancelled);
        tolua_function(tolua_S,"onTouchBegan",lua_psframework_GameLayer_onTouchBegan);
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
int lua_psframework_CoreLayer_init(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_CoreLayer_init'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_CoreLayer_init'.",&tolua_err);
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
static int lua_psframework_CoreLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CoreLayer)");
    return 0;
}

int lua_register_psframework_CoreLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.CoreLayer");
    tolua_cclass(tolua_S,"CoreLayer","pf.CoreLayer","pf.GameLayer",nullptr);

    tolua_beginmodule(tolua_S,"CoreLayer");
        tolua_function(tolua_S,"popLayer",lua_psframework_CoreLayer_popLayer);
        tolua_function(tolua_S,"init",lua_psframework_CoreLayer_init);
        tolua_function(tolua_S,"getTopLayer",lua_psframework_CoreLayer_getTopLayer);
        tolua_function(tolua_S,"pushLayer",lua_psframework_CoreLayer_pushLayer);
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
int lua_psframework_GameScene_init(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_GameScene_init'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_GameScene_init'.",&tolua_err);
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
            cocos2d::__Dictionary* arg0;
            ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 2, "cc.__Dictionary",&arg0);
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
        tolua_function(tolua_S,"init",lua_psframework_GameScene_init);
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

int lua_psframework_MaskLayerDelegate_onEventPenetrated(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayerDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayerDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayerDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayerDelegate_onEventPenetrated'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayerDelegate_onEventPenetrated'.",&tolua_err);
#endif

    return 0;
}
int lua_psframework_MaskLayerDelegate_onEventIntercepted(lua_State* tolua_S)
{
    int argc = 0;
    framework::MaskLayerDelegate* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"pf.MaskLayerDelegate",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (framework::MaskLayerDelegate*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_psframework_MaskLayerDelegate_onEventIntercepted'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_psframework_MaskLayerDelegate_onEventIntercepted'.",&tolua_err);
#endif

    return 0;
}
static int lua_psframework_MaskLayerDelegate_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MaskLayerDelegate)");
    return 0;
}

int lua_register_psframework_MaskLayerDelegate(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"pf.MaskLayerDelegate");
    tolua_cclass(tolua_S,"MaskLayerDelegate","pf.MaskLayerDelegate","",nullptr);

    tolua_beginmodule(tolua_S,"MaskLayerDelegate");
        tolua_function(tolua_S,"onEventPenetrated",lua_psframework_MaskLayerDelegate_onEventPenetrated);
        tolua_function(tolua_S,"onEventIntercepted",lua_psframework_MaskLayerDelegate_onEventIntercepted);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(framework::MaskLayerDelegate).name();
    g_luaType[typeName] = "pf.MaskLayerDelegate";
    g_typeCast["MaskLayerDelegate"] = "pf.MaskLayerDelegate";
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
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"pf.MaskLayer");
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
TOLUA_API int register_all_psframework(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_psframework_ViewController(tolua_S);
	lua_register_psframework_MaskLayerDelegate(tolua_S);
	lua_register_psframework_GameLayer(tolua_S);
	lua_register_psframework_Queue(tolua_S);
	lua_register_psframework_SqliteDb(tolua_S);
	lua_register_psframework_MaskLayer(tolua_S);
	lua_register_psframework_CoreLayer(tolua_S);
	lua_register_psframework_Stack(tolua_S);
	lua_register_psframework_GameScene(tolua_S);

	tolua_endmodule(tolua_S);

	::printVersion();
	return 1;
}

