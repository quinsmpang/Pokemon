/******************************
Description: Http service.
Author: M.Wan
Date: 01/09/2015
******************************/

#ifndef __HTTP_HTTPSERVICE__
#define __HTTP_HTTPSERVICE__

#include "cocos2d.h"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "../net/NetService.h"
#include "../net/NetTransferStrategy.h"
#include <string>

namespace framework
{
	class NetRequest;
	class HttpForm;

	class HttpService : public NetService
	{
	public:
		/**
		* Create HttpService with specified service address.
		*/
		static HttpService *create(const std::string &serviceAddress);

		/**
		* HttpService constructor.
		*/
		explicit HttpService();
		/**
		* HttpService destructor.
		*/
		virtual ~HttpService();

		/**
		* NetService overrides.
		*/
		virtual void sendMessage(NetRequest *request);
		virtual void executeCommand(const std::string &cmd, cocos2d::Ref *param);

		/**
		* Set the rule of transfer in request.
		*
		* @param Transfer strategy.
		*/
		inline void setRequestTransferRule(NetTransferStrategy *strategy);

	protected:
		bool init(const std::string &serviceAddress);

		HttpForm *createForm(const std::string &body);
		void onHttpRequestCompleted(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);

		std::string _serviceAddr;
		NetTransferStrategy *_requestStrategy;
	};
}

#endif