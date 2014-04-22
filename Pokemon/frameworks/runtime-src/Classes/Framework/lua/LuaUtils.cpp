extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "LuaUtils.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

namespace framework
{

static std::string defaultPackagePath;

/*****************public api*****************/
const char *LuaUtils::getPackagePath()
{
	auto pEngine = LuaEngine::getInstance();
	lua_State *pState = pEngine->getLuaStack()->getLuaState();
	lua_getglobal(pState, "package");	// L: package
	lua_getfield(pState, -1, "path");	// L: package, path
	/*
	lua_pushstring(pState, "path");
	lua_gettable(pState, -2);	// get package["path"];  L: package, "path", path
	*/
	std::string path = lua_tostring(pState, -1);
	// clean stack
	lua_pop(pState, 1);
	return path.c_str();
}

void LuaUtils::setPackagePaths(std::vector<std::string> &paths)
{
	if (defaultPackagePath.size() <= 0)
	{
		defaultPackagePath = LuaUtils::getPackagePath();
	}
	std::string path = defaultPackagePath;
	for (auto iter = paths.begin(); iter != paths.end(); ++iter)
	{
		path.append(";");
		path.append(*iter);
		path.append("/?.lua");
	}
	LuaUtils::setPackagePath(path);
}

void LuaUtils::executeScriptFile(const std::string &filePath)
{
	auto pEngine = LuaEngine::getInstance();

	std::string path = FileUtils::getInstance()->fullPathForFilename(filePath.c_str());
	pEngine->executeScriptFile(path.c_str());
}

void LuaUtils::setTableField(const std::string &tableName, const std::string &key, cocos2d::Ref *value, const std::string &valueType)
{
	auto pEngine = LuaEngine::getInstance();
	lua_State *pState = pEngine->getLuaStack()->getLuaState();
	// push tableName
	lua_getglobal(pState, tableName.c_str());	// L: tableName
	// check whether the top one is lua table
	if (!lua_istable(pState, -1))
	{
		CCLOG("[LUA ERROR] tableName \"%s\" doesn't represent a Lua table.", tableName.c_str());
		// clean stack
		lua_pop(pState, 1);
		return;
	}
	// push key
	lua_pushstring(pState, key.c_str());
	pEngine->getLuaStack()->pushObject(value, valueType.c_str());  
	// L: table, key, value    so table is at -3
	lua_settable(pState, -3);
	// clean the stack
	lua_pop(pState, 1);
}

void *LuaUtils::executeTableFunction(const std::string &tableName, const std::string &functionName, cocos2d::Vector<cocos2d::Ref*> params, cocos2d::Vector<cocos2d::Ref*> paramTypes, bool hasReturnValue)
{
	auto pEngine = LuaEngine::getInstance();
	lua_State *pState = pEngine->getLuaStack()->getLuaState();

	lua_getglobal(pState, tableName.c_str());	// L: tableName

	if (!lua_istable(pState, -1))
	{
		CCLOG("[LUA ERROR] tableName \"%s\" doesn't represent a Lua table.", tableName.c_str());
		// clean stack
		lua_pop(pState, 1);
		return nullptr;
	}
	// push function name
	lua_pushstring(pState, functionName.c_str());  // L: tableName, functionName
	// index function from table
	lua_gettable(pState, -2);
	
	if (!lua_isfunction(pState, -1))
	{
		CCLOG("[LUA ERROR] functionName \"%s\" doesn't represent a Lua function.", functionName.c_str());
		// clean stack
		lua_pop(pState, 1);
		return nullptr;
	}
	// the first parameter is the lua instance itself
	lua_pushvalue(pState, -2);
	// execute function and get return value if it has.
	void *pResult = LuaUtils::executeFunction(params, paramTypes, hasReturnValue);
	// clean the stack
	lua_pop(pState, 1);

	return pResult;
}

void *LuaUtils::executePeertableFunction(cocos2d::Ref *userdata, const std::string &functionName, cocos2d::Vector<cocos2d::Ref*> params, cocos2d::Vector<cocos2d::Ref*> paramTypes, bool hasReturnValue)
{
	auto pEngine = LuaEngine::getInstance();
	lua_State *pState = pEngine->getLuaStack()->getLuaState();

	// if there is no peertable in the userdata or there is no function in peertable, then return directly.
	if (!LuaUtils::hasFunction(userdata, functionName))
	{
		return nullptr;
	}

	tolua_pushusertype(pState, userdata, "Ref");	// L: userdata
	// push function name
	lua_pushstring(pState, functionName.c_str());	// L: userdata, functionName
	// get function
	lua_gettable(pState, -2);
	// the first parameter is the lua instance itself
	lua_pushvalue(pState, -2);
	// execute function and get return value if it has.
	void *pResult = LuaUtils::executeFunction(params, paramTypes, hasReturnValue);
	// clean the stack
	lua_pop(pState, 1);

	return pResult;
}

/*****************private api*****************/
void LuaUtils::setPackagePath(const std::string &path)
{
	auto pEngine = LuaEngine::getInstance();
	lua_State *pState = pEngine->getLuaStack()->getLuaState();
	lua_getglobal(pState, "package");	// L: package
	lua_pushstring(pState, path.c_str());	// L: package, path
	lua_setfield(pState, -2, "path");
	lua_pop(pState, 1);
}

bool LuaUtils::hasPeertable(void *userdata)
{
	auto pEngine = LuaEngine::getInstance();
	lua_State *pState = pEngine->getLuaStack()->getLuaState();

	bool hasPeer = false;

	tolua_pushusertype(pState, userdata, "Ref");	// L: userdata
	// get peertable
	lua_getfenv(pState, -1);	// L: userdata, peer
	// if the entry is at TOLUA_NOPEER, then there is no peertable in the userdata
	if (lua_rawequal(pState, -1, TOLUA_NOPEER))
	{
		hasPeer = false;
	}
	else
	{
		hasPeer = true;
	}
	// don't clean the stack, remain the userdata.
	lua_pop(pState, 2);		// L: userdata

	return hasPeer;
}

bool LuaUtils::hasFunction(void *userdata, const std::string &functionName)
{
	if (!LuaUtils::hasPeertable(userdata))
	{
		return false;
	}

	auto pEngine = LuaEngine::getInstance();
	lua_State *pState = pEngine->getLuaStack()->getLuaState();

	// push userdata
	tolua_pushusertype(pState, userdata, "Ref");	// L: userdata
	// get peertable
	lua_getfenv(pState, -1);	// L: userdata, peer
	// push function name
	lua_pushstring(pState, functionName.c_str());	// L: userdata, peer, functionName
	// get function
	lua_gettable(pState, -2);	// L: userdata, peer, functionName, function

	bool isFunction = lua_isfunction(pState, -1);

	lua_pop(pState, 3);

	return isFunction;
}

void *LuaUtils::executeFunction(cocos2d::Vector<cocos2d::Ref*> params, cocos2d::Vector<cocos2d::Ref*> paramTypes, bool hasReturnValue)
{
	auto pEngine = LuaEngine::getInstance();
	lua_State *pState = pEngine->getLuaStack()->getLuaState();

	// indice the function entry
	int traceback = 0;
	// get exception handler
	lua_getglobal(pState, "__G__TRACKBACK__");	// L: __G__TRACKBACK__
	if (!lua_isfunction(pState, -1))
	{
		lua_pop(pState, 1);
	}
	else
	{
		// push the handler to index -3.
		lua_insert(pState, -3);
		traceback = -3;
	}

	// push parameters
	if (true)
	{
		if (traceback != 0)
		{
			// calculate params count
			traceback -= params.size();
		}

		for (int i = 0; i < params.size(); ++i)
		{
			Ref *pParam = params.at(i);
			const char *paramType = ((__String*)paramTypes.at(i))->getCString();
			// check basic types
			if (strcmp(paramType, "__Bool") == 0)
			{
				bool boolValue = ((__Bool*)pParam)->getValue();
				lua_pushboolean(pState, boolValue);
			}
			else if (strcmp(paramType, "__Integer") == 0)
			{
				int intValue = ((__Integer*)pParam)->getValue();
				lua_pushnumber(pState, intValue);
			}
			else if (strcmp(paramType, "__Float") == 0)
			{
				float floatValue = ((__Float*)pParam)->getValue();
				lua_pushnumber(pState, floatValue);
			}
			else if (strcmp(paramType, "__Double") == 0)
			{
				float doubleValue = ((__Double*)pParam)->getValue();
				lua_pushnumber(pState, doubleValue);
			}
			else if (strcmp(paramType, "__String") == 0)
			{
				const char *strValue = ((__String*)pParam)->getCString();
				lua_pushstring(pState, strValue);
			}
			else
			{
				// push cocos2dx object
				pEngine->getLuaStack()->pushObject(pParam, paramType);
			}
		}
	}

	// call function	/* L: ... G, func, self, arg1, arg2, .... argn */
	int error = lua_pcall(pState, params.size() + 1, hasReturnValue ? 1 : 0, traceback);

	void *pResult = NULL;

	if (error)	// L: ... G, error
	{
		if (traceback == 0)
		{
			const char *szError = lua_tostring(pState, -1);
			CCLOG("[LUA ERROR] %s", szError);
		}
		lua_pop(pState, 1);	// pop error	// L: ... G
	}
	else
	{
		// check return value
		if (hasReturnValue)		// L: ... G, result
		{
			if (lua_type(pState, -1) == LUA_TBOOLEAN)
			{
				bool value = lua_toboolean(pState, -1);
				pResult = __Bool::create(value);
			}
			else if (lua_type(pState, -1) == LUA_TNUMBER)
			{
				double value = lua_tonumber(pState, -1);
				pResult = __Double::create(value);
			}
			else if (lua_type(pState, -1) == LUA_TSTRING)
			{
				const char *value = lua_tostring(pState, -1);
				pResult = __String::create(value);
			}
			else
			{
				pResult = tolua_tousertype(pState, -1, nullptr);
			}
			lua_pop(pState, 1);
		}
	}

	// remove __G__TRACEBACK__
	if (traceback != 0)
	{
		lua_pop(pState, 1);
	}

	return pResult;
}

}