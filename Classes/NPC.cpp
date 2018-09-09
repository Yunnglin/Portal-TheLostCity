#include "NPC.h"
#include "PopWin.h"
USING_NS_CC;

bool NPC::init()
{
	m_sprite = NULL;
	m_isAccessible = false;

	this->scheduleUpdate();

	return true;
}

void NPC::update(float dt)
{
	if (!m_sprite)
		return;

	this->getChildByName("isActive")->setVisible(m_isAccessible);
}

void NPC::setSprite(Sprite* sprite, Sprite* isActive)
{
	m_sprite = sprite;
	this->setContentSize(m_sprite->getContentSize());
	this->addChild(sprite);

	auto msprite = isActive;
	msprite->setPosition(Point(getPosition().x + this->getContentSize().width / 3 + msprite->getContentSize().width / 2,
		getPosition().y + this->getContentSize().height / 3 + msprite->getContentSize().height / 2));
	msprite->setName("isActive");
	msprite->setVisible(m_isAccessible);

	this->addChild(msprite);
}


bool NPC::isAccessible()
{
	return m_isAccessible;
}


void NPC::setIsAccessible(bool bAccess)
{
	m_isAccessible = bAccess;
}

