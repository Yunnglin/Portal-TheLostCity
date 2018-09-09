#ifndef __WinnerScene_H__
#define __WinnerScene_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
class WinnerScene:public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(WinnerScene);
	void BacktoMenuClick(Ref* pSender, cocos2d::ui::TouchEventType type);
};

#endif