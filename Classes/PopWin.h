#ifndef _POP_LAYER_H_
#define _POP_LAYER_H_


#include "cocos2d.h"

USING_NS_CC;

class PopWin :public cocos2d::Node{
public:
	CREATE_FUNC(PopWin);
	virtual bool init();
	static PopWin* createWin(const char* path);

	void setLabel(Label * label, const char* filePath, std::string key);

	void setIsActive(bool bActive);
	bool isActive();
	void labelStart();
	void labelEnd();
private:
	bool m_isActive;
	cocos2d::Sprite* m_win;
	std::string sText;
	Label* m_label;
};
#endif 