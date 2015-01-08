/******************************
Description: Encapsulate sqlite3 operations.
Author: M.Wan
Date: 4/25/2014
******************************/

#ifndef __SQLITE_SQLITEDB__
#define __SQLITE_SQLITEDB__

#include "cocos2d.h"
#include "libsqlite/sqlite3.h"
#include "../containers/Vector.h"
#include "../containers/Map.h"

namespace framework
{
	class SqliteDb : public cocos2d::Ref
	{
	public:
		virtual ~SqliteDb();

		/**
         * Open a sqlite3 db and return a db object.
         *
         * @param dbPath Db file path.
         *
         * @return SqliteDb object.
         */
		static SqliteDb *openSqlite(const std::string &dbPath);

		/**
         * Clear all connection cache.
         */
		static void clearConnectionCache();

        /**
         * Get base cocos2dx object type name.
         *
         * @param value Cocos2dx object.
         *
         * @return The type name of the object.
         */
		const char *getValueTypeName(cocos2d::Ref *value);

        /**
         * Create a new table in db.
         *
         * @param tableName Name of the table.
         * @param columns All column names of the table.
         *
         * @return Execution result.
         */
		bool createTable(const std::string &tableName, Vector *columns);
        /**
         * Drop table in db.
         *
         * @param tableName Name of the table.
         *
         * @return Execution result.
         */
		bool dropTable(const std::string &tableName);
        /**
         * Insert new data into the table.
         *
         * @param tableName Name of the table.
         * @param keyValueDict Key-Value pairs.
         *
         * @return Execution result.
         */
		bool insertTable(const std::string &tableName, Map *keyValueDict);
        /**
         * Clear all data of the table.
         *
         * @param tableName Name of the table.
         *
         * @return Execution result.
         */
		bool clearTable(const std::string &tableName);
        /**
         * Delete data which matches the conditions from table.
         *
         * @param tableName Name of the table.
         * @param conditionDict All filter conditions.
         *
         * @return Execution result.
         */
		bool deleteFromTable(const std::string &tableName, Map *conditionDict);
		/**
         * Delete data which matches the condition 'columnName' = 'columnValue'.
         *
         * @param tableName Name of the table.
         * @param columnName Condition column name.
         * @param columnValue Condition column value.
         *
         * @return Execution result.
         */
		bool deleteFromTable(const std::string &tableName, const std::string &columnName, const std::string &columnValue);
        /**
         * Update data which matches the conditions from table.
         *
         * @param tableName Name of the table.
         * @param keyValueDict Update key-value pairs.
         * @param conditionDict All filter conditions.
         *
         * @return Execution result.
         */
		bool updateTable(const std::string &tableName, Map *keyValueDict, Map *conditionDict = nullptr);
		/**
         * Update data which matches the condition 'columnName' = 'columnValue'.
         *
         * @param tableName Name of the table.
         * @param keyValueDict Update key-value pairs.
         * @param columnName Condition column name.
         * @param columnValue Condition column value.
         *
         * @return Execution result.
         */
		bool updateTable(const std::string &tableName, Map *keyValueDict, const std::string &columnName, const std::string &columnValue);

        /**
         * Return data count of the table.
         *
         * @param tableName Name of the table.
         *
         * @return Data count.
         */
		int getRecordCount(const std::string &tableName);
		/**
         * Select data from specified table, return all data if there is no condition.
         *
         * @param tableName Name of the table.
         * @param conditionDict Filter conditions.
         *
         * @return Selected data collection of table.
         */
		Vector *selectTable(const std::string &tableName, Map *conditionDict = nullptr);
		/**
         * Select single data which satisfies 'columnName' = 'columnValue' from specified table.
         *
         * @param tableName Name of the table.
         * @param columnName Condition column name.
         * @param columnValue Condition column value.
         *
         * @return Selected data collection of table.
         */
		Vector *selectTable(const std::string &tableName, const std::string &columnName, const std::string &columnValue);
		/**
         * Select all data which satisfies 'columnName' = 'columnValues[i]' from specified table.
         *
         * @param tableName Name of the table.
         * @param columnName Condition column name.
         * @param columnValues All condition column values.
         *
         * @return Selected data collection of table.
         */
		Vector *selectTable(const std::string &tableName, const std::string &columnName, Vector *columnValues);
		/**
         * Select data with a sql statement.
         *
         * @param tableName Name of the table.
         * @param sql T-SQL statement.
         *
         * @return Selected data collection of table.
         */
		Vector *selectTable(const std::string &tableName, const std::string &sql);

	protected:
		sqlite3 *_db;

		bool initWithFile(const std::string &file);

		std::string getExecuteSql(const std::string &tableName, Map *conditionDict = nullptr);

		std::string getExecuteSql(const std::string &tableName, const std::string &columnName, const std::string &columnValue);

		std::string getExecuteSql(const std::string &tableName, const std::string &columnName, Vector *columnValues);
		
		bool executeSql(const std::string &sql);

		Vector *executeQuery(const std::string &sql);
		// convert conditions to string
		std::string convertConditionDictionary(Map *conditionDict);
	};
}

#endif