#include "Gun.h"
#include "Portal.h"
#include "config.h"

USING_NS_CC;

Gun::~Gun() {
	m_bluePortal->release();
	m_yellowPortal->release();
}


bool Gun::init()
{
	m_bluePortal = Portal::create();
	m_bluePortal->bindSprite(Sprite::create("portalblue.png"));
	m_bluePortal->setName("blue");
	m_bluePortal->retain();
	m_yellowPortal = Portal::create();
	m_yellowPortal->bindSprite(Sprite::create("portalyellow.png"));
	m_yellowPortal->setName("yellow");
	m_yellowPortal->retain();
	return true;
}

void Gun::setSprite(Sprite* sprite)
{
	m_sprite = sprite;
	this->addChild(m_sprite);
	this->setContentSize(m_sprite->getContentSize());
}

Sprite* Gun::getSprite()
{
	return m_sprite;
}

void Gun::shot(EventMouse::MouseButton button, Vec2 vec)
{
	auto scene = Director::getInstance()->getRunningScene();
	if (getChildByName("TSprite") == NULL) {
		return;
	}
	auto pos = Node::convertToWorldSpace(this->getChildByName("TSprite")->getPosition());
	Vec2 v = vec.getNormalized() * 1500;
	Portal* portal = NULL;
	switch (button) {
	case EventMouse::MouseButton::BUTTON_LEFT:
		this->removeChildByName("TSprite");
		if (m_bluePortal->getParent() == NULL) {
			scene->addChild(m_bluePortal);
		}
		m_bluePortal->setScaleX(1);
		m_bluePortal->setScaleY(1);
		m_bluePortal->setPosition(pos);
		portal = m_bluePortal;
		break;
	case EventMouse::MouseButton::BUTTON_RIGHT:
		this->removeChildByName("TSprite");
		if (m_yellowPortal->getParent() == NULL) {
			scene->addChild(m_yellowPortal);
		}
		m_yellowPortal->setScaleX(1);
		m_yellowPortal->setScaleY(1);
		m_yellowPortal->setPosition(pos);
		portal = m_yellowPortal;
		break;
	default:
		return;
	}

	portal->getPhysicsBody()->setVelocity(v);
}

bool Gun::standBy(EventMouse::MouseButton button)
{
	auto blue = Sprite::create("portalblue.png");
	auto yellow = Sprite::create("portalyellow.png");
	switch (button) {
	case EventMouse::MouseButton::BUTTON_LEFT:
		blue->setName("TSprite");
		this->addChild(blue);
		blue->setPosition(Vec2(this->getContentSize().width / 6 * 5, this->getContentSize().height / 2.5));
		break;
	case EventMouse::MouseButton::BUTTON_RIGHT:
		yellow->setName("TSprite");
		this->addChild(yellow);
		yellow->setPosition(Vec2(this->getContentSize().width / 6 * 5, this->getContentSize().height / 2.5));
		break;
	}

	return true;
}