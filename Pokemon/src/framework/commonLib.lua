--[[
	Description: Internal objects extensions
	Author: M.Wan
	Date: 04/26/2014
]]

-- return instance function pointer
function MakeScriptHandler(target, selector, ...)
	local args = {...}
	return function(...)
		-- the varadic params here are sent by the event automatically, append our own args after them.
		local internalArgs = {...}
		for _, arg in ipairs(args) do
			table.insert(internalArgs, arg)
		end
		return selector(target, unpack(internalArgs))
	end
end

-- call a function after delay
function CallFunctionAsync(target, selector, delay, ...)
	local args = {...}
	local handlerId = nil
	local handlerFunction = function()
		selector(target, unpack(args))
		cc.Director:getInstance():getScheduler():unscheduleScriptEntry(handlerId)
	end
	handlerId = cc.Director:getInstance():getScheduler():scheduleScriptFunc(handlerFunction, delay, false)
end

-- check whether fall in the random area, such as fallInRandom(3, 7) means whether it falls in 3/7.
function fallInRandom(numerator, denominator)
	local randomNum = math.random(1, denominator)
	return randomNum <= numerator
end

-- check whether a rect contains a point.
function containsPoint(rect, pos)
	return pos.x > rect.x and pos.x < rect.x + rect.width and pos.y > rect.y and pos.y < rect.y + rect.height
end