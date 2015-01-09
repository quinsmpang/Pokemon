#include "HttpService.h"
#include "HttpRequest.h"
#include "HttpForm.h"
#include "../net/NetRequest.h"
#include "../net/NetResponse.h"
#include "../net/NetCenter.h"
#include "../net/NetTransferStrategy.h"
#include <new>
#include <vector>

using namespace cocos2d;
using namespace cocos2d::network;
using namespace std;

namespace framework
{
	HttpService *HttpService::create(const std::string &serviceAddress)
	{
		auto pService = new (nothrow)HttpService();
		if (pService && pService->init(serviceAddress))
		{
			pService->autorelease();
			return pService;
		}
		CC_SAFE_RELEASE(pService);
		return nullptr;
	}

	bool HttpService::init(const std::string &serviceAddress)
	{
		_serviceAddr = serviceAddress;

		return true;
	}

	HttpService::HttpService()
		: _serviceAddr()
		, _requestStrategy(nullptr)
		, _responseStrategy(nullptr)
	{
	}

	HttpService::~HttpService()
	{
		if (_requestStrategy)
		{
			delete _requestStrategy;
		}
		if (_responseStrategy)
		{
			delete _responseStrategy;
		}
	}

	void HttpService::sendMessage(NetRequest *request)
	{
		std::string body = request->getBody();
		auto pHttpRequest = new HttpRequest();
		// save user data
		pHttpRequest->setUserData(request);
		// need retain
		request->retain();
		pHttpRequest->setRequestType(HttpRequest::Type::GET);
		HttpForm *pForm = nullptr;
		// get parameters through the strategy.
		if (_requestStrategy)
		{
			pForm = this->createForm(body);
		}
		else
		{
			CCLOG("You can't send the message if you don't set the transfer rule.");
			return;
		}

		if (!pForm)
		{
			CCLOG("Invalid http form.");
			return;
		}
		string url = _serviceAddr;
		string formStr = pForm->toString();
		if (formStr.size() > 0)
		{
			url.append("?").append(formStr);
		}
		pHttpRequest->setUrl(url.c_str());
		CCLOG("HttpService sent: %s", pHttpRequest->getUrl());
		// set callback
		pHttpRequest->setResponseCallback(this, httpresponse_selector(HttpService::onHttpRequestCompleted));
		HttpClient::getInstance()->send(pHttpRequest);
		pHttpRequest->release();
	}

	void HttpService::executeCommand(const std::string &cmd, cocos2d::Ref *param)
	{
		// Add user commands here.
	}

	void HttpService::onHttpRequestCompleted(HttpClient *client, HttpResponse *response)
	{
		HttpRequest *pRelatedRequest = response->getHttpRequest();
		NetRequest *pUserRequest = (NetRequest*)pRelatedRequest->getUserData();
		if (!response->isSucceed())
		{
			CCLOG("Response failed. Error: %s", response->getErrorBuffer());
			auto pResponse = NetResponse::create(pUserRequest->getProtocolId(), response->getErrorBuffer(), pUserRequest);
			NetCenter::getInstance()->dispatchFailedMessage(pResponse);
			// retained once when sending request, so release it here.
			pUserRequest->release();
			return;
		}
		// retrieve response data.
		vector<char> *buffer = response->getResponseData();
		string responseBody;
		responseBody.assign(buffer->begin(), buffer->end());
		// decode unicode todo

		CCLOG("Response successful. Data: %s", responseBody);
		// create net response
		auto pResponse = NetResponse::create(pUserRequest->getProtocolId(), responseBody, pUserRequest);
		NetCenter::getInstance()->dispatchSuccessfulMessage(pResponse);
		// retained once when sending request, so release it here.
		pUserRequest->release();
	}

	HttpForm *HttpService::createForm(const std::string &body)
	{
		CCASSERT(_requestStrategy, "A request rule is required!");
		void *pMsg = _requestStrategy->toTransferData(body);
		// distinguish different format type and handle with them. Add params to the form.
		HttpForm *pForm = HttpForm::create();
		auto transferType = _requestStrategy->getTransferType();
		if (transferType == NetTransferType::JSON)
		{
		}
		else if (transferType == NetTransferType::XML)
		{
		}
		else if (transferType == NetTransferType::PROTOBUF)
		{
		}
		else
		{
			// what's the rule you don't know about?
			pForm = nullptr;
		}

		return pForm;
	}
}