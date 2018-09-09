#ifndef __ENDGAME_H__
#define __ENDGAME_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "cocos\ui\CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class EndGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void StartCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	//void StartGame::showFont(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(EndGame);
};

#endif // __HELLOWORLD_SCENE_H__
