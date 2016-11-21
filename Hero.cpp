

#include "Hero.h"
#include "MapManager.h"
#include "Zhadan.h"

bool Hero::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	auto spr = Sprite::create("hero.png", Rect(0, 0, 55, 62));
	this->addChild(spr);
	spr->setScale(0.5f);

	m_moveState = MOVE_DIR::MOVE_NONE;

	auto lis = EventListenerKeyboard::create();

	lis->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
	lis->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, this);

	scheduleUpdate();
	return true;
}

void Hero::update(float dt)
{
	Vec2 newPos = this->getPosition();
	switch (m_moveState)
	{
	case MOVE_UP:
		newPos.y += m_moveSpeed * dt;
		break;
	case MOVE_LEFT:
		newPos.x -= m_moveSpeed * dt;
		break;
	case MOVE_RIGHT:
		newPos.x += m_moveSpeed * dt;
		break;
	case MOVE_DOWN:
		newPos.y -= m_moveSpeed * dt;
		break;
	}
	// 如果主角当前位置 在不可行走范围内，就不去检测下一步能否到达
	if (MapManager::getManager()->inBoom(this->getPosition()))
	{
		if (!MapManager::getManager()->inWall(newPos))
			this->setPosition(newPos);
	}
	else if (!MapManager::getManager()->inWall(newPos) && !MapManager::getManager()->inBoom(newPos))
	{
		this->setPosition(newPos);
	}
}

void Hero::onKeyPressed(EventKeyboard::KeyCode code , Event*)
{
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_W:
		m_moveState = MOVE_UP;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		m_moveState = MOVE_LEFT;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		m_moveState = MOVE_DOWN;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		m_moveState = MOVE_RIGHT;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		// 创建一个炸弹

		auto zd = Zhadan::create();
		zd->setPosition(MapManager::getManager()->getNearMapPos(this->getPosition()));
		this->getParent()->addChild(zd, -2);

		break;
	}
}

void Hero::onKeyReleased(EventKeyboard::KeyCode code, Event*)
{
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_D:
		m_moveState = MOVE_NONE;
		break;
	}
}