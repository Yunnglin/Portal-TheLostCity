#include "PopWin.h"
USING_NS_CC;

bool PopWin::init()
{
	m_isActive = false;
	return true;
}

void PopWin::setLabel(Label* label,const char* filePath,std::string key) {

	//创建词典类实例，将xml文件加载到词典中
	auto *chnStrings = Dictionary::createWithContentsOfFile(filePath);
	//通过xml文件中的key获取value
	sText = ((String*)chnStrings->objectForKey(key))->getCString();

	m_label = label;
	this->addChild(m_label);
	m_label ->setPosition(0, -this->getContentSize().height/4);
	m_label->setDimensions(this->getContentSize().width *3/4.0, this->getContentSize().height *5/6.0);
}

void PopWin::labelStart() {
	auto label = this->m_label;
	
	Vector<FiniteTimeAction*> m_vecAct;
	for (int i = 0; i <= (int)sText.length(); i++)
	{
		auto delay = DelayTime::create(0.025f);
		m_vecAct.pushBack(delay);
		std::string str = sText.substr(0, i);
		auto func = [label, str]() throw() {label->setString(str); };
		auto call = CallFunc::create(func);
		m_vecAct.pushBack((FiniteTimeAction*)call);
	}
	m_label->runAction(Sequence::create(m_vecAct));
}

void PopWin::labelEnd() {
	m_label->stopAllActions();
}

PopWin* PopWin::createWin(const char* path) {
	PopWin* node = PopWin::create();
	Sprite* win = Sprite::create(path);
	node->addChild(win);
	node->setContentSize(win->getContentSize());
	node->setPosition(Point(node->getContentSize().width / 2, node->getContentSize().height / 2));
	return node;
}

bool PopWin::isActive()
{
	return m_isActive;
}

void PopWin::setIsActive(bool bActive)
{
	m_isActive = bActive;
}
