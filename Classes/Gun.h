#ifndef _GUN_H_
#define _GUN_H_

#include "cocos2d.h"
#include "Entity.h"

class Portal;

class Gun:public cocos2d::Node{
public:
	CREATE_FUNC(Gun);
	virtual bool init();
	~Gun();
	void setSprite(cocos2d::Sprite* sprite);
	cocos2d::Sprite* getSprite();
	void shot(cocos2d::EventMouse::MouseButton button, cocos2d::Vec2 vec);
	bool standBy(cocos2d::EventMouse::MouseButton button);
	Portal* m_bluePortal;
	Portal* m_yellowPortal;
private:
	cocos2d::Sprite* m_sprite;
};




#endif 