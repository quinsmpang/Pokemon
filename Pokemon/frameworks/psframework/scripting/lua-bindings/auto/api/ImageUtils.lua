
--------------------------------
-- @module ImageUtils
-- @extend Ref

--------------------------------
-- @function [parent=#ImageUtils] createAnimationByGifImage 
-- @param self
-- @param #string str
-- @param #float float
-- @return Animate#Animate ret (return value: cc.Animate)
        
--------------------------------
-- @function [parent=#ImageUtils] createSpriteWithBinaryData 
-- @param self
-- @param #pf.BinaryData binarydata
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- overload function: getGifFrames(pf.BinaryData)
--          
-- overload function: getGifFrames(string)
--          
-- @function [parent=#ImageUtils] getGifFrames
-- @param self
-- @param #string str
-- @return Vector#Vector ret (retunr value: pf.Vector)

--------------------------------
-- @function [parent=#ImageUtils] createAnimationByFrames 
-- @param self
-- @param #pf.Vector array
-- @param #float float
-- @return Animate#Animate ret (return value: cc.Animate)
        
--------------------------------
-- @function [parent=#ImageUtils] createSpriteFrameWithBinaryData 
-- @param self
-- @param #pf.BinaryData binarydata
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)
        
--------------------------------
-- @function [parent=#ImageUtils] getInstance 
-- @param self
-- @return ImageUtils#ImageUtils ret (return value: pf.ImageUtils)
        
return nil
