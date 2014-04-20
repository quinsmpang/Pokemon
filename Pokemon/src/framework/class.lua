--[[
	Description: To create subclass of cpp class
	Author: M.Wan
	Date: 04/15/2014
]]

--[[ Notice that the param "super" must be the class created by "class" method or a table with create methods
	such as class("clsSprite", { create = function(...) return cc.Sprite:create(...) end }) or
	class("clsGameSprite", clsSprite)
]]
function class(className, super)
	local cls = {}
	cls.__index = cls

	cls.className = className

	-- super class is created by this method
	if super.__ctype == 1 then
		-- inherit super class
		setmetatable(cls, super)
	else	-- super is a table with create methods
		-- indice this class is a cpp subclass
		cls.__ctype = 1
		-- to keep instances from gc
		cls.instanceList = {}

		-- constructor
		for name, ctor in pairs(super) do
			cls[name] = function(...)
				local args = {...}
				-- the first parameter is the instance itself.
				local self = args[1]
				-- the rest parameters are the real parameters.
				table.remove(args, 1)

				-- get cpp instance
				local cppInstance = ctor(unpack(args))
				table.insert(cls.instanceList, cppInstance)

				-- set the peertable of cpp instance to self (to storage user-defined methods)
				-- seems there are risks here, to be validated later.
				tolua.setpeer(cppInstance, self)

				return cppInstance
			end
		end
	end

	_G[className] = cls
end