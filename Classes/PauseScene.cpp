#include "PauseScene.h"
#include "StartMenuScene.h"
#include "Setting_Scene.h"
#include "LevelScene.h"
#include "LevelSelectScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* PauseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto pauseScene = CSLoader::createNode("res/pause/PauseScene.csb");

	addChild(pauseScene);

	auto btnResume = (Button*)pauseScene->getChildByName("btnResume");
	auto btnRestart = (Button*)pauseScene->getChildByName("btnRestart");
	auto btnSelectLevel = (Button*)pauseScene->getChildByName("btnSelectLevel");
	auto btnSettings = (Button*)pauseScene->getChildByName("btnSettings");
	auto btnBackToMenu = (Button*)pauseScene->getChildByName("btnBackToMenu");

	btnResume->addTouchEventListener(this, toucheventselector(PauseScene::onClick1));
	btnRestart->addTouchEventListener(this, toucheventselector(PauseScene::onClick2));
	btnSelectLevel->addTouchEventListener(this, toucheventselector(PauseScene::onClick3));
	btnSettings->addTouchEventListener(this, toucheventselector(PauseScene::onClick4));
	btnBackToMenu->addTouchEventListener(this, toucheventselector(PauseScene::onClick5));

	return true;
}

void PauseScene::onClick1(Ref*, TouchEventType type) {
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
void PauseScene::onClick2(Ref*, TouchEventType type) {
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:

		Director::getInstance()->popSceneWithTransition<TransitionFade>(1.0f);
		Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	default:
		break;
	}
}
void PauseScene::onClick3(Ref*, TouchEventType type) {
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		cocos2d::Director::getInstance()->pushScene(TransitionCrossFade::create(0.8f, LevelSelectScene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	default:
		break;
	}
}
void PauseScene::onClick4(Ref*, TouchEventType type) {
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		cocos2d::Director::getInstance()->pushScene(TransitionCrossFade::create(0.8f, Setting_Scene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	default:
		break;
	}
}
void PauseScene::onClick5(Ref*, TouchEventType type) {
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.8f, StartMenuScene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	default:
		break;
	}
}