#pragma once
#ifndef _TimeCount_H_
#define _TimeCount_H_


#include "cocos2d.h"
USING_NS_CC;
class TimeCounter : public Node
{
public:
	CREATE_FUNC(TimeCounter);
	virtual bool init();

	//virtual void update(float dt);

	void updateTime(float dt);

	void start();//开始计时
	int getSec();//获取当前时间
	int getMin();
private:
	int m_sec;
	int m_min;
};

#endif // !_TimeCount_H_