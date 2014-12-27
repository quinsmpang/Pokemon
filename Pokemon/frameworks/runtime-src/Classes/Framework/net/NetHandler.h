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
	    CREATE_FUNC(NetHandler);
	    
	    virtual bool init();
	    
	    virtual ~NetHandler();
	    
	    virtual void handleSuccessfulMessage(NetResponse *response);
	    virtual void handleFailedMessage(NetResponse *response);
	};
}

#endif /* defined(__NET_NETHANDLER__) */
