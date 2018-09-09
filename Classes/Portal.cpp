#include "Portal.h"
#include "config.h"


USING_NS_CC;

bool Portal::init()
{
	this->setTag(PORTAL_TAG);
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](PhysicsContact& contact) {
		
		auto bodyA = contact.getShapeA()->getBody();
		auto bodyB = contact.getShapeB()->getBody();
		int A = bodyA->getCategoryBitmask();
		int B = bodyB->getCategoryBitmask();
		auto nodeA = bodyA->getNode();
		auto nodeB = bodyB->getNode();
		if (nodeA == NULL || nodeB == NULL)
			return true;
		if ((A == PORTAL_CATEGORY) && (B == PORTAL_CATEGORY)) {
			bodyA->setVelocity(Vec2::ZERO);
			bodyB->setVelocity(Vec2::ZERO);
			Director::getInstance()->getRunningScene()->removeChild(bodyA->getNode());
			Director::getInstance()->getRunningScene()->removeChild(bodyB->getNode());
			nodeA->setScaleX(1);
			nodeA->setScaleY(1);
			nodeB->setScaleX(1);
			nodeB->setScaleY(1);
		}
		else if ((A == PORTAL_CATEGORY) && (B == WALL_CATEGORY)) {
			bodyA->setVelocity(Vec2::ZERO);
			((Portal*)nodeA)->openDirection = Portal::getDirection(nodeA->getPosition(), nodeB->getPosition(), nodeB->getContentSize());
			switch (((Portal*)nodeA)->openDirection) {
			case Portal::Direction::Direction_Down:
			case Portal::Direction::Direction_Up:
				nodeA->setScaleY(1 / 3.0);
				nodeA->setScaleX(2);
				break;
			case Portal::Direction::Direction_Left:
			case Portal::Direction::Direction_Right:
				nodeA->setScaleX(1 / 3.0);
				nodeA->setScaleY(2);
				break;
			}
		}
		else if ((A == WALL_CATEGORY) && (B == PORTAL_CATEGORY)) {
			bodyB->setVelocity(Vec2::ZERO);
			((Portal*)nodeB)->openDirection = Portal::getDirection(nodeB->getPosition(), nodeA->getPosition(), nodeA->getContentSize());
			switch (((Portal*)nodeB)->openDirection) {
			case Portal::Direction::Direction_Down:
			case Portal::Direction::Direction_Up:
				nodeB->setScaleY(1 / 3.0);
				nodeB->setScaleX(2);
				break;
			case Portal::Direction::Direction_Left:
			case Portal::Direction::Direction_Right:
				nodeB->setScaleX(1 / 3.0);
				nodeB->setScaleY(2);
				break;
			}
		}
		else if ((A == PORTAL_CATEGORY) && (B == BARRIER_CATEGORY)) {
			Director::getInstance()->getRunningScene()->removeChild(bodyA->getNode());
			nodeA->setScaleX(1);
			nodeA->setScaleY(1);
		}
		else if ((A == BARRIER_CATEGORY) && (B == PORTAL_CATEGORY)) {
			Director::getInstance()->getRunningScene()->removeChild(bodyB->getNode());
			nodeB->setScaleX(1);
			nodeB->setScaleY(1);
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void Portal::bindSprite(Sprite* sprite)
{
	m_sprite = sprite;
	m_sprite->setPosition(Vec2::ZERO);
	auto body = PhysicsBody::createCircle(m_sprite->getContentSize().width / 6);
	body->setDynamic(false);
	body->setRotationEnable(false);
	body->setGravityEnable(false);
	body->setCategoryBitmask(PORTAL_CATEGORY);
	body->setCollisionBitmask(PORTAL_COLLISION);
	body->setContactTestBitmask(PORTAL_CONTACT);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setRestitution(0);
	this->setPhysicsBody(body);
	this->addChild(m_sprite);
	this->setContentSize(m_sprite->getContentSize());
}

Portal::Direction Portal::getDirection(Vec2 portal, Vec2 wall, Size wSize)
{
	Vec2 vec = portal - wall;
	if ((vec.x > 0) && (vec.y > 0)) {
		if (vec.y >= (wSize.height / 2))
			return Portal::Direction::Direction_Up;
		else if (vec.x >= (wSize.width / 2))
			return Portal::Direction::Direction_Right;
	}
	else if ((vec.x < 0) && (vec.y > 0)) {
		if (vec.y >= (wSize.height / 2))
			return Portal::Direction::Direction_Up;
		else if (vec.x <= -(wSize.width / 2)) 
			return Portal::Direction::Direction_Left;
	}
	else if ((vec.x < 0) && (vec.y < 0)) {
		if (vec.y <= -(wSize.height / 2))
			return Portal::Direction::Direction_Down;
		else if (vec.x <= -(wSize.width / 2))
			return Portal::Direction::Direction_Left;
	}
	else if ((vec.x > 0) && (vec.y < 0)) {
		if (vec.y <= -(wSize.height / 2))
			return Portal::Direction::Direction_Down;
		else if (vec.x >= (wSize.width / 2)) 
			return Portal::Direction::Direction_Right;
	}

	return Portal::Direction::Direction_Down;
}

