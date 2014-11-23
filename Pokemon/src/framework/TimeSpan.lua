--[[
	Description: Timespan to display time
	Author: M.Wan
	Date: 11/23/2014
]]

luaClass("TimeSpan")

TimeSpan.totalSeconds = nil
TimeSpan.hours = nil
TimeSpan.minutes = nil
TimeSpan.seconds = nil

function TimeSpan:create(totalSeconds)
	local ts = TimeSpan:new()
	ts:initWithSeconds(totalSeconds)
	return ts
end

function TimeSpan:initWithSeconds(totalSeconds)
	self:setTotalSeconds(totalSeconds)
end

function TimeSpan:getTotalSeconds()
	return self.totalSeconds
end

function TimeSpan:setTotalSeconds(totalSeconds)
	self.totalSeconds = totalSeconds

	self.hours = math.floor(totalSeconds / 3600)
	self.minutes = math.floor(totalSeconds % 3600 / 60)
	self.seconds = totalSeconds % 60
end

function TimeSpan:toString()
	return string.format("%02d:%02d:%02d", self.hours, self.minutes, self.seconds)
end