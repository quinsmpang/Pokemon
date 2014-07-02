#include "ViewController.h"
#include "../lua/LuaUtils.h"

using namespace cocos2d;

namespace framework
{

	ViewController::~ViewController()
	{
	}

	bool ViewController::init()
	{
		// to be override
		return true;
	}

	void ViewController::load()
	{
#if CC_ENABLE_SCRIPT_BINDING
		LuaUtils::getInstance()->executePeertableFunction(this, "load", Vector<Ref*>(), Vector<Ref*>(), false);
#endif
	}

	void ViewController::unload()
	{
#if CC_ENABLE_SCRIPT_BINDING
		LuaUtils::getInstance()->executePeertableFunction(this, "unload", Vector<Ref*>(), Vector<Ref*>(), false);
#endif
	}

}