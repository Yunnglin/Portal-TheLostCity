#pragma once
#ifndef _Entity_H_
#define _Entity_H_
#include "cocos2d.h"


USING_NS_CC;

class Entity:public Node
{
public:
	//绑定精灵对象
	virtual void bindSprite(Sprite* sprite);
	
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();
protected:
	Sprite * m_sprite;
	//Controller* m_controller;
};

#endif // !_Entity_H_