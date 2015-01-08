/******************************
 Description: Net protocol
 Author: M.Wan
 Date: 12/27/2014
 ******************************/

#ifndef __NET_NETPROTOCOL__
#define __NET_NETPROTOCOL__

#include "base/CCRef.h"
#include "../base/Uninheritable.h"
#include <string>

namespace framework
{
    class NetHandler;
    
    class NetProtocol : public cocos2d::Ref, public Uninheritable<NetProtocol>
    {
    public:
        /**
         * Create a new NetProtocol.
         *
         * @param protocolId Specified protocol id.
         * @param serviceId Specified service id.
         * @param handler Related net handler.
         *
         * @return Return a new NetProtocol.
         */
        static NetProtocol *create(const std::string &protocolId, const std::string &serviceId, NetHandler *handler);
        
        /**
         * NetProtocol destructor.
         */
        ~NetProtocol();
        
        /**
         * Get protocol id.
         *
         * @return Protocol id.
         */
        inline const std::string &getProtocolId() const
        {
            return _protocolId;
        }
        /**
         * Get service id.
         *
         * @return Service id.
         */
        inline const std::string &getServiceId() const
        {
            return _serviceId;
        }
        
        /**
         * Get related net handler.
         *
         * @return Related net handler.
         */
        inline NetHandler *getRelatedHandler() const
        {
            return _handler;
        }
        
    private:
        bool init(const std::string &protocolId, const std::string &serviceId, NetHandler *handler);
        
        std::string _protocolId;
        std::string _serviceId;
        NetHandler *_handler;
    };
}

#endif /* defined(__NET_NETPROTOCOL__) */
