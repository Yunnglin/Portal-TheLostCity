#pragma once
#ifndef _TollgateScene_H_
#define _TollgateScene_H_
#include "Player.h"
#include "cocos2d.h"
#include "KeyboardController.h"
USING_NS_CC;
class TollgateScene: public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
	void addPlayer(TMXTiledMap* map);
};

#endif