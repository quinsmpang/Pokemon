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
        /**
         * Get lua search paths.
         *
         * @return All package paths as a string.
         */
        const char *getPackagePath();

        /**
         * Set lua search paths.
         *
         * @param paths Set lua search paths.
         */
		void setPackagePaths(std::vector<std::string> &paths);

        /**
         * Execute a lua script.
         *
         * @param filePath The script to run.
         */
		void executeScriptFile(const std::string &filePath);

        /**
         * Set value of the specified key of a lua table.
         *
         * @param tableName Lua table name.
         * @param key Table key.
         * @param value The value you would like to set.
         * @param valueType Lua usertype name.
         */
		void setTableField(const std::string &tableName, const std::string &key, cocos2d::Ref *value, const std::string &valueType);

        /**
         * Execute a child function in the specified table.
         *
         * @param tableName Lua table name.
         * @param functionName The function name.
         * @param params Function parameters.
         * @param paramTypes Function parameter usertype names.
         * @param hasReturnValue Whether the function has return value.
         */
		void *executeTableFunction(const std::string &tableName, const std::string &functionName, cocos2d::Vector<cocos2d::Ref*> params, cocos2d::Vector<cocos2d::Ref*> paramTypes, bool hasReturnValue);

        /**
         * Execute a peertable function.
         *
         * @param userdata The related userdata of the peertable.
         * @param functionName The function name.
         * @param params Function parameters.
         * @param paramTypes Function parameter usertype names.
         * @param hasReturnValue Whether the function has return value.
         */
		void *executePeertableFunction(cocos2d::Ref *userdata, const std::string &functionName, cocos2d::Vector<cocos2d::Ref*> params, cocos2d::Vector<cocos2d::Ref*> paramTypes, bool hasReturnValue);

	private:
		void setPackagePath(const std::string &path);

		bool hasPeertable(void *userdata);

		bool hasFunction(void *userdata, const std::string &functionName);

		void *executeFunction(cocos2d::Vector<cocos2d::Ref*> params, cocos2d::Vector<cocos2d::Ref*> paramTypes, bool hasReturnValue);
	};

}

#endif