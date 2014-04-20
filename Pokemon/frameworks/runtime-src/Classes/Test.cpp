#include "Test.h"
#include "ui/MaskLayer.h"

using namespace cocos2d;
using namespace framework;

Scene *TestScene::scene()
{
	auto pScene = Scene::create();

	auto pLayer = TestScene::create();

	pScene->addChild(pLayer);

	return pScene;
}

bool TestScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	auto pMaskLayer = MaskLayer::create(Rect(200, 300, 100, 100));

	auto pStencil = Sprite::create("E:/Download/1.jpg");
	pStencil->setPosition(winSize.width / 2, winSize.height / 2);
	pMaskLayer->addChild(pStencil);
	pMaskLayer->setOpacity(200);
	pMaskLayer->setColor(Color3B::GREEN);

	this->addChild(pMaskLayer);

	return true;
}