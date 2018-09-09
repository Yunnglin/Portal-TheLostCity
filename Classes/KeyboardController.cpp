#include "KeyboardController.h"
#include "Player.h"
#include "Gun.h"
#include "LevelScene.h"
#include "PauseScene.h"

bool KeyboardController::init() {
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto *dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();
	//����һ���¼����������������¼�
	keyListener->onKeyPressed = CC_CALLBACK_2(KeyboardController::onKeyPressed, this);
	//���̱�����ʱ��Ӧ
	keyListener->onKeyReleased = CC_CALLBACK_2(KeyboardController::onKeyReleased, this);
	//���̰���������ʱ��Ӧ
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
//	// 0.3s�����Ŷ����ӿ�ʼ���������õ�ʱ�䣬�Ӷ��Եò�����ô��е��
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
//	//��Ϊ��Ծ״̬����ִ���ظ�
//	if (isJumping) {
//		return;
//	}
//
//	isJumping = true;
//	//һ��ԭ����Ծ250����һ��
//	auto jump = JumpBy::create(0.5f, Point(0, 0), 250, 1);
//	//�����ص�����
//	auto callFunc = CallFunc::create(
//		[&]() {
//		isJumping = false;
//	    }
//	);
//	//������������
//	auto jumpAction = Sequence::create(jump, callFunc, NULL);
//	//ִ�ж���
//	player->runAction(jumpAction);
//}

