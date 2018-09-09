#include "YouDiedScene.h"
#include "LevelScene.h"
#include "StartMenuScene.h"
using namespace CocosDenshion;



Scene* YouDiedScene::createScene()
{
	auto scene = Scene::create();
	auto layer = YouDiedScene::create();
	scene->addChild(layer);
	
	return scene;
}


bool YouDiedScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("res/youDied/MainScene.csb");
	addChild(rootNode);
	
	Button * BtnContinue = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "BtnContinue");
	BtnContinue->addTouchEventListener(this, toucheventselector(YouDiedScene::onClick1));
	Button * BtnBack = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "BtnBack");
	BtnBack->addTouchEventListener(this, toucheventselector(YouDiedScene::onClick2));

	
	return true;
}
void YouDiedScene::onClick1(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void YouDiedScene::onClick2(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, StartMenuScene::createScene()));
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}


