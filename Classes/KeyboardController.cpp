#include "KeyboardController.h"
#include "Player.h"
#include "Gun.h"
#include "LevelScene.h"
#include "PauseScene.h"

bool KeyboardController::init() {
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto *dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();
	//创建一个事件监听器监听键盘事件
	keyListener->onKeyPressed = CC_CALLBACK_2(KeyboardController::onKeyPressed, this);
	//键盘被按下时响应
	keyListener->onKeyReleased = CC_CALLBACK_2(KeyboardController::onKeyReleased, this);
	//键盘按键被弹回时响应
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	return true;
}

void KeyboardController::setPlayer(Player* player) {
	this->m_player = player;
}

void KeyboardController::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		m_player->jump();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		m_player->setXDirection(-1);
		m_player->playLeftAnimate();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		m_player->setXDirection(1);
		m_player->playRightAnimate();
		break;
	}
	
}

void KeyboardController::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event) {

	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		m_player->setXDirection(0);
		m_player->stopRunning();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		m_player->setXDirection(0);
		m_player->stopRunning();
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
	case EventKeyboard::KeyCode::KEY_P:
		Director::getInstance()->pushScene(TransitionSplitCols::create(1.2f, PauseScene::createScene()));
		break;
	case EventKeyboard::KeyCode::KEY_F:
		NotificationCenter::getInstance()->postNotification("dialog", NULL);
		NotificationCenter::getInstance()->postNotification("exit", NULL);
		break;

	}

}




//void KeyboardController::keyPressedDuration(EventKeyboard::KeyCode code) {
//	int offsetX = 0, offsetY = 0;
//	//Point pos = m_controllerListener->getTagPosition();
//	switch (code) {
//	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
//		offsetX = -5;
//		break;
//	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
//		offsetX = 5;
//		break;
//	default:
//		offsetY = offsetX = 0;
//		break;
//	}
//	// 0.3s代表着动作从开始到结束所用的时间，从而显得不会那么机械。
//	if (isPressingLeft) {
//		auto moveTo1 = MoveTo::create(0.3, Vec2(player->getPositionX() + offsetX, player->getPositionY() + offsetY));
//		player->runAction(moveTo1);
//	}
//	else if (isPressingRight) {
//		auto moveTo2 = MoveTo::create(0.3, Vec2(player->getPositionX() + offsetX, player->getPositionY() + offsetY));
//		player->runAction(moveTo2);
//		//player->runAction(m_animateRight);
//	}
//	
//}

//void KeyboardController::jump() {
//
//	//若为跳跃状态，不执行重复
//	if (isJumping) {
//		return;
//	}
//
//	isJumping = true;
//	//一秒原地跳跃250像素一次
//	auto jump = JumpBy::create(0.5f, Point(0, 0), 250, 1);
//	//创建回调动作
//	auto callFunc = CallFunc::create(
//		[&]() {
//		isJumping = false;
//	    }
//	);
//	//创建连续动作
//	auto jumpAction = Sequence::create(jump, callFunc, NULL);
//	//执行动作
//	player->runAction(jumpAction);
//}

