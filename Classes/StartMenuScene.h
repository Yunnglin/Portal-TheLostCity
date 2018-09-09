#ifndef _START_MENU_SCENE_H_
#define _START_MENU_SCENE_H_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
using namespace cocostudio::timeline;
USING_NS_CC;
class StartMenuScene:public cocos2d::Scene{
public:
	CREATE_FUNC(StartMenuScene);
	virtual bool init();
	static cocos2d::Scene* createScene();
	
	void menuNewGameCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void menuContinueCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void menuLevelSelectCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void menuSettingsCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void menuHelpCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void menuAboutCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void menuExitCallBack(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);

};


#endif 