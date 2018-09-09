
#include "LevelSelectScene.h"
#include "LevelScene.h"


Scene* LevelSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelSelectScene::create();
	scene->addChild(layer);
	return scene;
}


bool LevelSelectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	int level = UserDefault::getInstance()->getIntegerForKey("HeighLevel");

	auto rootNode = CSLoader::createNode("res/SelectLevel/LevelSelectScene.csb");
	addChild(rootNode); 
	Button * BtnLevel1 = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "BtnLevel1");
	BtnLevel1->addTouchEventListener(this, toucheventselector(LevelSelectScene::onClick1));
	Button * BtnLevel2 = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "BtnLevel2");
	BtnLevel2->addTouchEventListener(this, toucheventselector(LevelSelectScene::onClick2));
	Button * BtnLevel3 = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "BtnLevel3");
	BtnLevel3->addTouchEventListener(this, toucheventselector(LevelSelectScene::onClick3));
	Button * BtnLevel4 = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "BtnLevel4");
	BtnLevel4->addTouchEventListener(this, toucheventselector(LevelSelectScene::onClick4));
	Button * BtnLevel5 = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "BtnLevel5");
	BtnLevel5->addTouchEventListener(this, toucheventselector(LevelSelectScene::onClick5));
	Button * BtnLevelBack = (Button*)Helper::seekWidgetByName((Widget*)rootNode,"BtnLevelBack");
	BtnLevelBack->addTouchEventListener(this, toucheventselector(LevelSelectScene::onClickBack));

	switch(level) {
	case 1:
		BtnLevel2->setBright(false);
		BtnLevel2->setTouchEnabled(false);
		BtnLevel3->setBright(false);
		BtnLevel3->setTouchEnabled(false);
		BtnLevel4->setBright(false);
		BtnLevel4->setTouchEnabled(false);
		BtnLevel5->setBright(false);
		BtnLevel5->setTouchEnabled(false);
		break;
	case 2:
		BtnLevel2->setBright(true);
		BtnLevel2->setTouchEnabled(true);
		BtnLevel3->setBright(false);
		BtnLevel3->setTouchEnabled(false);
		BtnLevel4->setBright(false);
		BtnLevel4->setTouchEnabled(false);
		BtnLevel5->setBright(false);
		BtnLevel5->setTouchEnabled(false);
		break;
	case 3:
		BtnLevel2->setBright(true);
		BtnLevel2->setTouchEnabled(true);
		BtnLevel3->setBright(true);
		BtnLevel3->setTouchEnabled(true);
		BtnLevel4->setBright(false);
		BtnLevel4->setTouchEnabled(false);
		BtnLevel5->setBright(false);
		BtnLevel5->setTouchEnabled(false);
		break;
	case 4:
		BtnLevel2->setBright(true);
		BtnLevel2->setTouchEnabled(true);
		BtnLevel3->setBright(true);
		BtnLevel3->setTouchEnabled(true);
		BtnLevel4->setBright(true);
		BtnLevel4->setTouchEnabled(true);
		BtnLevel5->setBright(false);
		BtnLevel5->setTouchEnabled(false);
		break;
	case 5:
		BtnLevel2->setBright(true);
		BtnLevel2->setTouchEnabled(true);
		BtnLevel3->setBright(true);
		BtnLevel3->setTouchEnabled(true);
		BtnLevel4->setBright(true);
		BtnLevel4->setTouchEnabled(true);
		BtnLevel5->setBright(true);
		BtnLevel5->setTouchEnabled(true);
		break;

	}

	return true;
}
void LevelSelectScene::onClick1(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		UserDefault::getInstance()->setIntegerForKey("PreLevel", 1);
		UserDefault::getInstance()->flush();
		Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void LevelSelectScene::onClick2(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		UserDefault::getInstance()->setIntegerForKey("PreLevel", 2);
		UserDefault::getInstance()->flush();
		Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void LevelSelectScene::onClick3(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		UserDefault::getInstance()->setIntegerForKey("PreLevel", 3);
		UserDefault::getInstance()->flush();
		Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void LevelSelectScene::onClick4(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		UserDefault::getInstance()->setIntegerForKey("PreLevel", 4);
		UserDefault::getInstance()->flush();
		Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void LevelSelectScene::onClick5(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		UserDefault::getInstance()->setIntegerForKey("PreLevel", 5);
		UserDefault::getInstance()->flush();
		Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void LevelSelectScene::onClickBack(Ref*, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->popSceneWithTransition<TransitionFade>(1.0f);
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}