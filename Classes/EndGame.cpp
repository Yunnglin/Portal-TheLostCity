#include "EndGame.h"
//#include "Game.h"
#include "ui\CocosGUI.h"
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "AboutScene.h"

using namespace cocos2d::ui;
using cocos2d::ui::SEL_TouchEvent;
using namespace cocos2d;

USING_NS_CC;


Scene* EndGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = EndGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance

bool EndGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = cocos2d::CSLoader::createNode("res/EndGame/endgame.csb");
	this->addChild(rootNode);
	auto SkipBtn = (Button*)rootNode->getChildByName("endGameBtn");
	SkipBtn->addTouchEventListener(this, toucheventselector(EndGame::StartCallback));


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//标题
	auto label = Label::createWithTTF("YOU    WIN", "fonts/Marker Felt.ttf", 50);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height - 10));

	this->addChild(label, 1);

	Label* laber = Label::createWithSystemFont("", "Consolas", 30);
	laber->setColor(Color3B(255, 255, 255));
	std::string sText = "Congratulations! Having successfully led the doctor out of the previous jails, you must think that he will be free soon. Emmmm, maybe you are too naive.... Malicious programmers and product manager have all agreed to set more barriers for him in the future. So, to save our poor doctor, please stay tuned to us for the latest version of our game. Thank you for playing our game.";
	this->addChild(laber);
	laber->setPosition(ccp(640, 400));
	//边界
	laber->setDimensions(1000, 0);

	//打字机效果
	Vector<FiniteTimeAction*> m_vecAct;
	for (int i = 0; i <= sText.length(); i++)
	{
		auto delay = DelayTime::create(0.05f);
		m_vecAct.pushBack(delay);
		std::string str = sText.substr(0, i);
		auto func = [laber, str]() throw() {laber->setString(str); };
		auto call = CallFunc::create(func);
		m_vecAct.pushBack((FiniteTimeAction*)call);
	}
	laber->runAction(Sequence::create(m_vecAct));
	return true;
}


void EndGame::StartCallback(Ref*, TouchEventType type) {
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, AboutScene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	default:
		break;
	}
}
