/******************************
 Description: Net management center
 Author: M.Wan
 Date: 12/27/2014
 ******************************/

#ifndef __NET_NETCENTER__
#define __NET_NETCENTER__

#include "cocos2d.h"
#include "../base/Macros.h"
#include "../containers/Map.h"
#include <string>

namespace framework
{
    class NetRequest;
    class NetResponse;
    class NetService;
    class NetHandler;
    class NetProtocol;
    
    class NetCenter : public cocos2d::Ref
    {
        SINGLETON(NetCenter);
    public:
        ~NetCenter();
        
        void sendMessage(NetRequest *request);
        
        void dispatchSuccessfulMessage(NetResponse *response);
        void dispatchFailedMessage(NetResponse *response);
        
        void addNetService(const std::string &serviceId, NetService *service);
        void removeNetService(const std::string &serviceId);
        
        void addNetProtocol(const std::string &protocolId, const std::string &serviceId, NetHandler *handler);
        void addNetProtocol(NetProtocol *protocol);
        void removeNetProtocol(const std::string &protocolId);
        
    private:
        Map *_services;
        Map *_protocols;
    };
}

#endif /* defined(__NET_NETCENTER__) */
