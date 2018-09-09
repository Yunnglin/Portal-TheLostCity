#ifndef _NPC_H_
#define _NPC_H_

#include "cocos2d.h"

class Player;
class PopWin;
class NPC :public cocos2d::Node{
public:
	CREATE_FUNC(NPC);
	virtual bool init();
	virtual void update(float dt);

	void setSprite(cocos2d::Sprite* sprite,cocos2d::Sprite* isAcitve);
	bool isAccessible();
	void setIsAccessible(bool bAccess);
private:
	cocos2d::Sprite * m_sprite;
	bool m_isAccessible;
};



#endif 