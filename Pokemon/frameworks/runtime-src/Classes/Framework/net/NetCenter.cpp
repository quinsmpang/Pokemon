#include "NetCenter.h"
#include "NetRequest.h"
#include "NetResponse.h"
#include "NetService.h"
#include "NetHandler.h"
#include "NetFilter.h"
#include "NetProtocol.h"

using namespace std;
using namespace cocos2d;

namespace framework
{
	NetCenter::NetCenter()
		: _services(new Map())
		, _protocols(new Map())
		, _filters(new Vector())
	{
	}

	NetCenter::~NetCenter()
	{
		CC_SAFE_DELETE(_services);
		CC_SAFE_DELETE(_protocols);
		CC_SAFE_DELETE(_filters);
	}

	void NetCenter::sendMessage(framework::NetRequest *request)
	{
		string protocolId = request->getProtocolId();
		NetProtocol *pProtocol = (NetProtocol*)_protocols->objectForKey(protocolId);
		CCASSERT(pProtocol, "unknown protocol");
		NetService *pService = (NetService*)_services->objectForKey(pProtocol->getServiceId());
		CCASSERT(pService, "unknown service");
		pService->sendMessage(request);
	}

	void NetCenter::sendCommand(const std::string &serviceId, const std::string &cmd, cocos2d::Ref *params)
	{
		NetService *pService = (NetService*)_services->objectForKey(serviceId);
		if (pService)
		{
			pService->executeCommand(cmd, params);
		}
		else
		{
			CCLOG("The service [%s] doesn't exist.", serviceId.c_str());
		}
	}

	void NetCenter::dispatchSuccessfulMessage(framework::NetResponse *response)
	{
		CCASSERT(response, "Invalid response to dispatch");
		string protocolId = response->getProtocolId();
		NetProtocol *pProtocol = (NetProtocol*)_protocols->objectForKey(protocolId);
		if (!pProtocol)
		{
			CCLOG("Unknown protocol");
			return;
		}
		// filter first
		NetFilter *pFilter = nullptr;
		for (int i = 0; i < _filters->getLength(); ++i)
		{
			pFilter = (NetFilter*)_filters->objectAt(i);
			response = pFilter->filterSuccessfulMessage(response);
		}
		// handle the response
		NetHandler *pHandler = (NetHandler*)pProtocol->getRelatedHandler();
		CCASSERT(pHandler, "The protocol must have a handler to handle the response.");
		pHandler->handleSuccessfulMessage(response);
	}

	void NetCenter::dispatchFailedMessage(framework::NetResponse *response)
	{
		CCASSERT(response, "Invalid response to dispatch");
		string protocolId = response->getProtocolId();
		NetProtocol *pProtocol = (NetProtocol*)_protocols->objectForKey(protocolId);
		if (!pProtocol)
		{
			CCLOG("Unknown protocol");
			return;
		}
		// filter first
		NetFilter *pFilter = nullptr;
		for (int i = 0; i < _filters->getLength(); ++i)
		{
			pFilter = (NetFilter*)_filters->objectAt(i);
			response = pFilter->filterFailedMessage(response);
		}
		// handle the response
		NetHandler *pHandler = (NetHandler*)pProtocol->getRelatedHandler();
		CCASSERT(pHandler, "The protocol must have a handler to handle the response.");
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

	void NetCenter::addNetFilter(NetFilter *filter)
	{
		_filters->addObject(filter);
	}

	void NetCenter::removeNetFilter(NetFilter *filter)
	{
		_filters->removeObject(filter);
	}

	void NetCenter::removeAllNetFilters()
	{
		_filters->clear();
	}
}