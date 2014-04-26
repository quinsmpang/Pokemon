--[[
	Description: Internal objects extensions
	Author: M.Wan
	Date: 04/26/2014
]]

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
	local count = 0
	for k, v in pairs(table) do
		count = count + 1
	end

	return count
end

-- lock table, for synchronization
function table.lock(table)
	local mt = {
		__newindex = function(_, key, value)
			error("The table is locked, you can't insert any new data now.")
		end
	}
	setmetatable(table, mt)
end

-- unlock table
function table.unlock(table)
	setmetatable(table, nil)
end