--[[
	Description: Internal objects extensions
	Author: M.Wan
	Date: 04/26/2014
]]

function log(...)
	if DEBUG then
		print(os.date("%X"), unpack{...})
	end
end

-- Copy k-v from source table to the target table.
function table.shallowCopy(targetTable, sourceTable)
	if type(targetTable) == "table" and type(sourceTable) == "table" then
		for k, v in pairs(sourceTable) do
			targetTable[k] = v
		end
	end
end

-- Deep copy
function table.deepCopy(targetTable, sourceTable)
	if type(targetTable) == "table" and type(sourceTable) == "table" then
		for k, v in pairs(sourceTable) do
			if type(v) == "table" then
				if type(targetTable[k]) ~= "table" then
					targetTable[k] = {}
				end
				table.deepCopy(targetTable[k], v)
			else
				targetTable[k] = v
			end
		end
	end
end

-- get k-v count
function table.getTotalCount(table)
	if type(table) ~= "table" then
		return -1
	end
	
	local count = 0
	for k, v in pairs(table) do
		count = count + 1
	end

	return count
end

-- concat strings with the specified character
function table.join(table, joinChar)
	if type(table) ~= "table" or type(joinChar) ~= "string" then
		return
	end

	local str = ""
	local count = 0
	for k, v in pairs(table) do
		str = str .. tostring(v)
		count = count + 1
		if count ~= #table then		
			str = str .. joinChar	
		end
	end
	return str
end

-- do action for each array element in table
function table.forEachAsArray(table, action)
	if type(table) ~= "table" or type(action) ~= "function" then
		return
	end

	for _, v in ipairs(table) do
		action(v)
	end
end

-- do action for each element in table
function table.forEachAsHash(table, action)
	if type(table) ~= "table" or type(action) ~= "function" then
		return
	end

	for k, v in pairs(table) do
		action(k, v)
	end
end

-- whether the table contains the object which satisfies the condition
function table.contains(table, selector, ...)
	if type(table) ~= "table" then
		return false
	end

	for _, v in ipairs(table) do
		if selector(v, unpack{...}) then
			return true
		end
	end
	return false
end

-- find the object which satisfies the condition
function table.find(table, selector, ...)
	if type(table) ~= "table" then
		return false
	end

	for _, v in ipairs(table) do
		if selector(v, unpack{...}) then
			return v
		end
	end
	return nil
end

-- split string from the specified character
function string.split(str, splitChar)
	local resultTable = {}

	while true do
		local pos = string.find(str, splitChar)
		if not pos then
			resultTable[#resultTable + 1] = str
			break
		end
		local subStr = string.sub(str, 1, pos - 1)
		resultTable[#resultTable + 1] = subStr
		str = string.sub(str, pos + 1, #str)
	end

	return resultTable
end