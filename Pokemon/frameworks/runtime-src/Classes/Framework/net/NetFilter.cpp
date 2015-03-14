#include "NetFilter.h"
#include "NetResponse.h"
#include "../lua/LuaUtils.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace framework
{
	bool NetFilter::init()
	{
		return true;
	}

	NetFilter::~NetFilter()
	{
	}

	void NetFilter::filterSuccessfulMessage(NetResponse *response)
	{
#if CC_ENABLE_SCRIPT_BINDING
		Vector<Ref*> params;
		params.pushBack(response);
		Vector<Ref*> paramTypes;
		paramTypes.pushBack(__String::create("pf.NetResponse"));

		LuaUtils::getInstance()->executePeertableFunction(this, "filterSuccessfulMessage", params, paramTypes, true);
#endif
	}

	void NetFilter::filterFailedMessage(NetResponse *response)
	{
#if CC_ENABLE_SCRIPT_BINDING
		Vector<Ref*> params;
		params.pushBack(response);
		Vector<Ref*> paramTypes;
		paramTypes.pushBack(__String::create("pf.NetResponse"));

		LuaUtils::getInstance()->executePeertableFunction(this, "filterFailedMessage", params, paramTypes, true);
#endif
	}
}