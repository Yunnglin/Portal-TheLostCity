#include "LevelScene.h"
#include "Player.h"
#include "NPC.h"
#include "PopWin.h"
#include "KeyboardController.h"
#include "AnimationUtil.h"
#include "Gun.h"
#include "config.h"
#include "YouDiedScene.h"
#include "SimpleAudioEngine.h"
#include "Portal.h"
#include "Monsters.h"
#include "WinnerScene.h"

USING_NS_CC;
using namespace CocosDenshion;

LevelScene::LevelScene()
{
}


LevelScene::~LevelScene()
{
	NotificationCenter::getInstance()->removeObserver(this,"dialog");
	NotificationCenter::getInstance()->removeObserver(this, "exit");
}

int LevelScene::levelNum = 1;

Scene* LevelScene::createScene()
{


	LevelScene::levelNum = UserDefault::getInstance()->getIntegerForKey("PreLevel");
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //开启调试模式
	scene->getPhysicsWorld()->setGravity(Point(0, -1000));


	auto layer = LevelScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	Gun* gun = Gun::create();
	gun->setSprite(Sprite::create("gun.png"));
	layer->m_player->addGun(gun);

	layer->registeMouseListener();

	return scene;
}

bool LevelScene::init()
{
	if (!Scene::init())
		return false;
	//初始化鼠标位置
	m_curPos = Vec2::ZERO;
	
	//加载地图
	initMap(TMXTiledMap::create(StringUtils::format("res/map/level%d/level%d.tmx",levelNum,levelNum)));
	
	//订阅dialog消息
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LevelScene::dialogLoad), "dialog", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LevelScene::goToNextLevel), "exit", NULL);


	//添加计时器
	m_timeCounter = TimeCounter::create();
	this->addChild(m_timeCounter);
	//计时标签
	m_timeCount = Label::create("", "Terminal", 40);
	this->addChild(m_timeCount,10);
	m_timeCount->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, 700));

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("heroleft.plist", "heroleft.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("heroright.plist", "heroright.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("explode.plist", "explode.png");
	auto left = Animate::create(AnimationUtil::createWithSingleFrameName("heroleft", 0.2f, -1));
	auto right = Animate::create(AnimationUtil::createWithSingleFrameName("heroright", 0.2f, -1));


	Sprite* sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("heroright1.png"));
	
	//添加主角
	Player* player = Player::create();
	player->bindSprite(sprite);
	player->setRunAnimate(left, right);

	this->setPlayer(player);

	//添加怪物

	if (levelNum < 5) {
		m_monster = NULL;
	}
	if (levelNum == 5) {
		Monsters* monster = Monsters::create();
		monster->bindSprite(Sprite::create("monster.png"));
		this->setMonsters(monster);
	}
	
	//添加键盘监听
	KeyboardController* keycon = KeyboardController::create();
	keycon->setPlayer(player);
	this->addChild(keycon);


	//添加NPC
	NPC* npc = NPC::create();
	npc->setSprite(Sprite::create("npc1.png"),Sprite::create("NPC/isActive.png"));
	this->setNPC(npc);
	//添加出口
	NPC* door = NPC::create();
	door->setSprite(Sprite::create("door.png"), Sprite::create("NPC/F.png"));
	this->setDoor(door);


	//add dialog
	Label* label = Label::create("", "simhei.ttf", 25);
	PopWin* dialog = PopWin::createWin("res/NPC/dialog1.png");
	dialog->setLabel(label, "language.xml", StringUtils::format("string%d",levelNum));
	this->setDialog(dialog);

	
	//更改鼠标样式
	auto cursor = Sprite::create("cursor.png");
	m_cursor = Node::create();
	m_cursor->addChild(cursor);
	this->addChild(this->m_cursor, 100);

	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseMove = [&](EventMouse* evt) {
		Point mouse = evt->getLocationInView();
		/*Point mouse = Director::getInstance()->convertToGL(pos);*/
		this->m_cursor->setPosition(mouse);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);


	//音效
	SimpleAudioEngine::getInstance()->preloadEffect("shot.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("die.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("portal.mp3");

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(LevelScene::updateStart), 0.0);
	
	this->scheduleUpdate();


	return true;
}

void LevelScene::setPhysicsWorld(PhysicsWorld* phWorld)
{
	m_physicsWorld = phWorld;
}

void LevelScene::setNPC(NPC* mNPC)
{
	m_NPC = mNPC;

	TMXObjectGroup* objGroup = m_tiledMap->getObjectGroup("Objects");
	ValueMap npcPos = objGroup->getObject("npcPos");
	m_NPC->setPosition(Point(npcPos.at("x").asFloat(), npcPos.at("y").asFloat()));
	this->addChild(m_NPC);
}

void LevelScene::setDoor(NPC* door) {
	m_door = door;
	TMXObjectGroup* objGroup = m_tiledMap->getObjectGroup("Objects");
	ValueMap npcPos = objGroup->getObject("exitPos");
	m_door->setPosition(Point(npcPos.at("x").asFloat(), npcPos.at("y").asFloat()));
	this->addChild(m_door);
}

void LevelScene::setPlayer(Player* player)
{
	m_player = player;
	TMXObjectGroup* objGroup = m_tiledMap->getObjectGroup("Objects");
	ValueMap pos = objGroup->getObject("InitialPos");
	float x = pos.at("x").asFloat();
	float y = pos.at("y").asFloat();

	m_player->setPosition(Point(x, y));
	this->addChild(m_player);
}

void LevelScene::setMonsters(Monsters* monster) {
	m_monster = monster;
	TMXObjectGroup* objGroup = m_tiledMap->getObjectGroup("Objects");
	ValueMap pos = objGroup->getObject("monsterPos");
	float x = pos.at("x").asFloat();
	float y = pos.at("y").asFloat();

	m_monster->setPosition(Point(x, y));

	m_monster->setTarget(m_player);
	this->addChild(m_monster);
}

void LevelScene::setDialog(PopWin* dialog)
{
	m_dialog = dialog;
	m_dialog->setPosition(Point(m_dialog->getContentSize().width / 2, m_dialog->getContentSize().height / 2));
	m_dialog->setVisible(m_dialog->isActive());
	this->addChild(m_dialog,5);
}

PopWin* LevelScene::getDialog()
{
	return m_dialog;
}

void LevelScene::dialogLoad(Ref* pSender)
{
	if (m_dialog->isActive()) {
			m_dialog->setVisible(false);
			m_dialog->setIsActive(false);
			m_dialog->labelEnd();
		}
	else {
		if (m_NPC->isAccessible()) {
				m_dialog->setIsActive(true);
				m_dialog->setVisible(true);
				m_dialog->labelStart();
		}
	}

}

void LevelScene::goToNextLevel(Ref* pSender) {
	
	if (m_door->isAccessible()) {
		if (levelNum < 5) {
			UserDefault::getInstance()->setIntegerForKey("PreLevel", levelNum + 1);
			UserDefault::getInstance()->flush();
			if (UserDefault::getInstance()->getIntegerForKey("HeighLevel") < (levelNum + 1)) {
				UserDefault::getInstance()->setIntegerForKey("HeighLevel", levelNum + 1);
				UserDefault::getInstance()->flush();
			}
			SimpleAudioEngine::getInstance()->playEffect("portal.mp3");
			Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, LevelScene::createScene()));
		}
		else {
			SimpleAudioEngine::getInstance()->playEffect("portal.mp3");
			Director::getInstance()->replaceScene(TransitionSplitCols::create(1.2f, WinnerScene::createScene()));
		}
	}
	
}

void LevelScene::updateStart(float dt)
{
	m_physicsWorld->setAutoStep(false);
	m_physicsWorld->setFixedUpdateRate(180);
	//开始计时
	m_timeCounter->start();
}

void LevelScene::update(float dt)
{
	for (int i = 0; i < 3; i++) {
		m_physicsWorld->step(1 / 180.0f);
	}

	//计时标签
	m_timeCount->setString(StringUtils::format("%d min : %d sec ", m_timeCounter->getMin(), m_timeCounter->getSec()));
	//时间到后GameOver
	if (m_timeCounter->getMin() < 0) {
		Director::getInstance()->replaceScene(YouDiedScene::createScene());
	}


	//检测人物是否到达NPC旁边
	auto size = m_NPC->getContentSize() * 3;
	auto npcPos = m_NPC->getPosition();
	if ((m_player->getPosition().x > npcPos.x - size.width / 2) && (m_player->getPosition().x < npcPos.x + size.width / 2)
		&& (m_player->getPosition().y < npcPos.y + size.height / 2) && (m_player->getPosition().y < npcPos.y + size.height / 2)) {
		m_NPC->setIsAccessible(true);
	}
	else {
		m_NPC->setIsAccessible(false);
	}
	

	//检测人物是否到达门
	auto doorSize = m_door->getContentSize();
	auto doorPos = m_door->getPosition();
	if ((m_player->getPosition().x > doorPos.x - doorSize.width / 2) && (m_player->getPosition().x < doorPos.x + doorSize.width / 2)
		&& (m_player->getPosition().y < doorPos.y + doorSize.height / 2) && (m_player->getPosition().y < doorPos.y + doorSize.height / 2)) {
		m_door->setIsAccessible(true);
	}
	else {
		m_door->setIsAccessible(false);
	}
	
	
	//判断人物是否死亡
	//判断人物是否掉出屏幕
	Point pos = m_player->getPosition();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if ((pos.x <= visibleSize.width&&pos.x >= 0 && pos.y <= visibleSize.height&&pos.y >= 0)) {

	}
	else {
		SimpleAudioEngine::getInstance()->playEffect("die.mp3");
		Director::getInstance()->replaceScene(YouDiedScene::createScene());
	}

	if ((m_player->m_hp) <= 0) {
		SimpleAudioEngine::getInstance()->playEffect("die.mp3");
		Director::getInstance()->replaceScene(YouDiedScene::createScene());
	}


		if (m_monster != NULL) {
		if (m_monster->m_hp <= 0) {
			this->removeChild(m_monster);
			}
		}



	//判断门是否出屏幕
	auto scene = Director::getInstance()->getRunningScene();
	if (scene->getChildByName("blue") != NULL ) {
		Point portalBlue = m_player->getGun()->m_bluePortal->getPosition();
		if (portalBlue.x > visibleSize.width || portalBlue.x < 0 || portalBlue.y > visibleSize.height || portalBlue.y < 0) {
			scene->removeChildByName("blue");
		}
		
	}
	if (scene->getChildByName("yellow") != NULL) {
		Point portalYellow = m_player->getGun()->m_yellowPortal->getPosition();
		if (portalYellow.x > visibleSize.width || portalYellow.x < 0 || portalYellow.y > visibleSize.height || portalYellow.y < 0) {
			scene->removeChildByName("yellow");
		}
	}
}


void LevelScene::initMap(TMXTiledMap* map)
{
	auto bgImage = Sprite::create("res/map/bgImage.jpg");
	bgImage->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height/2));
	this->addChild(bgImage);

	this->m_tiledMap = map;
	this->m_objWall = m_tiledMap->getObjectGroup("Objects");

	auto objects = m_objWall->getObjects();

	for (auto obj : objects) {
		auto dict = obj.asValueMap();
		if (dict.size() == 0)
			continue;
		if (dict.find("wall") != dict.end()) {
			auto body = PhysicsBody::createBox(Size(dict.at("width").asFloat(), dict.at("height").asFloat()));
			body->setContactTestBitmask(BARRIER_CONTACT);
			body->setCollisionBitmask(BARRIER_COLLISION);
			body->setCategoryBitmask(BARRIER_CATEGORY);
			body->setDynamic(false);
			body->getShape(0)->setFriction(0);
			body->getShape(0)->setRestitution(0);
			body->setGravityEnable(false);
			

			auto node = Node::create();
			node->setPosition(Point(dict.at("x").asFloat() + dict.at("width").asFloat() / 2, dict.at("y").asFloat() + dict.at("height").asFloat() / 2));
			node->addComponent(body);
			node->setContentSize(Size(dict.at("width").asFloat(), dict.at("height").asFloat()));
			this->addChild(node);
		}
		if (dict.find("barrier") != dict.end()) {
			auto body = PhysicsBody::createBox(Size(dict.at("width").asFloat(), dict.at("height").asFloat()));
			body->setContactTestBitmask(WALL_CONTACT);
			body->setCollisionBitmask(WALL_COLLISION);
			body->setCategoryBitmask(WALL_CATEGORY);
			body->setDynamic(false);
			body->getShape(0)->setFriction(0);
			body->getShape(0)->setRestitution(0);
			body->setGravityEnable(false);


			auto node = Node::create();
			node->setPosition(Point(dict.at("x").asFloat() + dict.at("width").asFloat() / 2, dict.at("y").asFloat() + dict.at("height").asFloat() / 2));
			node->addComponent(body);
			node->setContentSize(Size(dict.at("width").asFloat(), dict.at("height").asFloat()));
			this->addChild(node);
		}
	}

	this->addChild(m_tiledMap);
}

void LevelScene::registeMouseListener()
{
	auto listener = EventListenerMouse::create();

	listener->onMouseMove = [&](EventMouse* evt) {
		Vec2 cursorPos = evt->getLocationInView();
		this->m_curPos = cursorPos;
		Vec2 gunPos = this->m_player->getPosition();
		Vec2 vec = cursorPos - gunPos;
		

		float radians = acos(vec.x / vec.length());
		float angle = CC_RADIANS_TO_DEGREES(radians);
		float degrees = (vec.y > 0) ? (-angle) : angle;
		this->m_player->getGun()->setRotation(degrees);
	};
	listener->onMouseDown = [&](EventMouse* evt) {
		EventMouse::MouseButton button = evt->getMouseButton();
		switch (button) {
		case EventMouse::MouseButton::BUTTON_LEFT:
			this->m_player->getGun()->standBy(button);
			break;
		case EventMouse::MouseButton::BUTTON_RIGHT:
			this->m_player->getGun()->standBy(button);
			break;
		}
	};
	listener->onMouseUp = [&](EventMouse* evt) {
		Vec2 gunPos = m_player->getPosition();
		Vec2 cursorPos = this->m_curPos;
		Vec2 vec = cursorPos - gunPos;
		EventMouse::MouseButton button = evt->getMouseButton();
		switch (button) {
		case EventMouse::MouseButton::BUTTON_LEFT:
			m_player->getGun()->shot(button, vec);
			SimpleAudioEngine::getInstance()->playEffect("shot.mp3");
			break;
		case EventMouse::MouseButton::BUTTON_RIGHT:
			m_player->getGun()->shot(button, vec);
			SimpleAudioEngine::getInstance()->playEffect("shot.mp3");
			
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
