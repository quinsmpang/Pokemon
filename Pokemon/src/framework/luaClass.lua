--[[
	Description: to create a lua class
	Author: M.Wan
	Date: 04/13/2014
]]

function luaClass(className, super)
	local class = {}
	class.__index = class

	class.__className = className
	-- super class
	class.__super = super

	setmetatable(class, super)

	if not class.__super then
		-- to create object.
		function class:new()
			local instance = self:__ctor()
			log("luaclass new [" .. self.__className .. "]")
			return instance
		end

		-- real constructor, don't call this outside.
		function class:__ctor()
			local instance = nil
			if self.__super then
				-- only call the first super class constructor
				instance = self.__super:__ctor()
			else
				instance = {}
			end

			-- set template pointer
			setmetatable(instance, self)
			-- set class template
			instance.__class = self

			return instance
		end
	end

	_G[className] = class
end