#include "HelpScene.h"
#include "StartMenuScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelpScene::createScene()
{
	auto scene = Scene::create();

	auto layer = HelpScene::create();

	scene->addChild(layer);

	return scene;
}

bool HelpScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto helpScene = CSLoader::createNode("res/HelpScene/MainScene.csb");

	this->addChild(helpScene);

	auto btnBack = (Button*)helpScene->getChildByName("btnBack");

	btnBack->addTouchEventListener(this, toucheventselector(HelpScene::BacktoMenuClick));

	return true;
}

void HelpScene::BacktoMenuClick(Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->popSceneWithTransition<TransitionFade>(1.0f);
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	default:
		break;
	}
}