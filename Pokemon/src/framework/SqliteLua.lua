--[[
	Description: Support passing lua table to operate sqlite3
	Author: M.Wan
	Date: 04/26/2014
]]

class("SqliteLua", {
		openSqlite = function(...)
			return SqliteDb:openSqlite(...)
		end
	})

-- columns is a lua array
function SqliteLua:createTableByLuaArray(tableName, columns)
	if type(columns) ~= "table" then
		return false
	end

	local columnArray = Vector:create()
	for _, col in ipairs(columns) do
		columnArray:addString(col)
	end

	return self:createTable(tableName, columnArray)
end

function SqliteLua:selectTableAsLuaTable(...)
	local resultArray = self:selectTable(...)

	local luaArray = {}
	local resultCount = resultArray:getLength()
	for i = 0, resultCount - 1 do
		local dataRow = {}
		local columnDict = resultArray:objectAt(i)
		local columnNames = columnDict:allKeys()
		local columnCount = columnNames:getLength()
		for j = 0, columnCount - 1 do
			local columnName = tolua.cast(columnNames:objectAt(j), "pf.RefString")
			local columnValue = tolua.cast(columnDict:objectForKey(columnName:getCString()), "pf.RefString")
			dataRow[columnName:getCString()] = columnValue:getCString()
		end

		table.insert(luaArray, dataRow)
	end

	return luaArray
end

-- 多条件查询
function SqliteLua:selectTableByConditions(tableName, conditionDict)
	if type(conditionDict) ~= "table" then
		return nil
	end

	local dict = Map:create()
	for k, v in pairs(conditionDict) do
		dict:setStringForKey(v, k)
	end
	local resultArray = self:selectTableAsLuaTable(tableName, dict)

	return resultArray
end

-- 单条件单值查询
function SqliteLua:selectTableByConditionWithOneValue(tableName, columnName, columnValue)
	local resultArray = self:selectTableAsLuaTable(tableName, columnName, columnValue)

	return resultArray
end

-- 单条件多值查询
function SqliteLua:selectTableByConditionWithMultipleValues(tableName, columnName, columnValues)
	if type(columnValues) ~= "table" then
		return nil
	end

	local values = Vector:create()
	for _, v in ipairs(columnValues) do
		values:addString(v)
	end
	local resultArray = self:selectTableAsLuaTable(tableName, columnName, values)

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

	return self:updateTable(tableName, dict, "id", tostring(luaTable.id))
end

function SqliteLua:deleteFromTableWithOneValue(tableName, columnName, columnValue)
	return self:deleteFromTable(tableName, columnName, columnValue)
end

function SqliteLua:deleteFromTableByConditions(tableName, conditionDict)
	if type(conditionDict) ~= "table" then
		return false
	end

	local dict = Map:create()
	for k, v in pairs(conditionDict) do
		dict:setStringForKey(v, k)
	end
	return self:deleteFromTable(tableName, dict)
end

function SqliteLua:mergeValueToDictionary(luaTable)
	local dict = Map:create()
	local count = 0
	-- concat by ',' at the first level
	-- concat by '|' at the second level
	for k, v in pairs(luaTable) do
		local str = ""
		if type(v) == "table" then
			local count = 0
			for k2, v2 in pairs(v) do
				if type(v2) == "table" then
					str = str .. table.join(v2, "|")
				else
					str = str .. tostring(v2)
				end
				count = count + 1
				if count ~= table.getTotalCount(v) then
					str = str .. ","
				end
			end
		else
			str = tostring(v)
		end

		dict:setStringForKey(str, k)
	end	

	return dict
end