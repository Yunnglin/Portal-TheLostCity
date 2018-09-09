#include "AboutScene.h"
#include "StartMenuScene.h"
Scene* AboutScene::createScene()
{
	
	auto scene = Scene::create();

	auto layer = AboutScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool AboutScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto aboutScene = CSLoader::createNode("res/about/AboutScene.csb");

	this->addChild(aboutScene);

	auto btnBack = (Button*)aboutScene->getChildByName("btnBack");

	btnBack->addTouchEventListener(this, toucheventselector(AboutScene::onClick));


	return true;
}

void AboutScene::onClick(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN: // 点击事件开始时触发（也就是按下的时候）
		break;
	case TouchEventType::TOUCH_EVENT_MOVED: // 按下之后，进行移动操作时触发
		break;
	case TouchEventType::TOUCH_EVENT_ENDED: // 按下之后，然后松开时触发
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.8f, StartMenuScene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:  // 因为一些特殊情况而中断点击事件时触发
		break;
	default:
		break;
	}

}