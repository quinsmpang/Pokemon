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
        /**
         * Create a NetFileter object.
         */
		CREATE_FUNC(NetFilter);

        /**
         * NetFilter destructor.
         */
		virtual ~NetFilter();

        /**
         * Filter the successful response message.
         *
         * @param response Target response object.
         */
		virtual void filterSuccessfulMessage(NetResponse *response);
        /**
         * Filter the failed response message.
         *
         * @param response Target response object.
         */
		virtual void filterFailedMessage(NetResponse *response);
        
    protected:
		virtual bool init();
	};
}

#endif