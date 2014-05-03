--[[
	Description: Child class of SqliteDb
	Author: M.Wan
	Date: 04/26/2014
]]

class("SqliteLua", {
		openSqlite = function(...)
			return SqliteDb:openSqlite(...)
		end
	})

function SqliteLua:selectTableAsLuaTable(...)
	local resultArray = self:selectTable(...)

	local luaArray = {}
	local resultCount = luaArray:count()
	for i = 0, resultCount - 1 do
		local dataRow = {}
		local columnDict = tolua.cast(resultArray:objectAtIndex(i), "__Dictionary")
		local columnNames = columnDict:allKeys()
		local columnCount = columnNames:count()
		for j = 0, columnCount - 1 do
			local columnName = tolua.cast(columnNames:objectAtIndex(j), "__String")
			local columnValue = tolua.cast(columnDict:objectForKey(columnNames:getCString()), "__String")
			dataRow[columnName:getCString()] = columnValue:getCString()
		end

		table.insert(luaArray, dataRow)
	end

	return luaArray
end

-- 多条件查询
function SqliteLua:selectTableByConditions(tableName, conditionDict)
	local resultArray = self:selectTableAsLuaTable(tableName, conditionDict)

	return resultArray
end

-- 单条件单值查询
function SqliteLua:selectTableByConditionWithOneValue(tableName, columnName, columnValue)
	local resultArray = self:selectTableAsLuaTable(tableName, columnName, columnValue)

	return resultArray
end

-- 单条件多值查询
function SqliteLua:selectTableByConditionWithMultipleValues(tableName, columnName, columnValues)
	local resultArray = self:selectTableAsLuaTable(tableName, columnName, columnValues)

	return resultArray
end

-- sql语句查询
function SqliteLua:selectTableBySql(tableName, sqlStr)
	local resultArray = self:selectTableAsLuaTable(tableName, sqlStr)

	return resultArray
end

-- 将Lua Table插入到表中
function SqliteLua:insertLuaTableIntoDB(luaTable, tableName)
	if type(luaTable) ~= "table" then
		return false
	end

	local dict = self:mergeValueToDictionary(luaTable)

	return self:insertTable(tableName, dict)
end

-- 将Lua Table更新到表中
function SqliteLua:updateLuaTableIntoDB(luaTable, tableName)
	if type(luaTable) ~= "table" then
		return false
	end

	local dict = self:mergeValueToDictionary(luaTable)

	return self:updateTable(tableName, dict, "ID", tostring(luaTable.ID))
end

function SqliteLua:mergeValueToDictionary(luaTable)
	local dict = __Dictionary:create()
	local count = 0
	for k, v in pairs(luaTable) do
		local str = ""
		if type(v) == "table" then
			local count = 0
			for k2, v2 in pairs(v) do
				if type(v2) == "table" then
					str = str .. v2:join("|")
				else
					str = str .. tostring(v2)
				end
				count = count + 1
				if count ~= v:getTotalCount() then
					str = str .. ","
				end
			end
		else
			str = tostring(v)
		end

		dict:setObject(__String:create(str), __String:create(k))
	end	

	return dict
end