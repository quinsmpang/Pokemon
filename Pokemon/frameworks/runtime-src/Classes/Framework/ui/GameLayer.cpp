#include "GameLayer.h"

using namespace cocos2d;

namespace framework
{

GameLayer::GameLayer()
	: _parentLayer(nullptr)
	, _focusNode(nullptr)
	, _isEnabled(true)
{
}

GameLayer *GameLayer::create()
{
	auto pLayer = new GameLayer();
	pLayer->autorelease();

	return pLayer;
}

bool GameLayer::init()
{
	return Layer::init();
}

}