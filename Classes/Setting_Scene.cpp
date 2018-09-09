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

//AudioEngine的特性，通过int型变量对应音乐  详见libcocos2d/audioengine/AudiEngine.h/cpp
//同时播放音乐
int Setting_Scene::audioID = AudioEngine::play2d("bgmusic.mp3",true,1.0f);    //音乐
//int Setting_Scene::effectID = AudioEngine::play2d("Setting_Scene/effect.mp3");  //音效

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

	/*设置菜单场景加载,以及加载背景音乐*/
	auto rootNode = cocos2d::CSLoader::createNode("Setting_Scene/Setting_Scene.csb");
	this->addChild(rootNode);

	/*返回主菜单*/
	auto mainMenuBtn = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("Back to menu"));
	mainMenuBtn->addTouchEventListener(this, toucheventselector(Setting_Scene::buttonMainMenuCallBack));
	
	/*开关声音*/
	auto soundCheckBox = dynamic_cast<cocos2d::ui::CheckBox*>(rootNode->getChildByName("CheckBox"));


	soundCheckBox->addTouchEventListener(this, toucheventselector(Setting_Scene::checkBoxCallback));
	
	if (AudioEngine::getVolume(audioID) * 100) {
		soundCheckBox->setSelectedState(true);
	}


	/*第二个滑条slider,音效控制*/
	auto slider2 = dynamic_cast<cocos2d::ui::Slider*>(rootNode->getChildByName("Slider_2"));
	slider2->setPercent(AudioEngine::getVolume(audioID) * 100);
	slider2->addTouchEventListener(this, toucheventselector(Setting_Scene::sliderCallback2));

}

// CheckBox复写框

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
		AudioEngine::resumeAll();   //按偶数下恢复播放

	}
	else {
		AudioEngine::pauseAll();    //按奇数下暂停播放

	}
}


//实现Slider滑动回调函数2, 音乐音量接口

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

//按钮，BacktoMenu回到主菜单

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
