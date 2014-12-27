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
        static NetResponse *create(const std::string &protocolId, const std::string &body, NetRequest *request);
    
        virtual bool init(const std::string &protocolId, const std::string &body, NetRequest *request);
    
        virtual ~NetResponse();
    
        inline const std::string &getBody() const
        {
            return _body;
        }
        inline void setBody(const std::string &body)
        {
            _body = body;
        }
    
        inline const std::string &getProtocolId() const
        {
            return _protocolId;
        }
        inline void setProtocolId(const std::string &protocolId)
        {
            _protocolId = protocolId;
        }
    
        inline NetRequest *getRelatedRequest() const
        {
            return _relatedRequest;
        }
    
    protected:
        std::string _protocolId;		// net response id
        std::string _body;				// net data package
        NetRequest *_relatedRequest;		// related request object
    };
}

#endif /* defined(__NET_NETRESPONSE__) */
