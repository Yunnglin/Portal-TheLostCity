#include "Missile.h"
#include "Player.h"
#include "config.h"
#include "AnimationUtil.h"
#include "Monsters.h"
#include "Portal.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

bool Missile::init()
{
	auto sprite = Sprite::create("missile.png");
	this->bindSprite(sprite);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [&](PhysicsContact& contact) {
		auto scene = Director::getInstance()->getRunningScene();
		auto bodyA = contact.getShapeA()->getBody();
		auto bodyB = contact.getShapeB()->getBody();
		auto nodeA = bodyA->getNode();
		auto nodeB = bodyB->getNode();
		int A = bodyA->getCategoryBitmask();
		int B = bodyB->getCategoryBitmask();

		if (nodeA == NULL || nodeB == NULL)
			return true;

		if (A == MISSILE_CATEGORY || B == MISSILE_CATEGORY) {
			if (B == MISSILE_CATEGORY) {
				int t;
				t = A; A = B; B = t;
				Node* node;
				node = nodeA; nodeA = nodeB; nodeB = node;
				PhysicsBody* body;
				body = bodyA; bodyA = bodyB; bodyB = body;
			}
			auto v = ((Missile*)nodeA)->getPhysicsBody()->getVelocity().length();
			if (B == PLAYER_CATEGORY) {
				((Missile*)nodeA)->explode();
				((Player*)nodeB)->m_hp -=50;
			}
			else if ((B == WALL_CATEGORY) || (B == BARRIER_CATEGORY)) {
				((Missile*)nodeA)->explode();
			}
			else if (B == MONSTER_CATEGORY) {
				((Missile*)nodeA)->explode();
				((Monsters*)nodeB)->m_hp -=20;
			}
			else if (B == PORTAL_CATEGORY) {
				if ((strcmp(nodeB->getName().c_str(), "blue") == 0) && (scene->getChildByName("yellow") != NULL)) {
					switch (((Portal*)(scene->getChildByName("yellow")))->openDirection) {
					case Portal::Direction::Direction_Down:
						((Missile*)nodeA)->runAction(Place::create(Vec2(scene->getChildByName("yellow")->getPosition().x,
							scene->getChildByName("yellow")->getPosition().y - ((Missile*)nodeA)->getContentSize().height / 2 - scene->getChildByName("yellow")->getContentSize().height / 2 - 10)));
						((Missile*)nodeA)->getPhysicsBody()->setVelocity(Vec2(0, -v));
						break;
					case Portal::Direction::Direction_Left:
						((Missile*)nodeA)->runAction(Place::create(Vec2(scene->getChildByName("yellow")->getPosition().x - ((Missile*)nodeA)->getContentSize().width / 2 - scene->getChildByName("yellow")->getContentSize().width / 2 - 10,
							scene->getChildByName("yellow")->getPosition().y)));
						((Missile*)nodeA)->getPhysicsBody()->setVelocity(Vec2(-v, 0));
						break;
					case Portal::Direction::Direction_Right:
						((Missile*)nodeA)->runAction(Place::create(Vec2(scene->getChildByName("yellow")->getPosition().x + ((Missile*)nodeA)->getContentSize().width / 2 + scene->getChildByName("yellow")->getContentSize().width / 2 + 10,
							scene->getChildByName("yellow")->getPosition().y)));
						((Missile*)nodeA)->getPhysicsBody()->setVelocity(Vec2(v, 0));
						break;
					case Portal::Direction::Direction_Up:
						((Missile*)nodeA)->runAction(Place::create(Vec2(scene->getChildByName("yellow")->getPosition().x,
							scene->getChildByName("yellow")->getPosition().y + ((Missile*)nodeA)->getContentSize().height / 2 + scene->getChildByName("yellow")->getContentSize().height / 2 + 10)));
						((Missile*)nodeA)->getPhysicsBody()->setVelocity(Vec2(0, v));
						break;
					}

				}
				else if ((strcmp(nodeB->getName().c_str(), "yellow") == 0) && (scene->getChildByName("blue") != NULL)) {
					switch (((Portal*)(scene->getChildByName("yellow")))->openDirection) {
					case Portal::Direction::Direction_Down:
						((Missile*)nodeA)->runAction(Place::create(Vec2(scene->getChildByName("blue")->getPosition().x,
							scene->getChildByName("blue")->getPosition().y - ((Missile*)nodeA)->getContentSize().height / 2 - scene->getChildByName("blue")->getContentSize().height / 2 - 10)));
						((Missile*)nodeA)->getPhysicsBody()->setVelocity(Vec2(0, -v));
						break;
					case Portal::Direction::Direction_Left:
						((Missile*)nodeA)->runAction(Place::create(Vec2(scene->getChildByName("blue")->getPosition().x - ((Missile*)nodeA)->getContentSize().width / 2 - scene->getChildByName("blue")->getContentSize().width / 2 - 10,
							scene->getChildByName("blue")->getPosition().y)));
						((Missile*)nodeA)->getPhysicsBody()->setVelocity(Vec2(-v, 0));
						break;
					case Portal::Direction::Direction_Right:
						((Missile*)nodeA)->runAction(Place::create(Vec2(scene->getChildByName("blue")->getPosition().x + ((Missile*)nodeA)->getContentSize().width / 2 + scene->getChildByName("blue")->getContentSize().width / 2 + 10,
							scene->getChildByName("blue")->getPosition().y)));
						((Missile*)nodeA)->getPhysicsBody()->setVelocity(Vec2(v, 0));
						break;
					case Portal::Direction::Direction_Up:
						((Missile*)nodeA)->runAction(Place::create(Vec2(scene->getChildByName("blue")->getPosition().x,
							scene->getChildByName("blue")->getPosition().y + ((Missile*)nodeA)->getContentSize().height / 2 + scene->getChildByName("blue")->getContentSize().height / 2 + 10)));
						((Missile*)nodeA)->getPhysicsBody()->setVelocity(Vec2(0, v));
						break;
					}
				}
			}
		}
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	schedule(schedule_selector(Missile::missileUpdate), 0.5f);
	return true;
}


void Missile::bindSprite(Sprite* sprite)
{
	m_sprite = sprite;
	auto body = PhysicsBody::createBox(sprite->getContentSize() / 4.0 * 3);
	body->setGravityEnable(false);
	body->setDynamic(false);
	body->setRotationEnable(false);
	body->setCategoryBitmask(MISSILE_CATEGORY);
	body->setCollisionBitmask(MISSILE_COLLISION);
	body->setContactTestBitmask(MISSILE_CONTACT);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setRestitution(0);
	this->setPhysicsBody(body);
	this->addChild(m_sprite);
	this->setContentSize(m_sprite->getContentSize());
}

void Missile::setTarget(Player* target)
{
	m_target = target;
}

Player* Missile::getTarget()
{
	return m_target;
}

void Missile::missileUpdate(float dt)
{
	auto v = this->getPhysicsBody()->getVelocity().length();
	auto currentPos = this->getPosition();
	auto targetPos = m_target->getPosition();
	Vec2 vec = targetPos - currentPos;
	vec = vec.getNormalized();

	this->getPhysicsBody()->setVelocity(vec*v);

	float radians = acos(vec.x);
	float angle = CC_RADIANS_TO_DEGREES(radians);
	float degree = (vec.y > 0) ? (-angle) : angle;

	this->setRotation(degree);
}

void Missile::explode()
{

	SimpleAudioEngine::getInstance()->playEffect("boom.mp3");
	this->getPhysicsBody()->setVelocity(Vec2::ZERO);
	auto scene = Director::getInstance()->getRunningScene();
	Animate* animate = Animate::create(AnimationUtil::createWithSingleFrameName("explode", 0.05, 1));
	auto sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("explode1.png"));
	scene->addChild(sprite);
	sprite->setPosition(this->getPosition());
	sprite->setName("Texplode");
	auto func = [&]() {
		auto scene = Director::getInstance()->getRunningScene();
		scene->removeChildByName("Texplode");
	};
	CallFunc* callFunc = CallFunc::create(func);
	Sequence* seq = Sequence::create(DelayTime::create(0.5), callFunc, NULL);
	Action* action = Spawn::create(animate, seq, NULL);
	sprite->runAction(action);
	if(this != NULL)
		scene->removeChild(this);
}