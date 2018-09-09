#ifndef _LEVEL_SCENE_H_
#define _LEVEL_SCENE_H_

#include "cocos2d.h"
#include "TimeCounter.h"
class NPC;
class PopWin;
class Player;
class Monsters;

class LevelScene:public cocos2d::Scene{
public:
	LevelScene();
	~LevelScene();
	CREATE_FUNC(LevelScene);
	virtual bool init();

	cocos2d::Point m_curPos;

	static cocos2d::Scene* createScene();
	void initMap(cocos2d::TMXTiledMap* map);
	virtual void update(float dt);
	void updateStart(float dt);
	void setPhysicsWorld(cocos2d::PhysicsWorld* phWorld);

	void setNPC(NPC* mNPC);
	void setDoor(NPC* door);
	void setDialog(PopWin* dialog);
	void goToNextLevel(Ref* pSend);

	PopWin* getDialog();
	void dialogLoad(Ref* pSend);
	void setPlayer(Player* player);
	void setMonsters(Monsters* monster);
	//¹Ø¿¨
	static int levelNum;

	

private:

	cocos2d::TMXTiledMap* m_tiledMap;
	cocos2d::TMXObjectGroup* m_objWall;
	cocos2d::PhysicsWorld* m_physicsWorld;
	void registeMouseListener();
	NPC* m_NPC;
	NPC* m_door;
	PopWin* m_dialog;
	Player* m_player;
	Node* m_cursor;
	Label* m_timeCount;
	TimeCounter* m_timeCounter;
	Monsters* m_monster;
};




#endif