#ifndef _MONSTERS_H_
#define _MONSTERS_H_

#include "cocos2d.h"
#include "Entity.h"

class Missile;
class Player;

class Monsters:public Entity{
public:
	CREATE_FUNC(Monsters);
	virtual bool init();
	virtual void bindSprite(cocos2d::Sprite* sprite);

	int m_hp;

	void monsterUpdate(float dt);
	void launchMissile();
	void setTarget(Player* player);
private:
	Player * m_player;
};





#endif 