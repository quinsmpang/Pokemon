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
        static NetProtocol *create(const std::string &protocolId, const std::string &serviceId, NetHandler *handler);
        
        bool init(const std::string &protocolId, const std::string &serviceId, NetHandler *handler);
        
        ~NetProtocol();
        
        inline const std::string &getProtocolId() const
        {
            return _protocolId;
        }
        
        inline const std::string &getServiceId() const
        {
            return _serviceId;
        }
        
        inline NetHandler *getRelatedHandler() const
        {
            return _handler;
        }
        
    private:
        std::string _protocolId;
        std::string _serviceId;
        NetHandler *_handler;
    };
}

#endif /* defined(__NET_NETPROTOCOL__) */
