#include "StartGame.h"
#include "ui\CocosGUI.h"
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "LevelScene.h"

using namespace cocos2d::ui;
using cocos2d::ui::SEL_TouchEvent;
using namespace cocos2d;

USING_NS_CC;


Scene* StartGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance

bool StartGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto rootNode = cocos2d::CSLoader::createNode("res/StartGame/StartGame.csb");
	this->addChild(rootNode);
	auto SkipBtn = (Button*)rootNode->getChildByName("Skipbtn");
	SkipBtn->addTouchEventListener(this, toucheventselector(StartGame::StartCallback));


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

 
    
	//标题
    auto label = Label::createWithTTF("Portal: The lost city", "fonts/Marker Felt.ttf", 40);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height - 10));

    this->addChild(label, 1);

	Label* laber = Label::createWithSystemFont("", "Consolas", 30);
	laber->setColor(Color3B(255, 255, 255));
	std::string sText = "In 8102, a genius scientist named Dr Who invented a tool that could open portals under the auspices of an ancient and mysterious organization. The ancient city of Atlantis hides the artifacts that this organization has been pursuing for centuries. However, when Doctor and his assistants approached near the site, they encountered strong magnetic and gravitational anomalies. When Dr Who tried to escape from the disaster, he was suddenly taken away by the mechanism of Atlantis and trapped on the bottom of sea. Please lead the doctor to escape from the cages.";
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


void StartGame::StartCallback(Ref* pSender, cocos2d::ui::TouchEventType type)
{
	//记得删改

	UserDefault::getInstance()->setIntegerForKey("PreLevel", 1);
	UserDefault::getInstance()->flush();
	Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

