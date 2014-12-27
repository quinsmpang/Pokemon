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
        static NetRequest *create(const std::string &protocolId, const std::string &body);
    
        virtual bool init(const std::string &protocolId, const std::string &body);
    
        virtual ~NetRequest();
    
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
    
    protected:
        std::string _body;
        std::string _protocolId;
    };
}

#endif /* defined(__NET_NETREQUEST__) */
