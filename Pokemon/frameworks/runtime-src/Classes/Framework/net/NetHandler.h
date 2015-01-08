/******************************
 Description: Net handler
 Author: M.Wan
 Date: 12/27/2014
 ******************************/

#ifndef __NET_NETHANDLER__
#define __NET_NETHANDLER__

#include "base/CCRef.h"

namespace framework
{
    class NetResponse;
    
	class NetHandler : public cocos2d::Ref
	{
	public:
        /**
         * Create a new NetHandler.
         */
	    CREATE_FUNC(NetHandler);
        
        /**
         * NetHandler destructor.
         */
	    virtual ~NetHandler();
	    
        /**
         * How to handle successful message.
         *
         * @param response The response to handle.
         */
	    virtual void handleSuccessfulMessage(NetResponse *response);
        /**
         * How to handle failed message.
         *
         * @param response The response to handle.
         */
	    virtual void handleFailedMessage(NetResponse *response);
        
    protected:
	    virtual bool init();
	};
}

#endif /* defined(__NET_NETHANDLER__) */
