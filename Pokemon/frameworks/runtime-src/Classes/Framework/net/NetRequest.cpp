#include "NetRequest.h"
#include <new>

using namespace std;

namespace framework
{
    NetRequest *NetRequest::create(const std::string &protocolId, const std::string &body)
    {
        auto pRequest = new (nothrow) NetRequest();
        if (pRequest && pRequest->init(protocolId, body))
        {
            pRequest->autorelease();
            return pRequest;
        }
        CC_SAFE_RELEASE(pRequest);
        return nullptr;
    }

    bool NetRequest::init(const std::string &protocolId, const std::string &body)
    {
        _protocolId = protocolId;
        _body = body;
    
        return true;
    }

    NetRequest::~NetRequest()
    {
    }
}