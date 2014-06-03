
--------------------------------
-- @module SqliteDb
-- @extend Ref

--------------------------------
-- overload function: updateTable(string, pf.Map, string, string)
--          
-- overload function: updateTable(string, pf.Map, pf.Map)
--          
-- @function [parent=#SqliteDb] updateTable
-- @param self
-- @param #string str
-- @param #pf.Map map
-- @param #string str
-- @param #string str
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#SqliteDb] dropTable 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SqliteDb] clearTable 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- overload function: deleteFromTable(string, string, string)
--          
-- overload function: deleteFromTable(string, pf.Map)
--          
-- @function [parent=#SqliteDb] deleteFromTable
-- @param self
-- @param #string str
-- @param #string str
-- @param #string str
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#SqliteDb] insertTable 
-- @param self
-- @param #string str
-- @param #pf.Map map
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SqliteDb] createTable 
-- @param self
-- @param #string str
-- @param #pf.Vector array
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SqliteDb] getRecordCount 
-- @param self
-- @param #string str
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#SqliteDb] getValueTypeName 
-- @param self
-- @param #cc.Ref ref
-- @return char#char ret (return value: char)
        
--------------------------------
-- overload function: selectTable(string, string, string)
--          
-- overload function: selectTable(string, pf.Map)
--          
-- overload function: selectTable(string, string, pf.Vector)
--          
-- overload function: selectTable(string, string)
--          
-- @function [parent=#SqliteDb] selectTable
-- @param self
-- @param #string str
-- @param #string str
-- @param #pf.Vector array
-- @return Vector#Vector ret (retunr value: pf.Vector)

--------------------------------
-- @function [parent=#SqliteDb] openSqlite 
-- @param self
-- @param #string str
-- @return SqliteDb#SqliteDb ret (return value: pf.SqliteDb)
        
--------------------------------
-- @function [parent=#SqliteDb] clearConnectionCache 
-- @param self
        
return nil
