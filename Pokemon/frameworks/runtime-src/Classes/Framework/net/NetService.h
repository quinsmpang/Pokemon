/******************************
 Description: Net service interface
 Author: M.Wan
 Date: 12/27/2014
 ******************************/

#ifndef __NET_NETSERVICE__
#define __NET_NETSERVICE__

#include "base/CCRef.h"
#include <string>

namespace framework
{
    class NetRequest;

    class NetService : public cocos2d::Ref
    {
    public:
        /**
         * NetService destructor.
         */
        virtual ~NetService() {}
    
		/**
         * Send request to the server.
         *
         * @param request The request to send.
         */
        virtual void sendMessage(NetRequest *request) = 0;

		/**
         * Execute extra command.
         *
         * @param cmd Command name.
         * @param params Command parameters.
         */
		virtual void executeCommand(const std::string &cmd, cocos2d::Ref *params) = 0;
    };
}

#endif /* defined(__NET_NETSERVICE__) */
