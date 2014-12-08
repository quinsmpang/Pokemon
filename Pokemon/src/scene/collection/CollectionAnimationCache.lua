--[[
	Description: Collection resource cache
	Author: M.Wan
	Date: 12/9/2014
]]

CollectionAnimationCache = {}

CollectionAnimationCache.animationCache = {}		-- 方便搜索用哈希存储
CollectionAnimationCache.keys = QueueLua:new()	-- 记录key值的顺序, 为了能有序的维护

CollectionAnimationCache.STORAGE = 50		-- 最多缓存50个

function CollectionAnimationCache:cache(key, animation)
	if not self.animationCache[key] then
		animation:retain()
		self.animationCache[key] = animation
		self.keys:enqueue(key)
		if self.keys:count() > self.STORAGE then
			local oldest = self.keys:front()
			self.animationCache[oldest]:release()
			self.animationCache[oldest] = nil
			self.keys:dequeue()
		end
	end
end

function CollectionAnimationCache:purge()
	for k, v in pairs(self.animationCache) do
		v:release()
	end
	self.animationCache = {}
	self.keys = QueueLua:new()
	collectgarbage()	-- gc
end