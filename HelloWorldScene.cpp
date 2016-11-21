#include "HelloWorldScene.h"
#include "Hero.h"
#include "MapManager.h"

#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Director::getInstance()->setContentScaleFactor(1.0f);
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("NewAnimation.ExportJson");
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto map = TMXTiledMap::create("map/level1.tmx");
	this->addChild(map);

	MapManager::getManager()->setMapData(map);

	auto objLayer = map->getObjectGroup("Objs");
	auto heroObj = objLayer->getObject("Hero");
	auto heroPos = Vec2(heroObj["x"].asFloat(), heroObj["y"].asFloat());
	CCLOG("%s", heroObj["aaa"].asString());

	auto hero = Hero::create();
	hero->setPosition(heroPos);
	this->addChild(hero);
	
	//ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("HeroAnimation.ExportJson");
	//Armature *armature = Armature::create("HeroAnimation");
	//armature->getAnimation()->setMovementEventCallFunc(
	//	[](Armature *armature, MovementEventType movementType, const std::string& movementID)->void{
	//	if (movementType == LOOP_COMPLETE && movementID.compare("stand_stand_handgun_LR") == 0)
	//	{
	//		armature->getAnimation()->playWithIndex(1);
	//	}
	//});
	//armature->getAnimation()->playWithIndex(0);
	//armature->setPosition(visibleSize / 2);
	//this->addChild(armature);
	
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
