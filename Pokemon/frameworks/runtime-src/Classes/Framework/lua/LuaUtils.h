/******************************
Description: Deal with Lua and cocos2dx
Author: M.Wan
Date: 4/17/2014
******************************/

#ifndef __LUA_LUAUTIL__
#define __LUA_LUAUTIL__

#include "cocos2d.h"
#include "../base/Macros.h"
#include <vector>
#include <string>

namespace framework
{

	class LuaUtils
	{
        SINGLETON(LuaUtils)
	public:
        const char *getPackagePath();

		void setPackagePaths(std::vector<std::string> &paths);

		void executeScriptFile(const std::string &filePath);

		void setTableField(const std::string &tableName, const std::string &key, cocos2d::Ref *value, const std::string &valueType);

		void *executeTableFunction(const std::string &tableName, const std::string &functionName, cocos2d::Vector<cocos2d::Ref*> params, cocos2d::Vector<cocos2d::Ref*> paramTypes, bool hasReturnValue);

		void *executePeertableFunction(cocos2d::Ref *userdata, const std::string &functionName, cocos2d::Vector<cocos2d::Ref*> params, cocos2d::Vector<cocos2d::Ref*> paramTypes, bool hasReturnValue);

	private:
		static LuaUtils *_instance;

		void setPackagePath(const std::string &path);

		bool hasPeertable(void *userdata);

		bool hasFunction(void *userdata, const std::string &functionName);

		void *executeFunction(cocos2d::Vector<cocos2d::Ref*> params, cocos2d::Vector<cocos2d::Ref*> paramTypes, bool hasReturnValue);
	};

}

#endif