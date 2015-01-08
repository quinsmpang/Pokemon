/******************************
 Description: Net response base
 Author: M.Wan
 Date: 12/27/2014
 ******************************/

#ifndef __NET_NETRESPONSE__
#define __NET_NETRESPONSE__

#include "cocos2d.h"
#include <string>

namespace framework
{
    class NetRequest;

    class NetResponse : public cocos2d::Ref
    {
    public:
        /**
         * Create a new NetResponse.
         *
         * @param protocolId Protocol id.
         * @param body Response body.
         * @param request Related request.
         *
         * @return Return a new NetResponse object.
         */
        static NetResponse *create(const std::string &protocolId, const std::string &body, NetRequest *request);
    
        /**
         * NetResponse destructor.
         */
        virtual ~NetResponse();
    
        /**
         * Get response body.
         *
         * @return Response body.
         */
        inline const std::string &getBody() const
        {
            return _body;
        }
        /**
         * Set response body.
         *
         * @param body Response body.
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
    
        /**
         * Get related net request.
         *
         * @return Related net request.
         */
        inline NetRequest *getRelatedRequest() const
        {
            return _relatedRequest;
        }
    
    protected:
        virtual bool init(const std::string &protocolId, const std::string &body, NetRequest *request);
        
        std::string _protocolId;		// net response id
        std::string _body;				// net data package
        NetRequest *_relatedRequest;		// related request object
    };
}

#endif /* defined(__NET_NETRESPONSE__) */
