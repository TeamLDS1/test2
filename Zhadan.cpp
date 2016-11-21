

#include "Zhadan.h"
#include "MapManager.h"

bool Zhadan::init()
{
	if (Node::init() == false)
	{
		return false;
	}
	this->setScale(0.6f);
	m_level = 5;
	m_timeOut = 10;

	MapManager::getManager()->addBoomItem(this);

	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("NewAnimation.ExportJson");
	Armature *armature = Armature::create("NewAnimation");
	armature->getAnimation()->play("action1");
	this->addChild(armature);

	scheduleOnce(CC_CALLBACK_1(Zhadan::timeOut, this), m_timeOut, "TIMEOUT");

	return true;
}

void Zhadan::animationCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == LOOP_COMPLETE)
	{
		armature->removeFromParent();
		m_effectCount--;
		if (m_effectCount == 0)
		{
			MapManager::getManager()->removeBoomItem(this);
			this->removeFromParent();
		}
	}
}

void Zhadan::createEffect(const Node * node)
{
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("NewAnimation.ExportJson");
	Armature *armature = Armature::create("NewAnimation");
	armature->getAnimation()->play("action2");
	armature->setPosition(node->getPosition());
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Zhadan::animationCallBack, this));
	this->addChild(armature);
	m_effectCount++;
}

void Zhadan::timeOut(float dt)
{
	m_effectCount = 0;
	auto manager = MapManager::getManager();
	this->removeAllChildren();
	// 创建一堆爆炸效果 上下左右四方向
	for (int i = 0; i < m_level; i++)  // 上
	{
		auto type = manager->inBreakWall(this->getPosition(), Vec2(0, i + 1));
		if (type != BREAK_FALSE)
		{
			// 放一个特效
			// 给每一个动画增加一个回调，动作驱动
			auto node = Node::create();
			this->addChild(node);
			node->setPosition(Vec2(0, manager->getMapTiledSize().height*(i + 1)));
			auto callback = CCCallFuncN::create(CC_CALLBACK_1(Zhadan::createEffect, this));
			node->runAction(Sequence::create(DelayTime::create(i*0.05f), callback, nullptr));
		}

		if (type != BREAK_NONE)
		{
			break;
		}
	}
	for (int i = 0; i < m_level; i++)	// 右
	{
		auto type = manager->inBreakWall(this->getPosition(), Vec2(i + 1, 0));
		if (type != BREAK_FALSE)
		{
			// 放一个特效			
			auto node = Node::create();
			this->addChild(node);
			node->setPosition(Vec2(manager->getMapTiledSize().width*(i + 1), 0));
			auto callback = CCCallFuncN::create(CC_CALLBACK_1(Zhadan::createEffect, this));
			node->runAction(Sequence::create(DelayTime::create(i*0.05f), callback, nullptr));
		}

		if (type != BREAK_NONE)
		{
			break;
		}
	}
	for (int i = 0; i < m_level; i++)		// 下
	{
		auto type = manager->inBreakWall(this->getPosition(), Vec2(0, -1 - i));
		if (type != BREAK_FALSE)
		{
			// 放一个特效
			auto node = Node::create();
			this->addChild(node);
			node->setPosition(Vec2(0, manager->getMapTiledSize().height*(-1 - i)));
			auto callback = CCCallFuncN::create(CC_CALLBACK_1(Zhadan::createEffect, this));
			node->runAction(Sequence::create(DelayTime::create(i*0.05f), callback, nullptr));
		}

		if (type != BREAK_NONE)
		{
			break;
		}
	}
	for (int i = 0; i < m_level; i++)	// 右
	{
		auto type = manager->inBreakWall(this->getPosition(), Vec2(-1 - i, 0));
		if (type != BREAK_FALSE)
		{
			// 放一个特效
			auto node = Node::create();
			this->addChild(node);
			node->setPosition(Vec2(manager->getMapTiledSize().width*(-1 - i), 0));
			auto callback = CCCallFuncN::create(CC_CALLBACK_1(Zhadan::createEffect, this));
			node->runAction(Sequence::create(DelayTime::create(i*0.05f), callback, nullptr));
		}

		if (type != BREAK_NONE)
		{
			break;
		}
	}
}