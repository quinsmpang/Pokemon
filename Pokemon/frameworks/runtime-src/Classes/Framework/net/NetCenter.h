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
#include "../containers/Vector.h"
#include <string>

namespace framework
{
    class NetRequest;
    class NetResponse;
    class NetService;
    class NetHandler;
	class NetFilter;
    class NetProtocol;
    
    class NetCenter : public cocos2d::Ref
    {
        SINGLETON(NetCenter);
    public:
        ~NetCenter(); 
        
        void sendMessage(NetRequest *request);
		void sendCommand(const std::string &serviceId, const std::string &cmd, cocos2d::Ref *params);
        
        void dispatchSuccessfulMessage(NetResponse *response);
        void dispatchFailedMessage(NetResponse *response);
        
		// service manage
        void addNetService(const std::string &serviceId, NetService *service);
        void removeNetService(const std::string &serviceId);
        
		// protocol manage
        void addNetProtocol(const std::string &protocolId, const std::string &serviceId, NetHandler *handler);
        void addNetProtocol(NetProtocol *protocol);
        void removeNetProtocol(const std::string &protocolId);

		// filter manage
		void addNetFilter(NetFilter *filter);
		void removeNetFilter(NetFilter *filter);
		void removeAllNetFilters();
        
    private:
        Map *_services;
        Map *_protocols;
		Vector *_filters;
    };
}

#endif /* defined(__NET_NETCENTER__) */
