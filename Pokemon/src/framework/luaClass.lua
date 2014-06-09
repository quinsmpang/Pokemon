--[[
	Description: to create a lua class
	Author: M.Wan
	Date: 04/13/2014
]]

function luaClass(className, super)
	local class = {}
	class.__index = class

	class.className = className
	-- super class
	class.super = super

	setmetatable(class, super)

	if not class.super then
		-- to create object.
		function class:new()
			local instance = self:__ctor()
			log("luaclass new [" .. self.className .. "]")
			return instance
		end

		-- real constructor, don't call this outside.
		function class:__ctor()
			local instance = nil
			if self.super then
				-- only call the first super class constructor
				instance = self.super:__ctor()
			else
				instance = {}
			end

			setmetatable(instance, self)
			-- set template pointer
			instance.class = self
			-- set class template
			instance:init()

			return instance
		end
	end

	-- You can override this method to initialize.
	function class:init()
	end

	_G[className] = class
end