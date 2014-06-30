--[[
	Description: extensions of RecordHelper
	Author: M.Wan
	Date: 05/19/2014
]]

RecordHelperLua = {}

-- analyze the record string to lua table
function RecordHelperLua:getTableFromRecord(filePath)
	local content = RecordHelper:getInstance():readRecord(filePath)
	log(string.format("Load record content: %s", content))
	local resultTable = {}

	local pairTable = string.split(content, ";")
	for _, pair in ipairs(pairTable) do
		local kv = string.split(pair, "|")
		resultTable[kv[1]] = kv[2]
	end

	return resultTable
end

-- save table pairs except functions.
function RecordHelperLua:recordTable(filePath, table)
	if type(table) ~= "table" then
		return false
	end

	local content = ""
	local index = 1
	for k, v in pairs(table) do
		if type(v) ~= "function" and type(v) ~= "table" and type(v) ~= "nil" then
			if index > 1 then
				content = content .. ";"
			end
			content = content .. k .. "|" .. v
		end
		index = index + 1
	end

	log(string.format("Save record content: %s", content))
	return RecordHelper:getInstance():writeRecord(filePath, content)
end