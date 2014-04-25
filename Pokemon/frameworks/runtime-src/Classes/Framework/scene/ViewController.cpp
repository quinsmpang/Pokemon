#include "ViewController.h"
#include "lua/LuaUtils.h"

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
#if ScriptType == 1
		LuaUtils::executePeertableFunction(this, "load", nullptr, nullptr, false);
#endif
	}

	void ViewController::unload()
	{
#if ScriptType == 1
		LuaUtils::executePeertableFunction(this, "unload", nullptr, nullptr, false);
#endif
	}

}