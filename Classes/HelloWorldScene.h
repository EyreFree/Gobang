#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "GameControl.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
private:

	GameControl GameControler;

public:

	CCNode * Menunode;
	CCSprite* pWinSprite;
	CCSprite* pLoseSprite;

public:

	virtual bool init();

    static CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
	void menuReplayCallback(CCObject* pSender);
    CREATE_FUNC(HelloWorld);

	// TouchesPerformTest1
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void ccTouchMoved(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void ccTouchCancelled(CCTouch* touch, CCEvent* event);

	// SpriteBatchNode1
	void HelloWorld::SpriteBatchNodeInit();
	void HelloWorld::addNewSpriteWithCoords(CCPoint p);

	// CommonFunction
	bool CCPointToSite(CCPoint * thePoint,POINT targetPoint);
	bool SetPointToScreen(POINT targetPoint);
};

#endif  // __HELLOWORLD_SCENE_H__