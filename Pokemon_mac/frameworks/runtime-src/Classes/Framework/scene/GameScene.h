/******************************
Description: Game base scene
Author: M.Wan
Date: 4/18/2014
******************************/

#ifndef __SCENE_GAMESCENE_H__
#define __SCENE_GAMESCENE_H__

#include "cocos2d.h"
#include "ViewController.h"
#include "../ui/CoreLayer.h"
#include "../containers/Map.h"

namespace framework
{

	class GameScene : public cocos2d::Scene
	{
	public:
		CREATE_FUNC(GameScene);

		static GameScene *create(Map *paramsMap);

		virtual ~GameScene();

		virtual bool init() override;

		void setCoreLayer(CoreLayer *coreLayer);

		inline CoreLayer *getCoreLayer()
		{
			return this->_coreLayer;
		}

		virtual void onEnter() override;

		virtual void onExit() override;

		virtual void onEnterTransitionDidFinish() override;

		virtual void onExitTransitionDidStart() override;

		void putBoolAttribute(const std::string &key, bool value);

		void putIntAttribute(const std::string &key, int value);

		void putDoubleAttribute(const std::string &key, double value);

		void putStringAttribute(const std::string &key, const std::string &value);

		void putRefAttribute(const std::string &key, cocos2d::Ref *value);

		bool getBoolAttribute(const std::string &key) const;

		int getIntAttribute(const std::string &key) const;

		double getDoubleAttribute(const std::string &key) const;

		const char *getStringAttribute(const std::string &key) const;

		cocos2d::Ref *getRefAttribute(const std::string &key) const;

		void loadViewController(ViewController *viewController);

		void unloadViewController(ViewController *viewController);

		void unloadAllViewControllers();
	protected:
		GameScene();

		Map *_paramsMap;
		cocos2d::Vector<ViewController*> *_viewControllers;
		CoreLayer *_coreLayer;
	};

}

#endif