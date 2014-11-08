#include "Win32EventListener.h"

using namespace cocos2d;

namespace framework
{
	Win32EventListener::Win32EventListener()
		: _isEnabled(true)
		, _swallowed(true)
		, _type()
		, _listenerId()
		, _target(nullptr)
		, _callback()
	{
	}

	Win32EventListener::~Win32EventListener()
	{
	}

	bool Win32EventListener::init(Win32EventListenerType type, WIN32_LISTENER_ID listenerId, Node *target, const std::function<void(Node*, Win32EventArgs*)> &callback)
	{
		_type = type;
		_listenerId = listenerId;
		_target = target;
		_callback = callback;
		_isEnabled = true;

		// lua support
#if CC_ENABLE_SCRIPT_BINDING
		ScriptEngineProtocol *pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
		_scriptType = pEngine ? pEngine->getScriptType() : kScriptTypeNone;
#endif

		return true;
	}
}