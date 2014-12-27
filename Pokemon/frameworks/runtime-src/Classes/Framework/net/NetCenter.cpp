#include "NetCenter.h"
#include "NetRequest.h"
#include "NetResponse.h"
#include "NetService.h"
#include "NetHandler.h"
#include "NetProtocol.h"

using namespace std;
using namespace cocos2d;

namespace framework
{
    NetCenter::NetCenter()
    : _services(new Map())
    , _protocols(new Map())
    {
    }
    
    NetCenter::~NetCenter()
    {
        CC_SAFE_DELETE(_services);
        CC_SAFE_DELETE(_protocols);
    }
    
    void NetCenter::sendMessage(framework::NetRequest *request)
    {
        string protocolId = request->getProtocolId();
        NetProtocol *pProtocol = (NetProtocol*)_protocols->objectForKey(protocolId);
        NetService *pService = (NetService*)_services->objectForKey(pProtocol->getServiceId());
        pService->sendMessage(request);
    }
    
    void NetCenter::dispatchSuccessfulMessage(framework::NetResponse *response)
    {
        string protocolId = response->getProtocolId();
        NetProtocol *pProtocol = (NetProtocol*)_protocols->objectForKey(protocolId);
        NetHandler *pHandler = (NetHandler*)pProtocol->getRelatedHandler();
        pHandler->handleSuccessfulMessage(response);
    }
    
    void NetCenter::dispatchFailedMessage(framework::NetResponse *response)
    {
        string protocolId = response->getProtocolId();
        NetProtocol *pProtocol = (NetProtocol*)_protocols->objectForKey(protocolId);
        NetHandler *pHandler = (NetHandler*)pProtocol->getRelatedHandler();
        pHandler->handleFailedMessage(response);
    }
    
    void NetCenter::addNetService(const std::string &serviceId, framework::NetService *service)
    {
        _services->setObjectForKey(service, serviceId);
    }
    
    void NetCenter::removeNetService(const std::string &serviceId)
    {
        _services->removeObjectForKey(serviceId);
    }
    
    void NetCenter::addNetProtocol(const std::string &protocolId, const std::string &serviceId, framework::NetHandler *handler)
    {
        auto pProtocol = NetProtocol::create(protocolId, serviceId, handler);
        this->addNetProtocol(pProtocol);
    }
    
    void NetCenter::addNetProtocol(framework::NetProtocol *protocol)
    {
        _protocols->setObjectForKey(protocol, protocol->getProtocolId());
    }
    
    void NetCenter::removeNetProtocol(const std::string &protocolId)
    {
        _protocols->removeObjectForKey(protocolId);
    }
}