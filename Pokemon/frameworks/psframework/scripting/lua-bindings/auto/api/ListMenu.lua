
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
-- @function [parent=#ListMenu] getIndexInAllItems 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#ListMenu] getTopGlobalIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#ListMenu] setMenuEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ListMenu] getCurrentShowIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#ListMenu] isBottomOverflowed 
-- @param self
-- @return bool#bool ret (return value: bool)
        
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
-- @function [parent=#ListMenu] setEventsSwallowed 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ListMenu] isTopOverflowed 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ListMenu] reloadData 
-- @param self
        
--------------------------------
-- @function [parent=#ListMenu] select 
-- @param self
-- @param #int int
-- @param #int int
        
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
