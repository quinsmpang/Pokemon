
--------------------------------
-- @module ListMenu
-- @extend Layer

--------------------------------
-- @function [parent=#ListMenu] dequeueItem 
-- @param self
-- @return ListMenuItem#ListMenuItem ret (return value: pf.ListMenuItem)
        
--------------------------------
-- @function [parent=#ListMenu] setResponseKeyCodes 
-- @param self
-- @param #int int
-- @param #int int
-- @param #int int
        
--------------------------------
-- @function [parent=#ListMenu] onKeyReleased 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#ListMenu] updateItemAtIndex 
-- @param self
-- @param #long long
        
--------------------------------
-- @function [parent=#ListMenu] initWithShowCount 
-- @param self
-- @param #long long
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ListMenu] setMenuEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ListMenu] getCurrentShowIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#ListMenu] insertItemAtIndex 
-- @param self
-- @param #long long
        
--------------------------------
-- @function [parent=#ListMenu] onKeyPressed 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#ListMenu] getItemAtIndex 
-- @param self
-- @param #long long
-- @return ListMenuItem#ListMenuItem ret (return value: pf.ListMenuItem)
        
--------------------------------
-- @function [parent=#ListMenu] isMenuEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ListMenu] removeItemAtIndex 
-- @param self
-- @param #long long
        
--------------------------------
-- @function [parent=#ListMenu] getTopGlobalIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#ListMenu] reloadData 
-- @param self
        
--------------------------------
-- overload function: create(pf.ListMenuDataSource, long)
--          
-- overload function: create(long)
--          
-- @function [parent=#ListMenu] create
-- @param self
-- @param #pf.ListMenuDataSource listmenudatasource
-- @param #long long
-- @return ListMenu#ListMenu ret (retunr value: pf.ListMenu)

--------------------------------
-- @function [parent=#ListMenu] onEnter 
-- @param self
        
--------------------------------
-- @function [parent=#ListMenu] onExit 
-- @param self
        
--------------------------------
-- @function [parent=#ListMenu] ListMenu 
-- @param self
        
return nil
