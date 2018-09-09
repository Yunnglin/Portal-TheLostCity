#include "Monsters.h"
#include "Missile.h"
#include "config.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

bool Monsters::init()
{
	m_hp = 100;

	this->schedule(schedule_selector(Monsters::monsterUpdate), 3);

	return true;
}

void Monsters::bindSprite(Sprite* sprite)
{
	
	m_sprite = sprite;
	PhysicsBody* body = PhysicsBody::createBox(sprite->getContentSize());
	body->setDynamic(false);
	body->setRotationEnable(false);
	body->setGravityEnable(false);
	body->setCategoryBitmask(MONSTER_CATEGORY);
	body->setCollisionBitmask(MONSTER_COLLISION);
	body->setContactTestBitmask(MONSTER_CONTACT);
	body->getShape(0)->setRestitution(0);
	this->setPhysicsBody(body);
	this->addChild(m_sprite);
	this->setContentSize(m_sprite->getContentSize());

}

void Monsters::setTarget(Player* player)
{
	m_player = player;
}

void Monsters::monsterUpdate(float dt)
{
	launchMissile();
}

void Monsters::launchMissile()
{

	SimpleAudioEngine::getInstance()->playEffect("launch.mp3");
	Missile* missile = Missile::create();
	auto scene = Director::getInstance()->getRunningScene();
	if (scene->getPhysicsWorld() == NULL)
		return;
	scene->addChild(missile);
	missile->setRotation(180);
	missile->setPosition(Point(this->getPosition().x - this->getContentSize().width / 2 - missile->getContentSize().width / 2 - 5,
								this->getPosition().y));
	missile->getPhysicsBody()->setVelocity(Vec2(-200, 0));

	missile->setTarget(m_player);
}