#include "WinnerScene.h"
#include "StartMenuScene.h"
#include "EndGame.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* WinnerScene::createScene()
{
	auto scene = Scene::create();

	auto layer = WinnerScene::create();	
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool WinnerScene::init()
{
	
	if (!Layer::init())
	{
		return false;
	}
	auto winScene = CSLoader::createNode("res/winScene/WinScene.csb");

	this->addChild(winScene);

	auto btnBack = (Button*)winScene->getChildByName("btnBack");

	btnBack->addTouchEventListener(this, toucheventselector(WinnerScene::BacktoMenuClick));

	return true;
}

void WinnerScene::BacktoMenuClick(cocos2d::Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, EndGame::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	default:
		break;
	}
}