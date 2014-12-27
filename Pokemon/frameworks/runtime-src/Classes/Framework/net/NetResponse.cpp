#include "NetResponse.h"
#include "NetRequest.h"
#include <new>

using namespace std;

namespace framework
{
    NetResponse *NetResponse::create(const std::string &protocolId, const std::string &body, NetRequest *request)
    {
        auto pResponse = new (nothrow) NetResponse();
        if (pResponse && pResponse->init(protocolId, body, request))
        {
            pResponse->autorelease();
            return pResponse;
        }
        CC_SAFE_RELEASE(pResponse);
        return nullptr;
    }

    bool NetResponse::init(const std::string &protocolId, const std::string &body, NetRequest *request)
    {
        _protocolId = protocolId;
        _body = body;
        _relatedRequest = request;
        request->retain();
        
        return true;
    }

    NetResponse::~NetResponse()
    {
        CC_SAFE_RELEASE(_relatedRequest);
    }
}