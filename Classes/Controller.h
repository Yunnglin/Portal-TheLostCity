#pragma once
#ifndef _Controller_H_
#define _Controller_H_
#include "cocos2d.h"
#include "ControllerListener.h"
USING_NS_CC;
class Controller:public Node
{
public:
	void setControllerListener(ControllerListener* controllerListener);
protected:
	ControllerListener * m_controllerListener;
};

#endif // !_Controller_H_