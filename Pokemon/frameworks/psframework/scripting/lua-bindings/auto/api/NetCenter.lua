
--------------------------------
-- @module NetCenter
-- @extend Ref

--------------------------------
-- @function [parent=#NetCenter] addNetService 
-- @param self
-- @param #string str
-- @param #pf.NetService netservice
        
--------------------------------
-- @function [parent=#NetCenter] removeAllNetFilters 
-- @param self
        
--------------------------------
-- @function [parent=#NetCenter] addNetFilter 
-- @param self
-- @param #pf.NetFilter netfilter
        
--------------------------------
-- @function [parent=#NetCenter] removeNetProtocol 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#NetCenter] removeNetFilter 
-- @param self
-- @param #pf.NetFilter netfilter
        
--------------------------------
-- @function [parent=#NetCenter] removeNetService 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#NetCenter] sendMessage 
-- @param self
-- @param #pf.NetRequest netrequest
        
--------------------------------
-- overload function: addNetProtocol(pf.NetProtocol)
--          
-- overload function: addNetProtocol(string, string, pf.NetHandler)
--          
-- @function [parent=#NetCenter] addNetProtocol
-- @param self
-- @param #string str
-- @param #string str
-- @param #pf.NetHandler nethandler

--------------------------------
-- @function [parent=#NetCenter] dispatchFailedMessage 
-- @param self
-- @param #pf.NetResponse netresponse
        
--------------------------------
-- @function [parent=#NetCenter] dispatchSuccessfulMessage 
-- @param self
-- @param #pf.NetResponse netresponse
        
--------------------------------
-- @function [parent=#NetCenter] sendCommand 
-- @param self
-- @param #string str
-- @param #string str
-- @param #cc.Ref ref
        
--------------------------------
-- @function [parent=#NetCenter] getInstance 
-- @param self
-- @return NetCenter#NetCenter ret (return value: pf.NetCenter)
        
return nil
