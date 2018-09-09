#include "StartMenuScene.h"
#include "LevelSelectScene.h"
#include "Setting_Scene.h"
#include "HelpScene.h"
#include "AboutScene.h"
#include "LevelScene.h"
#include "StartGame.h"


using cocos2d::ui::SEL_TouchEvent;

cocos2d::Scene* StartMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartMenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool StartMenuScene::init()
{
	if (!Scene::init())
		return false;

	/*��ʼ�˵���������*/
	auto rootNode = cocos2d::CSLoader::createNode("res/StartMenuScene/StartMenuScene.csb");
	this->addChild(rootNode);


	/*��ʼ����Ϸ*/
	auto newGameBtn = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("StartMenu_NewGameBtn"));
	newGameBtn->addTouchEventListener(this, toucheventselector(StartMenuScene::menuNewGameCallBack));

	/*������Ϸ*/
	auto continueBtn = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("StartMenu_ContinueBtn"));
	continueBtn->addTouchEventListener(this, toucheventselector(StartMenuScene::menuContinueCallBack));

	/*ѡ��*/
	auto levelSelectBtn = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("StartMenu_LevelSelectBtn"));
	levelSelectBtn->addTouchEventListener(this, toucheventselector(StartMenuScene::menuLevelSelectCallBack));

	/*�趨*/
	auto settingsBtn = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("StartMenu_SettingsBtn"));
	settingsBtn->addTouchEventListener(this, toucheventselector(StartMenuScene::menuSettingsCallBack));

	/*����*/
	auto helpBtn = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("StartMenu_HelpBtn"));
	helpBtn->addTouchEventListener(this, toucheventselector(StartMenuScene::menuHelpCallBack));

	/*����*/
	auto aboutBtn = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("StartMenu_AboutBtn"));
	aboutBtn->addTouchEventListener(this, toucheventselector(StartMenuScene::menuAboutCallBack));

	/*�˳���Ϸ��ť*/
	auto exitBtn = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("StartMenu_ExitBtn"));
	exitBtn->addTouchEventListener(this, toucheventselector(StartMenuScene::menuExitCallBack));

	return true;
}

void StartMenuScene::menuNewGameCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type) {
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED:
		
		cocos2d::Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, StartGame::createScene()));
		//�л�����Ϸ����
		break;
	}
}



void StartMenuScene::menuContinueCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type) {
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED:
		UserDefault::getInstance()->setIntegerForKey("PreLevel",
			UserDefault::getInstance()->getIntegerForKey("HeighLevel")
		);
		cocos2d::Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
		//�л�����߹ص���Ϸ����
		break;
	}
}

void StartMenuScene::menuLevelSelectCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type) {
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->pushScene(TransitionCrossFade::create(0.8f, LevelSelectScene::createScene()));
		break;
	}
}

void StartMenuScene::menuSettingsCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type) {
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED:
		cocos2d::Director::getInstance()->pushScene(TransitionCrossFade::create(0.8f, Setting_Scene::createScene()));
		break;
	}
}

void StartMenuScene::menuHelpCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type) {
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED:
		cocos2d::Director::getInstance()->pushScene(TransitionCrossFade::create(0.8f, HelpScene::createScene()));
		break;
	}
}

void StartMenuScene::menuAboutCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type) {
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED:
		cocos2d::Director::getInstance()->pushScene(TransitionCrossFade::create(0.8f,AboutScene::createScene()));
		break;
	}
}

void StartMenuScene::menuExitCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type) {
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED:
		cocos2d::Director::getInstance()->end();
	}
}