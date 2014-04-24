/******************************
	Description: Manage handlers in lua, while lua-binding doesn't support std::function
	Author: M.Wan
	Date: 4/24/2014
******************************/

#ifndef __LUA_SCRIPTHANDLERMANAGER__
#define __LUA_SCRIPTHANDLERMANAGER__

#include "cocos2d.h"
#include <vector>
#include <map>

enum class ScriptHandlerType
{
	EVENTNODE_TOUCH,
	EVENTNODE_KEYBOARD,
};

class ScriptHandlerDelegate : public cocos2d::Ref
{
	friend class ScriptHandlerManager;
public:
	static ScriptHandlerDelegate *create(cocos2d::Node *listener, void *handler);

	~ScriptHandlerDelegate();
private:
	ScriptHandlerDelegate(cocos2d::Node *listener, void *handler);

	cocos2d::Node *_listener;
	void *_handler;
};

class ScriptHandlerManager
{
public:
	static ScriptHandlerManager *getInstance();

	void addHandler(cocos2d::Node *listener, void *handler, ScriptHandlerType handlerType);
	void removeHandler(cocos2d::Node *listener, ScriptHandlerType handlerType);
	void notify(ScriptHandlerType handlerType);
private:
	ScriptHandlerManager();
	~ScriptHandlerManager();

	static ScriptHandlerManager *_instance;

	std::map<ScriptHandlerType, std::vector<ScriptHandlerDelegate*> > _handlers;
};

#endif