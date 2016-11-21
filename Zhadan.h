
#ifndef _CZHADAN_
#define _CZHADAN_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

class Zhadan : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Zhadan);
	int m_level;
	int m_timeOut;
	void animationCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void createEffect(const Node * node);
	void timeOut(float dt);

	int m_effectCount;
};


#endif
