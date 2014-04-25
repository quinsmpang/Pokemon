/******************************
Description: Encapsulate sqlite3 operations.
Author: M.Wan
Date: 4/25/2014
******************************/

#ifndef __SQLITE_SQLITEDB__
#define __SQLITE_SQLITEDB__

#include "cocos2d.h"
#include "libsqlite\sqlite3.h"

namespace framework
{
	class SqliteDb : public cocos2d::Ref
	{
	public:
		virtual ~SqliteDb();

		// open sqlite3 db
		static SqliteDb *openSqlite(const std::string &dbPath);

		// clear cache
		static void clearConnectionCache();

		const char *getValueTypeName(cocos2d::Ref *value);

		bool createTable(const std::string &tableName, cocos2d::__Array *columns);

		bool dropTable(const std::string &tableName);

		bool insertTable(const std::string &tableName, cocos2d::__Dictionary *keyValueDict);
		bool clearTable(const std::string &tableName);
		// delete data which matches the conditions.
		bool deleteFromTable(const std::string &tableName, cocos2d::__Dictionary *conditionDict);
		// delete data which matches the condition
		bool deleteFromTable(const std::string &tableName, const std::string &columnName, const std::string &columnValue);
		// update data which match the conditions
		bool updateTable(const std::string &tableName, cocos2d::__Dictionary *keyValueDict, cocos2d::__Dictionary *conditionDict = nullptr);
		// update data which matches the condition
		bool updateTable(const std::string &tableName, cocos2d::__Dictionary *keyValueDict, const std::string &columnName, const std::string &columnValue);

		int getRecordCount(const std::string &tableName);
		// consult data which match the conditions
		cocos2d::__Array *selectTable(const std::string &tableName, cocos2d::__Dictionary *conditionDict = nullptr);
		// consult data which matches the condition
		cocos2d::__Array *selectTable(const std::string &tableName, const std::string &columnName, const std::string &columnValue);
		
		cocos2d::__Array *selectTable(const std::string &tableName, const std::string &columnName, cocos2d::__Array *columnValues);
		// execute sql statement to consult
		cocos2d::__Array *selectTable(const std::string &tableName, const std::string &sql);

	protected:
		sqlite3 *_db;

		bool initWithFile(const std::string &file);

		std::string getExecuteSql(const std::string &tableName, cocos2d::__Dictionary *conditionDict = nullptr);

		std::string getExecuteSql(const std::string &tableName, const std::string &columnName, const std::string &columnValue);

		std::string getExecuteSql(const std::string &tableName, const std::string &columnName, cocos2d::__Array *columnValues);
		
		bool executeSql(const std::string &sql);

		cocos2d::__Array *executeQuery(const std::string &sql);
		// convert conditions to string
		std::string convertConditionDictionary(cocos2d::__Dictionary *conditionDict);
	};
}

#endif