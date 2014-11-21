--[[
	Description: Game save data structure
	Author: M.Wan
	Date: 11/21/2014
]]

--[[
Detail:
struct
{
	DWORD prefix;
	DWORD length;
}
]]
luaClass("GameSaveData")

local PREFIX = "PSSD"		-- 前缀