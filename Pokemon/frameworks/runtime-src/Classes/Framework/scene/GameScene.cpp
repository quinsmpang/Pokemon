#include "GameScene.h"
#include "../lua/LuaUtils.h"
#include "../base/RefBoolean.h"
#include "../base/RefInteger.h"
#include "../base/RefDouble.h"
#include "../base/RefString.h"

using namespace cocos2d;

namespace framework
{

	GameScene::GameScene()
		: Scene()
		, _paramsMap(nullptr)
		, _viewControllers(nullptr)
		, _coreLayer(nullptr)
	{
	}

	GameScene::~GameScene()
	{
		CC_SAFE_RELEASE_NULL(this->_paramsMap);
		CC_SAFE_RELEASE_NULL(this->_coreLayer);
		if (this->_viewControllers)
		{
			delete this->_viewControllers;
		}
	}

	GameScene *GameScene::create(Map *paramsMap)
	{
		auto pScene = GameScene::create();
		paramsMap->retain();
		if (pScene->_paramsMap)
		{
			pScene->_paramsMap->release();
		}
		pScene->_paramsMap = paramsMap;

		return pScene;
	}

	bool GameScene::init()
	{
		if (!CCScene::init())
		{
			return false;
		}

		this->_paramsMap = Map::create();
		this->_paramsMap->retain();
		this->_viewControllers = new cocos2d::Vector<ViewController*>();

		return true;
	}

	void GameScene::setCoreLayer(CoreLayer *coreLayer)
	{
		CCASSERT(coreLayer, "The core layer can't be null");

		if (this->_coreLayer)
		{
			this->_coreLayer->removeFromParentAndCleanup(true);
		}
		this->_coreLayer = coreLayer;
		this->_coreLayer->retain();

		this->addChild(coreLayer);
	}

	void GameScene::onEnter()
	{
		Scene::onEnter();

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::getInstance()->executePeertableFunction(this, "onEnter", cocos2d::Vector<Ref*>(), cocos2d::Vector<Ref*>(), false);
		}
#endif
	}

	void GameScene::onExit()
	{
#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::getInstance()->executePeertableFunction(this, "onExit", cocos2d::Vector<Ref*>(), cocos2d::Vector<Ref*>(), false);
		}
#endif

		this->unloadAllViewControllers();

		Scene::onExit();
	}

	void GameScene::onEnterTransitionDidFinish()
	{
		Scene::onEnterTransitionDidFinish();

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::getInstance()->executePeertableFunction(this, "onEnterTransitionDidFinish", cocos2d::Vector<Ref*>(), cocos2d::Vector<Ref*>(), false);
		}
#endif
	}

	void GameScene::onExitTransitionDidStart()
	{
#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::getInstance()->executePeertableFunction(this, "onExitTransitionDidStart", cocos2d::Vector<Ref*>(), cocos2d::Vector<Ref*>(), false);
		}
#endif
		
		Scene::onExitTransitionDidStart();
	}

	void GameScene::putBoolAttribute(const std::string &key, bool value)
	{
		this->_paramsMap->setObjectForKey(RefBoolean::create(value), key);
	}

	void GameScene::putIntAttribute(const std::string &key, int value)
	{
		this->_paramsMap->setObjectForKey(RefInteger::create(value), key);
	}

	void GameScene::putDoubleAttribute(const std::string &key, double value)
	{
		this->_paramsMap->setObjectForKey(RefDouble::create(value), key);
	}

	void GameScene::putStringAttribute(const std::string &key, const std::string &value)
	{
		this->_paramsMap->setObjectForKey(RefString::create(value), key);
	}

	void GameScene::putRefAttribute(const std::string &key, Ref *value)
	{
		this->_paramsMap->setObjectForKey(value, key);
	}

	bool GameScene::getBoolAttribute(const std::string &key) const
	{
		Ref *value = this->getRefAttribute(key);
		RefBoolean *boolValue = dynamic_cast<RefBoolean*>(value);
		if (boolValue)
		{
			return boolValue->getBoolean();
		}

		return false;
	}

	int GameScene::getIntAttribute(const std::string &key) const
	{
		Ref *value = this->getRefAttribute(key);
		RefInteger *intValue = dynamic_cast<RefInteger*>(value);
		if (intValue)
		{
			return intValue->getNumber();
		}

		return 0;
	}

	double GameScene::getDoubleAttribute(const std::string &key) const
	{
		Ref *value = this->getRefAttribute(key);
		RefDouble *doubleValue = dynamic_cast<RefDouble*>(value);
		if (doubleValue)
		{
			return doubleValue->getNumber();
		}

		return 0;
	}

	const char *GameScene::getStringAttribute(const std::string &key) const
	{
		Ref *value = this->getRefAttribute(key);
		RefString *strValue = dynamic_cast<RefString*>(value);
		if (strValue)
		{
			return strValue->getCString();
		}

		return nullptr;
	}

	Ref *GameScene::getRefAttribute(const std::string &key) const
	{
		return this->_paramsMap->objectForKey(key);
	}

	void GameScene::loadViewController(ViewController *viewController)
	{
		CCASSERT(viewController, "viewController can't be null");

		this->_viewControllers->pushBack(viewController);
		viewController->setScene(this);
		viewController->load();
	}

	void GameScene::unloadViewController(ViewController *viewController)
	{
		for (auto iter = this->_viewControllers->begin(); iter < this->_viewControllers->end(); ++iter)
		{
			if (*iter == viewController)
			{
				viewController->unload();
				this->_viewControllers->erase(iter);
				break;
			}
		}
	}

	void GameScene::unloadAllViewControllers()
	{
		for (auto iter = this->_viewControllers->begin(); iter < this->_viewControllers->end(); ++iter)
		{
			(*iter)->unload();
		}
		this->_viewControllers->clear();
	}

}