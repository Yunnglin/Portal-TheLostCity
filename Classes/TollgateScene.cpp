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
	//��������
	Sprite* playerSprite = Sprite::create("player.png");
	//����������Ұ�
	Player* mPlayer = Player::create();
	mPlayer->bindSprite(playerSprite);
	//mPlayer->run();

	mPlayer->setTiledMap(map);
	//�����������
	//mPlayer->setPosition(Point(100, visibleSize.height / 2));

	//���ض����
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");
	//��������������
	ValueMap playerPointMap = objGroup->getObject("PlayerPoint");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();
	mPlayer->setPosition(Point(playerX, playerY));
	//�����ҵ���ͼ
	map->addChild(mPlayer);

	////������Ҽ��ƶ�������
	//SimpleMoveController* simpleMoveControll = SimpleMoveController::create();
	////�����ƶ��ٶ�
	//simpleMoveControll->setiSpeed(2);
	////����������ӵ������в�����update������
	//this->addChild(simpleMoveControll);
	////���ÿ���������������
	//mPlayer->setController(simpleMoveControll);

	/* ------------ ��������ƶ������� -------------- */
	KeyboardController* keyboardController = KeyboardController::create();
	
	keyboardController->setSprite(playerSprite);
	/* ������Ҫ��ӵ������в��ܻ��update�¼� */
	this->addChild(keyboardController);

	/* ���ÿ��������������� */
	//mPlayer->setController(keyboardController);
}