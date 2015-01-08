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
        /**
         * NetCenter is a singleton.
         */
        SINGLETON(NetCenter);
    public:
        /**
         * NetCenter destructor.
         */
        ~NetCenter(); 
        
        /**
         * Send request to the server.
         *
         * @param request The request to send.
         */
        void sendMessage(NetRequest *request);
        /**
         * Execute specified command.
         *
         * @param serviceId The related service id.
         * @param cmd Command name.
         * @param params Command parameters.
         */
		void sendCommand(const std::string &serviceId, const std::string &cmd, cocos2d::Ref *params);
        
        /**
         * Dispatch the successful response.
         *
         * @param response Returned response from the server.
         */
        void dispatchSuccessfulMessage(NetResponse *response);
        /**
         * Dispatch the failed response.
         *
         * @param response Returned response from the server.
         */
        void dispatchFailedMessage(NetResponse *response);
        
		/**
         * Add a new net service.
         *
         * @param serviceId Service id to add.
         * @param service Service object.
         */
        void addNetService(const std::string &serviceId, NetService *service);
        /**
         * Remove net service.
         *
         * @param serviceId Service id to remove.
         */
        void removeNetService(const std::string &serviceId);
        
		/**
         * Add a new net protocol.
         *
         * @param protocolId Protocol id.
         * @param serviceId Which service id to add.
         * @param handler Related net handler.
         */
        void addNetProtocol(const std::string &protocolId, const std::string &serviceId, NetHandler *handler);
        /**
         * Add a new net protocol.
         *
         * @param protocol Protocol object.
         */
        void addNetProtocol(NetProtocol *protocol);
        /**
         * Remove the specified protocol.
         *
         * @param protocolId Protocol id to remove.
         */
        void removeNetProtocol(const std::string &protocolId);

		/**
         * Add a new net filter.
         *
         * @param filter Filter to add.
         */
		void addNetFilter(NetFilter *filter);
        /**
         * Remove net filter.
         *
         * @param filter Filter to remove.
         */
		void removeNetFilter(NetFilter *filter);
        /**
         * Remove all filters.
         */
		void removeAllNetFilters();
        
    private:
        Map *_services;
        Map *_protocols;
		Vector *_filters;
    };
}

#endif /* defined(__NET_NETCENTER__) */
