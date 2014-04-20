/******************************
	Description: Deal with Lua and cocos2dx
	Author: M.Wan
	Date: 4/17/2014
******************************/

#ifndef __LUA_LUAUTIL__
#define __LUA_LUAUTIL__

#include "cocos2d.h"
#include <vector>
#include <string>

namespace framework
{

class LuaUtils
{
public:
	static const char *getPackagePath();

	static void setPackagePaths(std::vector<std::string> &paths);

	static void executeScriptFile(const std::string &filePath);

	static void setTableField(const std::string &tableName, const std::string &key, cocos2d::Ref *value, const std::string &valueType);

	static void *executeTableFunction(const std::string &tableName, const std::string &functionName, cocos2d::Vector<cocos2d::Ref*> *params, cocos2d::Vector<cocos2d::Ref*> *paramTypes, bool hasReturnValue);

	static void *executePeertableFunction(cocos2d::Ref *userdata, const std::string &functionName, cocos2d::Vector<cocos2d::Ref*> *params, cocos2d::Vector<cocos2d::Ref*> *paramTypes, bool hasReturnValue);

private:
	static void setPackagePath(const std::string &path);

	static bool hasPeertable(void *userdata);

	static bool hasFunction(void *userdata, const std::string &functionName);

	static void *executeFunction(cocos2d::Vector<cocos2d::Ref*> *params, cocos2d::Vector<cocos2d::Ref*> *paramTypes, bool hasReturnValue);
};

}

#endif