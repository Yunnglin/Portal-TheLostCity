#ifndef _PORTAL_H_
#define _PORTAL_H_

#include "cocos2d.h"
#include "Entity.h"


class Portal :public Entity {
public:
	enum Portal_Direction {
		Direction_Left,
		Direction_Right,
		Direction_Up,
		Direction_Down
	} typedef Direction;

	CREATE_FUNC(Portal);
	virtual bool init();

	virtual void bindSprite(cocos2d::Sprite* sprite);
	Direction openDirection;
	
	static Direction getDirection(cocos2d::Vec2 portal, cocos2d::Vec2 wall, cocos2d::Size wSize);
};



#endif 