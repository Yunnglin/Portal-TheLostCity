#include "TollgateScene.h"


Scene* TollgateScene::createScene() {
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}

bool TollgateScene::init() {
	if (!Layer::init()) { return false; }
	
	TMXTiledMap* map = TMXTiledMap::create("level01.tmx");

	this->addChild(map);
	addPlayer(map);
	return true;
}

void TollgateScene::addPlayer(TMXTiledMap* map) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//创建精灵
	Sprite* playerSprite = Sprite::create("player.png");
	//将精灵与玩家绑定
	Player* mPlayer = Player::create();
	mPlayer->bindSprite(playerSprite);
	//mPlayer->run();

	mPlayer->setTiledMap(map);
	//设置玩家坐标
	//mPlayer->setPosition(Point(100, visibleSize.height / 2));

	//加载对象层
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");
	//加载玩家坐标对象
	ValueMap playerPointMap = objGroup->getObject("PlayerPoint");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();
	mPlayer->setPosition(Point(playerX, playerY));
	//添加玩家到地图
	map->addChild(mPlayer);

	////创建玩家简单移动控制器
	//SimpleMoveController* simpleMoveControll = SimpleMoveController::create();
	////设置移动速度
	//simpleMoveControll->setiSpeed(2);
	////控制器有添加到场景中才能让update被调用
	//this->addChild(simpleMoveControll);
	////设置控制器到主角身上
	//mPlayer->setController(simpleMoveControll);

	/* ------------ 创建玩家移动控制器 -------------- */
	KeyboardController* keyboardController = KeyboardController::create();
	
	keyboardController->setSprite(playerSprite);
	/* 控制器要添加到场景中才能获得update事件 */
	this->addChild(keyboardController);

	/* 设置控制器到主角身上 */
	//mPlayer->setController(keyboardController);
}