

#ifndef _MAPMANAGER_
#define _MAPMANAGER_

#include "cocos2d.h"
USING_NS_CC;

enum BREAK_WALL_TYPE
{
	BREAK_NONE,			// û��
	BREAK_TRUE,			// ������
	BREAK_FALSE,		// ������
};

class MapManager
{
public:

	static MapManager * getManager();

	void setMapData(TMXTiledMap * mapData);
	bool inWall(const Vec2 &pos);
	bool inBoom(const Vec2 &pos);
	Vec2 getNearMapPos(const Vec2 &pos);			// ��һ�����꣬���ص�ͼ�Ķ�������
	Size getMapTiledSize();
	BREAK_WALL_TYPE inBreakWall(const Vec2 &pos, const Vec2 &dir);
	void addBoomItem(Node * b);
	void removeBoomItem(Node * b);

private:
	MapManager(){};
	~MapManager(){};

	TMXTiledMap * m_mapData;

	Vector<Node *> m_boomVector;


};



#endif