--[[
	Description: to create a lua class
	Author: M.Wan
	Date: 04/13/2014
]]

function luaClass(className, ...)
	local class = {}
	class.__index = class

	class.className = className
	class.super = {...}

	-- support multiple inheritance
	setmetatable(class, {__index = function (_, key)
		for i = 1, #class.super do
			local value = class.super[i][key]
			if value then
				return value
			end
		end
		return nil
	end})

	if #class.super <= 0 then
		-- to create object.
		function class:new()
			local instance = self:__ctor()
			log("luaclass new [" .. self.className .. "]")
			return instance
		end

		-- real constructor, don't call this outside.
		function class:__ctor()
			local instance = nil
			if #class.super > 0 then
				-- only call the first super class constructor
				instance = class.super[1]:__ctor()
			else
				instance = {}
			end

			setmetatable(instance, class)
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