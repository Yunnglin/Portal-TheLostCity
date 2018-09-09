#ifndef __PauseScene_H__
#define __PauseScene_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"



USING_NS_CC;
using namespace cocos2d::ui;

class PauseScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);

	void onClick1(Ref*, TouchEventType type);
	void onClick2(Ref*, TouchEventType type);
	void onClick3(Ref*, TouchEventType type);
	void onClick4(Ref*, TouchEventType type);
	void onClick5(Ref*, TouchEventType type);
};

#endif 

