/******************************
 Description: Net request base
 Author: M.Wan
 Date: 12/27/2014
 ******************************/

#ifndef __NET_NETREQUEST__
#define __NET_NETREQUEST__

#include "cocos2d.h"
#include <string>

namespace framework
{
    class NetRequest : public cocos2d::Ref
    {
    public:
        /**
         * Create a new NetRequest.
         *
         * @param protocolId Protocol id.
         * @param body Request body.
         *
         * @return Return a new NetRequest object.
         */
        static NetRequest *create(const std::string &protocolId, const std::string &body);
        
        /**
         * NetRequest destructor.
         */
        virtual ~NetRequest();
    
        /**
         * Get request body.
         *
         * @return Request body.
         */
        inline const std::string &getBody() const
        {
            return _body;
        }
        /**
         * Set request body.
         *
         * @param body Request body.
         */
        inline void setBody(const std::string &body)
        {
            _body = body;
        }
    
        /**
         * Get protocol id.
         *
         * @return Protocol id.
         */
        inline const std::string &getProtocolId() const
        {
            return _protocolId;
        }
        /**
         * Set protocol id.
         *
         * @param protocolId Protocol id.
         */
        inline void setProtocolId(const std::string &protocolId)
        {
            _protocolId = protocolId;
        }
    
    protected:
        virtual bool init(const std::string &protocolId, const std::string &body);
        
        std::string _body;				// net data package
        std::string _protocolId;		// net protocol id
    };
}

#endif /* defined(__NET_NETREQUEST__) */
