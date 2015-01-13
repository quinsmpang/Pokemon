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
#include "HttpTransferStrategy.h"
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
		explicit HttpService(const std::string &serviceAddress);
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
         * Get service address.
         */
        inline const std::string &getServiceAddress()
        {
            return _serviceAddr;
        }
        /**
         * Set service address.
         */
        inline void setServiceAddress(const std::string &serviceAddress)
        {
            _serviceAddr = serviceAddress;
        }

		/**
		* Set the rule of transfering.
		*
		* @param Transfer strategy.
		*/
		inline void setTransferRule(HttpTransferStrategy *strategy)
        {
            _strategy = strategy;
        }

	protected:
		bool init(const std::string &serviceAddress);

		HttpForm *createForm(const std::string &body);
		void onHttpRequestCompleted(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);

		std::string _serviceAddr;
        HttpTransferStrategy *_strategy;
	};
}

#endif