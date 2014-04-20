/******************************
	Description: Game base scene
	Author: M.Wan
	Date: 4/18/2014
******************************/

#ifndef __SCENE_GAMESCENE_H__
#define __SCENE_GAMESCENE_H__

#include "cocos2d.h"
#include "scene/ViewController.h"

namespace framework
{

class GameScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(GameScene);

	static GameScene *create(cocos2d::__Dictionary *paramsMap);

	virtual ~GameScene();

	virtual bool init() override;

	virtual void onEnter() override;

	virtual void onExit() override;

	void putBoolAttribute(const std::string &key, bool value);

	void putIntAttribute(const std::string &key, int value);

	void putDoubleAttribute(const std::string &key, double value);

	void putStringAttribute(const std::string &key, const std::string &value);

	void putRefAttribute(const std::string &key, cocos2d::Ref *value);

	bool getBoolAttribute(const std::string &key);

	int getIntAttribute(const std::string &key);

	double getDoubleAttribute(const std::string &key);

	const char *getStringAttribute(const std::string &key);

	cocos2d::Ref *getRefAttribute(const std::string &key);

	void loadViewController(ViewController *viewController);

	void unloadViewController(ViewController *viewController);

	void unloadAllViewControllers();
protected:
	cocos2d::__Dictionary *_paramsMap;
	cocos2d::Vector<ViewController*> *_viewControllers;
};

}

#endif