
#ifndef _HERO_
#define _HERO_

#include "cocos2d.h"
USING_NS_CC;

enum MOVE_DIR {

	MOVE_NONE,		// Í£ÖÍ  ÉÏ ×ó ÓÒ ÏÂ 
	MOVE_UP,			
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,

};

class Hero : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Hero);

	void update(float dt);

	void onKeyPressed (EventKeyboard::KeyCode, Event*);
	void onKeyReleased(EventKeyboard::KeyCode, Event*);

	const float m_moveSpeed = 100;

	MOVE_DIR m_moveState;

};


#endif
