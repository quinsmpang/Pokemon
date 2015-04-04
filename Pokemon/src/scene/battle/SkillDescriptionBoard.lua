--[[
	Description: Skill description board
	Author: M.Wan
	Date: 4/5/2015
]]

class("SkillDescriptionBoard", psNode)

SkillDescriptionBoard.skillData = nil

SkillDescriptionBoard.lblPP = nil
SkillDescriptionBoard.lblProperty = nil

SkillDescriptionBoard.LABEL_SIZE = 18
SkillDescriptionBoard.LABEL_COLOR = ccc3(0, 0, 0)

SkillDescriptionBoard.__create = psNode.create

local winSize = cc.Director:getInstance():getWinSize()

function SkillDescriptionBoard:create(skillData)
	local ret = SkillDescriptionBoard:__create()
	ret:init(skillData)
	return ret
end

function SkillDescriptionBoard:init(skillData)
	self.skillData = skillData
	local skillId = self.skillData[1]
	local skillPP = self.skillData[2]
	local skillUpValue = self.skillData[3]
	local skillModel = SkillInfo:create(skillId)

	local capInsets = CCRectMake(20, 20, 60, 60)
	local bg = cc.Scale9Sprite:createWithSpriteFrameName("images/common/border_aqua.png", capInsets)
	bg:setPreferredSize(CCSizeMake(winSize.width * 0.2, winSize.height * 0.21))
	bg:setPosition(bg:getContentSize().width * 0.5, bg:getContentSize().height * 0.5)
	self:addChild(bg)
	self:setContentSize(bg:getContentSize())
	self:setAnchorPoint(0.5, 0.5)

	self.lblPP = self:_createLabel()
	self.lblPP:setString(string.format("PP %d / %d", skillPP, skillModel.pp * (1 + skillUpValue * 0.2)))
	self.lblPP:setPosition(bg:getContentSize().width * 0.5, bg:getContentSize().height * 0.7)
	bg:addChild(self.lblPP)

	self.lblProperty = self:_createLabel()
	self.lblProperty:setString(string.format("属性 / %s", Enumerations.PROPERTY_STRING[skillModel.property]))
	self.lblProperty:setPosition(bg:getContentSize().width * 0.5, bg:getContentSize().height * 0.3)
	bg:addChild(self.lblProperty)
end

function SkillDescriptionBoard:update(skillData)
	self.skillData = skillData
	local skillId = self.skillData[1]
	local skillPP = self.skillData[2]
	local skillUpValue = self.skillData[3]
	local skillModel = SkillInfo:create(skillId)

	self.lblPP:setString(string.format("PP %d / %d", skillPP, skillModel.pp * (1 + skillUpValue * 0.2)))
	self.lblProperty:setString(string.format("属性 / %s", Enumerations.PROPERTY_STRING[skillModel.property]))
end

function SkillDescriptionBoard:_createLabel()
	local lbl = cc.Label:createWithTTF("", GameConfig.DEFAULT_FONT_PATH, self.LABEL_SIZE)
	lbl:setColor(self.LABEL_COLOR)
	return lbl
end