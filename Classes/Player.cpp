#include "Player.h"
#include "Gun.h"
#include "LevelScene.h"
#include "config.h"
#include "Portal.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Player:: ~Player() {
	m_leftAnimate->release();
	m_rightAnimate->release();
}

bool Player::init()
{
	m_isJumping = false;
	m_isPlayingAnimation = false;
	m_direction = 0;
	headToward = 1;

	m_hp = 100;
	this->setTag(PLAYER_TAG);
	this->schedule(schedule_selector(Player::playerUpdate), 0.02f);

	return true;
}

void Player::bindSprite(Sprite* sprite)
{

	m_sprite = sprite;
	PhysicsBody* body = PhysicsBody::createBox(m_sprite->getContentSize());
	body->setDynamic(true);
	body->setRotationEnable(false);
	body->setVelocityLimit(1500);
	body->setCategoryBitmask(PLAYER_CATEGORY);
	body->setCollisionBitmask(PLAYER_COLLISION);
	body->setContactTestBitmask(PLAYER_CONTACT);
	body->getShape(0)->setRestitution(0);
	this->setPhysicsBody(body);
	this->addChild(m_sprite);
	this->setContentSize(m_sprite->getContentSize());
}

Sprite* Player::getSprite()
{
	return m_sprite;
}

//方向取值为-1, 0, 1  分别代表正向 静止 负向
void Player::setXDirection(int direction)
{
	m_direction = direction;
}

bool Player::getXDirection()
{
	return m_direction;
}

void Player::jump()
{
	if (m_isJumping)
		return;

	m_sprite->stopAllActions();
	m_isPlayingAnimation = false;

	Point v = this->getPhysicsBody()->getVelocity();
	this->getPhysicsBody()->setVelocity(Point(v.x, 320));
	m_isJumping = true;
}


void Player::playerUpdate(float dt)
{
	Vec2 v = this->getPhysicsBody()->getVelocity();

	if (std::fabs(v.y - 0) < 0.000001) {
		m_isJumping = false;
		if ((m_isPlayingAnimation == false) && m_direction != 0) {
			if (m_direction > 0) {
				m_sprite->runAction(m_rightAnimate);
				m_isPlayingAnimation = true;
			}
			else {
				m_sprite->runAction(m_leftAnimate);
				m_isPlayingAnimation = true;
			}
		}
	}
	else
		m_isJumping = true;

	if (!m_isJumping) {
		if (m_direction == 0) {
			v.x = 0;
		}
		else if ((v.x == 0) || (!((v.x > 0) ^ (m_direction > 0)))) {
			v.x = m_direction * 100.0f;
		}
		else
			v.x = 0;
	}
	else {
		if ((v.x == 0) && (m_direction != 0)) {
			v.x = m_direction * 100.0f;			
		}
		else if ((v.x > 0) ^ (m_direction > 0)) {
			v.x += m_direction * 50.0f;
		}
	}

	this->getPhysicsBody()->setVelocity(v);
	
}

void Player::setRunAnimate(Animate* left, Animate* right)
{
	m_leftAnimate = left;
	m_rightAnimate = right;
	m_leftAnimate->retain();
	m_rightAnimate->retain();
}

void Player::playLeftAnimate()
{
	if (m_leftAnimate == NULL)
		return;
	m_sprite->runAction(m_leftAnimate);
	m_isPlayingAnimation = true;
}

void Player::playRightAnimate()
{
	if (m_rightAnimate == NULL)
		return;
	m_sprite->runAction(m_rightAnimate);
	m_isPlayingAnimation = true;
}

void Player::stopRunning()
{
	m_sprite->stopAllActions();
	m_isPlayingAnimation = false;
}

void Player::addGun(Gun* gun)
{
	m_gun = gun;
	m_gun->setAnchorPoint(Point(-0.29, 0.45));
	m_gun->setPosition(Point(0, this->getContentSize().height / 4));
	this->addChild(m_gun);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [&](PhysicsContact& contact) {
		auto scene = Director::getInstance()->getRunningScene();
		auto nodeA = contact.getShapeA()->getBody()->getNode();
		auto nodeB = contact.getShapeB()->getBody()->getNode();
		auto v = this->getPhysicsBody()->getVelocity().length();
		if (nodeA == NULL || nodeB == NULL)
			return true;
		if (nodeA->getTag() == PLAYER_TAG) {
			if (nodeB->getTag() == PORTAL_TAG) {
				//effect
				SimpleAudioEngine::getInstance()->playEffect("transport.mp3");
				if ((strcmp(nodeB->getName().c_str(), "blue") == 0) && (scene->getChildByName("yellow") != NULL)) {
					switch (this->getGun()->m_yellowPortal->openDirection) {
					case Portal::Direction::Direction_Down:
						this->runAction(Place::create(Vec2(this->getGun()->m_yellowPortal->getPosition().x,
							this->getGun()->m_yellowPortal->getPosition().y - this->getContentSize().height / 2  - this->getGun()->m_yellowPortal->getContentSize().height / 6 - 10)));
						this->getPhysicsBody()->setVelocity(Vec2(0, -v));
						break;
					case Portal::Direction::Direction_Left:
						this->runAction(Place::create(Vec2(this->getGun()->m_yellowPortal->getPosition().x - this->getContentSize().width / 2 - this->getGun()->m_yellowPortal->getContentSize().width / 6 - 10,
							this->getGun()->m_yellowPortal->getPosition().y )));
						this->getPhysicsBody()->setVelocity(Vec2(-v, 0));
						break;
					case Portal::Direction::Direction_Right:
						this->runAction(Place::create(Vec2(this->getGun()->m_yellowPortal->getPosition().x + this->getContentSize().width / 2 + this->getGun()->m_yellowPortal->getContentSize().width / 6 + 10,
							this->getGun()->m_yellowPortal->getPosition().y)));
						this->getPhysicsBody()->setVelocity(Vec2(v, 0));
						break;
					case Portal::Direction::Direction_Up:
						this->runAction(Place::create(Vec2(this->getGun()->m_yellowPortal->getPosition().x,
							this->getGun()->m_yellowPortal->getPosition().y + this->getContentSize().height / 2 + this->getGun()->m_yellowPortal->getContentSize().height / 6 + 10)));
						this->getPhysicsBody()->setVelocity(Vec2(0, v));
						break;
					}
					
				}
				else if ((strcmp(nodeB->getName().c_str(), "yellow") == 0) && (scene->getChildByName("blue") != NULL)) {
					switch (this->getGun()->m_bluePortal->openDirection) {
					case Portal::Direction::Direction_Down:
						this->runAction(Place::create(Vec2(this->getGun()->m_bluePortal->getPosition().x,
							this->getGun()->m_bluePortal->getPosition().y - this->getContentSize().height / 2 - this->getGun()->m_bluePortal->getContentSize().height / 6 - 10)));
						this->getPhysicsBody()->setVelocity(Vec2(0, -v));
						break;
					case Portal::Direction::Direction_Left:
						this->runAction(Place::create(Vec2(this->getGun()->m_bluePortal->getPosition().x - this->getContentSize().width / 2 - this->getGun()->m_bluePortal->getContentSize().width / 6 - 10,
							this->getGun()->m_bluePortal->getPosition().y)));
						this->getPhysicsBody()->setVelocity(Vec2(-v, 0));
						break;
					case Portal::Direction::Direction_Right:
						this->runAction(Place::create(Vec2(this->getGun()->m_bluePortal->getPosition().x + this->getContentSize().width / 2 + this->getGun()->m_bluePortal->getContentSize().width / 6 + 10,
							this->getGun()->m_bluePortal->getPosition().y)));
						this->getPhysicsBody()->setVelocity(Vec2(v, 0));
						break;
					case Portal::Direction::Direction_Up:
						this->runAction(Place::create(Vec2(this->getGun()->m_bluePortal->getPosition().x,
							this->getGun()->m_bluePortal->getPosition().y + this->getContentSize().height / 2 + this->getGun()->m_bluePortal->getContentSize().height / 6 + 10)));
						this->getPhysicsBody()->setVelocity(Vec2(0, v));
						break;
					}
				}
			}
		}
		else if (nodeB->getTag() == PLAYER_TAG) {
			if (nodeA->getTag() == PORTAL_TAG) {
				//effect
				SimpleAudioEngine::getInstance()->playEffect("transport.mp3");
				if ((strcmp(nodeA->getName().c_str(), "blue") == 0) && (scene->getChildByName("yellow") != NULL)) {
					switch (this->getGun()->m_yellowPortal->openDirection) {
					case Portal::Direction::Direction_Down:
						this->runAction(Place::create(Vec2(this->getGun()->m_yellowPortal->getPosition().x,
							this->getGun()->m_yellowPortal->getPosition().y - this->getContentSize().height / 2 - this->getGun()->m_yellowPortal->getContentSize().height / 6 - 10)));
						this->getPhysicsBody()->setVelocity(Vec2(0, -v));
						break;
					case Portal::Direction::Direction_Left:
						this->runAction(Place::create(Vec2(this->getGun()->m_yellowPortal->getPosition().x - this->getContentSize().width / 2 - this->getGun()->m_yellowPortal->getContentSize().width / 6 - 10,
							this->getGun()->m_yellowPortal->getPosition().y)));
						this->getPhysicsBody()->setVelocity(Vec2(-v, 0));
						break;
					case Portal::Direction::Direction_Right:
						this->runAction(Place::create(Vec2(this->getGun()->m_yellowPortal->getPosition().x + this->getContentSize().width / 2 + this->getGun()->m_yellowPortal->getContentSize().width / 6 + 10,
							this->getGun()->m_yellowPortal->getPosition().y)));
						this->getPhysicsBody()->setVelocity(Vec2(v, 0));
						break;
					case Portal::Direction::Direction_Up:
						this->runAction(Place::create(Vec2(this->getGun()->m_yellowPortal->getPosition().x,
							this->getGun()->m_yellowPortal->getPosition().y + this->getContentSize().height / 2 + this->getGun()->m_yellowPortal->getContentSize().height / 6 + 10)));
						this->getPhysicsBody()->setVelocity(Vec2(0, v));
						break;
					}
				}
				else if ((strcmp(nodeA->getName().c_str(), "yellow") == 0) && (scene->getChildByName("blue") != NULL)) {
					switch (this->getGun()->m_bluePortal->openDirection) {
					case Portal::Direction::Direction_Down:
						this->runAction(Place::create(Vec2(this->getGun()->m_bluePortal->getPosition().x,
							this->getGun()->m_bluePortal->getPosition().y - this->getContentSize().height / 2 - this->getGun()->m_bluePortal->getContentSize().height / 6 - 10)));
						this->getPhysicsBody()->setVelocity(Vec2(0, -v));
						break;
					case Portal::Direction::Direction_Left:
						this->runAction(Place::create(Vec2(this->getGun()->m_bluePortal->getPosition().x - this->getContentSize().width / 2 - this->getGun()->m_bluePortal->getContentSize().width / 6 - 10,
							this->getGun()->m_bluePortal->getPosition().y)));
						this->getPhysicsBody()->setVelocity(Vec2(-v, 0));
						break;
					case Portal::Direction::Direction_Right:
						this->runAction(Place::create(Vec2(this->getGun()->m_bluePortal->getPosition().x + this->getContentSize().width / 2 + this->getGun()->m_bluePortal->getContentSize().width / 6 + 10,
							this->getGun()->m_bluePortal->getPosition().y)));
						this->getPhysicsBody()->setVelocity(Vec2(v, 0));
						break;
					case Portal::Direction::Direction_Up:
						this->runAction(Place::create(Vec2(this->getGun()->m_bluePortal->getPosition().x,
							this->getGun()->m_bluePortal->getPosition().y + this->getContentSize().height / 2 + this->getGun()->m_bluePortal->getContentSize().height / 6 + 10)));
						this->getPhysicsBody()->setVelocity(Vec2(0, v));
						break;
					}
				}
			}
		}
		

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

Gun* Player::getGun()
{
	return m_gun;
	
}

