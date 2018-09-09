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
	case TouchEventType::TOUCH_EVENT_BEGAN: // ����¼���ʼʱ������Ҳ���ǰ��µ�ʱ��
		break;
	case TouchEventType::TOUCH_EVENT_MOVED: // ����֮�󣬽����ƶ�����ʱ����
		break;
	case TouchEventType::TOUCH_EVENT_ENDED: // ����֮��Ȼ���ɿ�ʱ����
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.8f, StartMenuScene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:  // ��ΪһЩ����������жϵ���¼�ʱ����
		break;
	default:
		break;
	}

}