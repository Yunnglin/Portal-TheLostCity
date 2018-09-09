#include "Setting_Scene.h"
#include "ui\CocosGUI.h"
#include "StartMenuScene.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

#define USER UserDefault::getInstance()

using namespace CocosDenshion;

using cocos2d::ui::SEL_TouchEvent;
using namespace cocos2d;
using namespace cocos2d::experimental;

//AudioEngine�����ԣ�ͨ��int�ͱ�����Ӧ����  ���libcocos2d/audioengine/AudiEngine.h/cpp
//ͬʱ��������
int Setting_Scene::audioID = AudioEngine::play2d("bgmusic.mp3",true,1.0f);    //����
//int Setting_Scene::effectID = AudioEngine::play2d("Setting_Scene/effect.mp3");  //��Ч

cocos2d::Scene* Setting_Scene::createScene()
{
	auto scene = Scene::create();
	auto layer = Setting_Scene::create();
	scene->addChild(layer);

	return scene;
}

bool Setting_Scene::init() {
	if (!Scene::init()) {
		return false;
	}
	
	isTouched = 0;

	/*���ò˵���������,�Լ����ر�������*/
	auto rootNode = cocos2d::CSLoader::createNode("Setting_Scene/Setting_Scene.csb");
	this->addChild(rootNode);

	/*�������˵�*/
	auto mainMenuBtn = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("Back to menu"));
	mainMenuBtn->addTouchEventListener(this, toucheventselector(Setting_Scene::buttonMainMenuCallBack));
	
	/*��������*/
	auto soundCheckBox = dynamic_cast<cocos2d::ui::CheckBox*>(rootNode->getChildByName("CheckBox"));


	soundCheckBox->addTouchEventListener(this, toucheventselector(Setting_Scene::checkBoxCallback));
	
	if (AudioEngine::getVolume(audioID) * 100) {
		soundCheckBox->setSelectedState(true);
	}


	/*�ڶ�������slider,��Ч����*/
	auto slider2 = dynamic_cast<cocos2d::ui::Slider*>(rootNode->getChildByName("Slider_2"));
	slider2->setPercent(AudioEngine::getVolume(audioID) * 100);
	slider2->addTouchEventListener(this, toucheventselector(Setting_Scene::sliderCallback2));

}

// CheckBox��д��

void Setting_Scene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED: {
		isTouched = isTouched + 1;
	}
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED: {
	}
		break;
	default:
		break;
	}

	if (isTouched % 2 == 0) {
		AudioEngine::resumeAll();   //��ż���»ָ�����

	}
	else {
		AudioEngine::pauseAll();    //����������ͣ����

	}
}


//ʵ��Slider�����ص�����2, ���������ӿ�

void Setting_Scene::sliderCallback2(cocos2d::Ref * ref, Slider::EventType type)
{
	auto item = (Slider*)ref;
	switch (type)
	{
	case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		Slider* slider = (Slider*)ref;
		int percent = slider->getPercent();
		AudioEngine::setVolume(Setting_Scene::audioID, percent / 100.0);
	}
	break;
	default:
		break;
	}
}

//��ť��BacktoMenu�ص����˵�

void Setting_Scene::buttonMainMenuCallBack(Ref *ref, cocos2d::ui::TouchEventType type) {
	switch (type) {
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED:
		cocos2d::Director::getInstance()->popSceneWithTransition<TransitionFade>(1.0f);
		break;
	}
}
