#include "NetHandler.h"
#include "NetResponse.h"
#include "../lua/LuaUtils.h"

using namespace cocos2d;

namespace framework
{
    bool NetHandler::init()
    {
        return true;
    }

    NetHandler::~NetHandler()
    {
    }

    void NetHandler::handleSuccessfulMessage(NetResponse *response)
    {
    #if CC_ENABLE_SCRIPT_BINDING
        Vector<Ref*> params;
        params.pushBack(response);
        Vector<Ref*> paramTypes;
        paramTypes.pushBack(__String::create("pf.NetHandler"));
        
        LuaUtils::getInstance()->executePeertableFunction(this, "handleSuccessfulMessage", params, paramTypes, false);
    #endif
    }

    void NetHandler::handleFailedMessage(NetResponse *response)
    {
    #if CC_ENABLE_SCRIPT_BINDING
        Vector<Ref*> params;
        params.pushBack(response);
        Vector<Ref*> paramTypes;
        paramTypes.pushBack(__String::create("pf.NetHandler"));
        
        LuaUtils::getInstance()->executePeertableFunction(this, "handleFailedMessage", params, paramTypes, false);
    #endif
    }
}