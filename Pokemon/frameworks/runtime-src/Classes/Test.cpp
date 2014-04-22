#include "Test.h"
#include "framework.h"

using namespace cocos2d;
using namespace framework;

class TestDelegate : public MaskLayerDelegate
{
public:
	virtual void onEventPenetrated(float x, float y)
	{
		printf("Penetrated at: %.2f, %.2f\n", x, y);
	}

	virtual void onEventIntercepted(float x, float y)
	{
		printf("Intercepted at: %.2f, %.2f\n", x, y);
	}
};

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

	auto pMaskLayer = MaskLayer::create(Rect(100, 100, 100, 100));

	auto pStencil = Sprite::create("farm.jpg");
	pStencil->setPosition(winSize.width / 2, winSize.height / 2);
	pMaskLayer->addChild(pStencil);
	pMaskLayer->setOpacity(200);
	pMaskLayer->setColor(Color3B::BLACK);
	pMaskLayer->forceInterceptAllEvents(false);

	MaskLayerDelegate *pDelegate = new TestDelegate();
	pMaskLayer->setDelegate(pDelegate);

	this->addChild(pMaskLayer);

	auto pGameLayer = GameLayer::create();
	auto btn = Button::create("btn1.png", "btn2.png", TOUCH_EVENT_CALLBACK(TestScene::onBtnClick, this), KEYBOARD_EVENT_CALLBACK(TestScene::onKbdPressed, this));
	btn->setPosition(winSize.width * 0.5, winSize.height * 0.5);
	pGameLayer->addControl(btn);
	pGameLayer->setFocusNode(btn);
	pGameLayer->registerTouchEvents();

	this->addChild(pGameLayer);

	return true;
}

void TestScene::onBtnClick(void *pParam)
{
	printf("btn clicked\n");
}

void TestScene::onKbdPressed(EventKeyboard::KeyCode keyCode, void *pParam)
{
	printf("%d pressed\n", keyCode);
}