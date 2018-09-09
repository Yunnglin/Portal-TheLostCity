#include "WinScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
//#include "StartMenuScene.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using cocos2d::ui::SEL_TouchEvent;
using namespace cocostudio::timeline;

Scene* WinScene::createScene()
{
	auto scene = Scene::create();

	auto layer = WinScene::create();

	scene->addChild(layer);

	return scene;
}

bool WinScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winScene = CSLoader::createNode("WinScene/WinScene.csb");

	this->addChild(winScene);

	auto btnBack = (Button*)winScene->getChildByName("btnBack");

	btnBack->addTouchEventListener(this, toucheventselector(WinScene::BacktoMenuClick));

	return true;
}

void WinScene::BacktoMenuClick(cocos2d::Ref* pSender, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(TransitionProgressCrossFade::create(0.5f, StartMenuScene::createScene());
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	default:
		break;
	}
}