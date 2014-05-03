--[[
	Description: Internal objects extensions
	Author: M.Wan
	Date: 04/26/2014
]]

function MakeScriptHandler(target, selector, ...)
	local args = {...}
	return function(...)
		local internalArgs = {...}
		for _, v in pairs(args) do
			table.insert(internalArgs, v)
		end
		internalArgs.n = table.maxn(internalArgs)
		return selector(target, unpack(internalArgs))
	end
end

function CallFunctionAsync(target, selector, delay, ...)
	local args = {...}
	local handlerId = nil
	local handlerFunction = function()
		selector(target, unpack(args))
		cc.Director:getInstance():getScheduler():unscheduleScriptEntry(handlerId)
	end
	handlerId = cc.Director:getInstance():getScheduler():scheduleScriptFunc(handlerFunction, delay, false)
end

function fallInRandom(numerator, denominator)
	local randomNum = math.random(1, denominator)
	return randomNum <= numerator
end