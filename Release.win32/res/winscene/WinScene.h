#ifndef __WINSCENE_H__
#define __WINSCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

class WinScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(WinScene);
	void BacktoMenuClick(Ref* pSender,cocos2d::ui::TouchEventType type);
};	

#endif