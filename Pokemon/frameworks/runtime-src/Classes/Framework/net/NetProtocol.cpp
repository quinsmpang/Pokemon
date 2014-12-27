#include "NetProtocol.h"
#include "NetHandler.h"
#include <new>

using namespace std;

namespace framework
{
    NetProtocol *NetProtocol::create(const std::string &protocolId, const std::string &serviceId, NetHandler *handler)
    {
        auto pProtocol = new (nothrow) NetProtocol();
        if (pProtocol && pProtocol->init(protocolId, serviceId, handler))
        {
            pProtocol->autorelease();
            return pProtocol;
        }
        CC_SAFE_RELEASE(pProtocol);
        return nullptr;
    }
    
    bool NetProtocol::init(const std::string &protocolId, const std::string &serviceId, NetHandler *handler)
    {
        _protocolId = protocolId;
        _serviceId = serviceId;
        _handler = handler;
        handler->retain();
        
        return true;
    }
    
    NetProtocol::~NetProtocol()
    {
        CC_SAFE_RELEASE(_handler);
    }
}