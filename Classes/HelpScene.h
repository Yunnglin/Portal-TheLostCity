#ifndef __HELPSCENE_H__
#define __HELPSCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
USING_NS_CC;

class HelpScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelpScene);
	void BacktoMenuClick(Ref* pSender, TouchEventType type);
};

#endif