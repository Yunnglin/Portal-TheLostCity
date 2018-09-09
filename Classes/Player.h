#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "Entity.h"


class Gun;

class Player:public Entity{
public:
	CREATE_FUNC(Player);
	virtual bool init();
	void playerUpdate(float dt);
	
	~Player();

	virtual void bindSprite(cocos2d::Sprite* sprite);
	void setRunAnimate(cocos2d::Animate* left, cocos2d::Animate* right);
	bool getXDirection();
	void setXDirection(int direction);
	void jump();
	void playLeftAnimate();
	void playRightAnimate();
	void stopRunning();
	void addGun(Gun* gun);
	Gun* getGun();
	int headToward;
	cocos2d::Sprite* getSprite();
	int m_hp;


private:
	int m_direction;
	bool m_isJumping;
	bool m_isPlayingAnimation;
	cocos2d::Animate* m_leftAnimate;
	cocos2d::Animate* m_rightAnimate;
	Gun* m_gun;
	
};

#endif 