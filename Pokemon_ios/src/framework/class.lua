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

	cls.__className = className

	-- super class is created by this method
	if super.__ctype == 1 then
		-- inherit super class
		setmetatable(cls, super)
	else	-- super is a table with create methods
		-- indice this class is a cpp subclass
		cls.__ctype = 1
		-- keep instances
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
				local peertable = {}
				setmetatable(peertable, self)

				tolua.setpeer(cppInstance, peertable)

				return cppInstance
			end
		end

		-- invoke origin methods of the cpp class
		function cls:callOrigin(functionName, ...)
			-- get peertable of the instance
			local peertable = tolua.getpeer(self)

			-- clear the peertable so that the instance could invoke the origin functions.
			tolua.setpeer(self, nil)

			-- invoke origin function
			self[functionName](self, unpack{...})

			-- restore the peertable
			tolua.setpeer(self, peertable)
		end
	end

	_G[className] = cls
end