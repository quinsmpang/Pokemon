/******************************
 Description: Net service interface
 Author: M.Wan
 Date: 12/27/2014
 ******************************/

#ifndef __NET_NETSERVICE__
#define __NET_NETSERVICE__

#include "base/CCRef.h"

namespace framework
{
    class NetRequest;

    class NetService : public cocos2d::Ref
    {
    public:
        virtual ~NetService() {}
    
        virtual void sendMessage(NetRequest *request) = 0;
    };
}

#endif /* defined(__NET_NETSERVICE__) */
