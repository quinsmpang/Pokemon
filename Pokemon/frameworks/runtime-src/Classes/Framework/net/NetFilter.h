/******************************
Description: Net filter
Author: M.Wan
Date: 12/27/2014
******************************/

#ifndef __NET_NETFILTER__
#define __NET_NETFILTER__

#include "cocos2d.h"

namespace framework
{
	class NetResponse;

	class NetFilter : public cocos2d::Ref
	{
	public:
		CREATE_FUNC(NetFilter);

		virtual bool init();

		virtual ~NetFilter();

		virtual NetResponse *filterSuccessfulMessage(NetResponse *response);
		virtual NetResponse *filterFailedMessage(NetResponse *response);
	};
}

#endif