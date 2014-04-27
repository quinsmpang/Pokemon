
--------------------------------
-- @module MaskLayer
-- @extend LayerColor,MaskLayerDelegate

--------------------------------
-- @function [parent=#MaskLayer] onEventPenetrated 
-- @param self
-- @param #float float
-- @param #float float
        
--------------------------------
-- @function [parent=#MaskLayer] setArea 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#MaskLayer] setColor 
-- @param self
-- @param #color3B_table color3b
        
--------------------------------
-- @function [parent=#MaskLayer] getArea 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#MaskLayer] setOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#MaskLayer] isInterceptAllEvents 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#MaskLayer] forceInterceptAllEvents 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#MaskLayer] onEventIntercepted 
-- @param self
-- @param #float float
-- @param #float float
        
--------------------------------
-- overload function: create(rect_table)
--          
-- overload function: create()
--          
-- @function [parent=#MaskLayer] create
-- @param self
-- @param #rect_table rect
-- @return MaskLayer#MaskLayer ret (retunr value: pf.MaskLayer)

--------------------------------
-- @function [parent=#MaskLayer] onTouchMoved 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#MaskLayer] onTouchEnded 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#MaskLayer] onTouchCancelled 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#MaskLayer] onTouchBegan 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#MaskLayer] MaskLayer 
-- @param self
        
return nil
