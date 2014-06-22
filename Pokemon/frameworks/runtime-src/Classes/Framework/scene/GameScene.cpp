#include "GameScene.h"
#include "lua/LuaUtils.h"

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

	GameScene *GameScene::create(cocos2d::__Dictionary *paramsMap)
	{
		auto pScene = GameScene::create();
		paramsMap->retain();
		if (pScene->_paramsMap)
		{
			pScene->release();
			pScene = nullptr;
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

		this->_paramsMap = __Dictionary::create();
		this->_paramsMap->retain();
		this->_viewControllers = new Vector<ViewController*>();

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
			LuaUtils::getInstance()->executePeertableFunction(this, "onEnter", Vector<Ref*>(), Vector<Ref*>(), false);
		}
#endif
	}

	void GameScene::onExit()
	{
#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::getInstance()->executePeertableFunction(this, "onExit", Vector<Ref*>(), Vector<Ref*>(), false);
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
			LuaUtils::getInstance()->executePeertableFunction(this, "onEnterTransitionDidFinish", Vector<Ref*>(), Vector<Ref*>(), false);
		}
#endif
	}

	void GameScene::onExitTransitionDidStart()
	{
		Scene::onExitTransitionDidStart();

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			LuaUtils::getInstance()->executePeertableFunction(this, "onExitTransitionDidStart", Vector<Ref*>(), Vector<Ref*>(), false);
		}
#endif
	}

	void GameScene::putBoolAttribute(const std::string &key, bool value)
	{
		this->_paramsMap->setObject(__Bool::create(value), key);
	}

	void GameScene::putIntAttribute(const std::string &key, int value)
	{
		this->_paramsMap->setObject(__Integer::create(value), key);
	}

	void GameScene::putDoubleAttribute(const std::string &key, double value)
	{
		this->_paramsMap->setObject(__Double::create(value), key);
	}

	void GameScene::putStringAttribute(const std::string &key, const std::string &value)
	{
		this->_paramsMap->setObject(__String::create(value), key);
	}

	void GameScene::putRefAttribute(const std::string &key, Ref *value)
	{
		this->_paramsMap->setObject(value, key);
	}

	bool GameScene::getBoolAttribute(const std::string &key)
	{
		Ref *value = this->getRefAttribute(key);
		__Bool *boolValue = dynamic_cast<__Bool*>(value);
		if (boolValue)
		{
			return boolValue->getValue();
		}

		return false;
	}

	int GameScene::getIntAttribute(const std::string &key)
	{
		Ref *value = this->getRefAttribute(key);
		__Integer *intValue = dynamic_cast<__Integer*>(value);
		if (intValue)
		{
			return intValue->getValue();
		}

		return 0;
	}

	double GameScene::getDoubleAttribute(const std::string &key)
	{
		Ref *value = this->getRefAttribute(key);
		__Double *doubleValue = dynamic_cast<__Double*>(value);
		if (doubleValue)
		{
			return doubleValue->getValue();
		}

		return 0;
	}

	const char *GameScene::getStringAttribute(const std::string &key)
	{
		Ref *value = this->getRefAttribute(key);
		__String *strValue = dynamic_cast<__String*>(value);
		if (strValue)
		{
			return strValue->getCString();
		}

		return nullptr;
	}

	Ref *GameScene::getRefAttribute(const std::string &key)
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