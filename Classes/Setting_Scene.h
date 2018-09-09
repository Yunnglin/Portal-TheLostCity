#ifndef __Setting_Scene_H__
#define __Setting_Scene_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "cocos\ui\CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace cocostudio::timeline;
USING_NS_CC;
using namespace cocos2d::ui;
class Setting_Scene :public cocos2d::Scene
{
	int isTouched;

public:
	static int audioID;
	CREATE_FUNC(Setting_Scene);
	virtual bool init();
	static cocos2d::Scene* createScene();
	//复写框
	void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
	//滑动条2，音乐音量
    void sliderCallback2(cocos2d::Ref * ref, cocos2d::ui::Slider::EventType type);
	//按钮，返回到主菜单
	void buttonMainMenuCallBack(Ref *ref, cocos2d::ui::TouchEventType type);

};


#endif
