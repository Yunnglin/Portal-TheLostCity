#ifndef _KeyboardController_H_
#define  _KeyboardController_H_
#include "AnimationUtil.h"

#include "cocos2d.h"

USING_NS_CC;

class Player;
class KeyboardController :public Node{
public:
	CREATE_FUNC(KeyboardController);
	virtual bool init();
	
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);


	void setPlayer(Player* player);
private:
	Player * m_player;
};

#endif
