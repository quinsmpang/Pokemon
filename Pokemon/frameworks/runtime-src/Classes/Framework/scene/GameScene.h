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
        /**
         * Create a GameScene object.
         *
         * @return Return a new GameScene object.
         */
		CREATE_FUNC(GameScene);

        /**
         * Create a GameScene object with passed parameters.
         *
         * @param paramsMap Parameters map.
         *
         * @return Return a new GameScene object.
         */
		static GameScene *create(Map *paramsMap);

        /**
         * GameScene destructor.
         */
		virtual ~GameScene();

        /**
         * Set the bottom layer of the scene.
         *
         * @param coreLayer Bottom layer of the scene.
         */
		void setCoreLayer(CoreLayer *coreLayer);
        /**
         * Get the bottom layer of the scene.
         *
         * @return Bottom layer of the scene.
         */
		inline CoreLayer *getCoreLayer()
		{
			return this->_coreLayer;
		}

        /**
         * Node base events overrides.
         */
		virtual void onEnter() override;
		virtual void onExit() override;
		virtual void onEnterTransitionDidFinish() override;
		virtual void onExitTransitionDidStart() override;

        /**
         * Put boolean parameter into the scene.
         *
         * @param key Parameter key name.
         * @param value Boolean parameter.
         */
		void putBoolAttribute(const std::string &key, bool value);
        /**
         * Put integer parameter into the scene.
         *
         * @param key Parameter key name.
         * @param value Integer parameter.
         */
		void putIntAttribute(const std::string &key, int value);
        /**
         * Put decimal parameter into the scene.
         *
         * @param key Parameter key name.
         * @param value Decimal parameter.
         */
		void putDoubleAttribute(const std::string &key, double value);
        /**
         * Put string parameter into the scene.
         *
         * @param key Parameter key name.
         * @param value String parameter.
         */
		void putStringAttribute(const std::string &key, const std::string &value);
        /**
         * Put cocos2dx parameter into the scene.
         *
         * @param key Parameter key name.
         * @param value Ref parameter.
         */
		void putRefAttribute(const std::string &key, cocos2d::Ref *value);
        /**
         * Get boolean parameter from the scene.
         *
         * @param key The parameter key name to consult.
         *
         * @return The specified value you would like to consult.
         */
		bool getBoolAttribute(const std::string &key) const;
        /**
         * Get integer parameter from the scene.
         *
         * @param key The parameter key name to consult.
         *
         * @return The specified value you would like to consult.
         */
		int getIntAttribute(const std::string &key) const;
        /**
         * Get decimal parameter from the scene.
         *
         * @param key The parameter key name to consult.
         *
         * @return The specified value you would like to consult.
         */
		double getDoubleAttribute(const std::string &key) const;
        /**
         * Get string parameter from the scene.
         *
         * @param key The parameter key name to consult.
         *
         * @return The specified value you would like to consult.
         */
		const char *getStringAttribute(const std::string &key) const;
        /**
         * Get Ref parameter from the scene.
         *
         * @param key The parameter key name to consult.
         *
         * @return The specified value you would like to consult.
         */
		cocos2d::Ref *getRefAttribute(const std::string &key) const;
        
        /**
         * Load a view controller.
         *
         * @param viewController The controller to load.
         */
		void loadViewController(ViewController *viewController);
        /**
         * Unload a view controller.
         *
         * @param viewController The controller to unload.
         */
		void unloadViewController(ViewController *viewController);
        /**
         * Uninstall all view controllers.
         */
		void unloadAllViewControllers();
	protected:
		GameScene();
        
		virtual bool init() override;

		Map *_paramsMap;
		cocos2d::Vector<ViewController*> *_viewControllers;
		CoreLayer *_coreLayer;
	};

}

#endif