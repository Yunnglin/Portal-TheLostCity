#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "cocos2d.h"
#include "Entity.h"

class Player;

class Missile :public Entity {
public:
	CREATE_FUNC(Missile);
	virtual bool init();
	virtual void bindSprite(cocos2d::Sprite* sprite);
	void missileUpdate(float dt);
	void setTarget(Player* target);
	Player* getTarget();
private:
	Player* m_target;
	void explode();
};

#endif 