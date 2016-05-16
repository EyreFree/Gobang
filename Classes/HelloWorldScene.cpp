#include "HelloWorldScene.h"
#include "EyreFree.h"

enum 
{
	kTagSpriteBatchNode_Black = 1,
	kTagSpriteBatchNode_White = 2
};

CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool HelloWorld::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);

	registerWithTouchDispatcher();

	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		//图片
		CCSprite* pBackGroundSprite = CCSprite::create("Square.png");
		CC_BREAK_IF(! pBackGroundSprite);
		pBackGroundSprite->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(pBackGroundSprite, 0);
		
		pWinSprite = CCSprite::create("Win+.png");
		CC_BREAK_IF(! pWinSprite);
		pWinSprite->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(pWinSprite, 0);
		pWinSprite->setScale(0.5);
		pWinSprite->setVisible(false);

		pLoseSprite = CCSprite::create("Lose+.png");
		CC_BREAK_IF(! pLoseSprite);
		pLoseSprite->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(pLoseSprite, 0);
		pLoseSprite->setScale(0.5);
		pLoseSprite->setVisible(false);
		
		//按钮
		Menunode = CCNode::create();
		this->addChild(Menunode ,0 );

		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);
		pCloseItem->setPosition(ccp(size.width / 2 + 62, size.height / 2));
		CCMenu* pCloseMenu = CCMenu::create(pCloseItem, NULL);
		pCloseMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pCloseMenu);
		Menunode->addChild(pCloseMenu, 1);

		CCMenuItemImage *pReplayItem = CCMenuItemImage::create(
			"ReplayNormal.png",
			"ReplaySelected.png",
			this,
			menu_selector(HelloWorld::menuReplayCallback));
		CC_BREAK_IF(! pReplayItem);
		pReplayItem->setPosition(ccp(size.width / 2 - 62 , size.height / 2));
		CCMenu* pReplayMenu = CCMenu::create(pReplayItem, NULL);
		pReplayMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pReplayMenu);

		Menunode->addChild(pReplayMenu, 1);
		Menunode->setPosition(ccp(0 , 0));
		Menunode->setScale(0.5);
		Menunode->setVisible(false); 

		bRet = true;
	} while (0);

	SpriteBatchNodeInit();

	return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();				 // close
}

void HelloWorld::menuReplayCallback(CCObject* pSender)
{
	CCSpriteBatchNode* BatchNode = (CCSpriteBatchNode*) getChildByTag(kTagSpriteBatchNode_Black);
	BatchNode->removeAllChildrenWithCleanup(true);

	BatchNode = (CCSpriteBatchNode*) getChildByTag(kTagSpriteBatchNode_White);
	BatchNode->removeAllChildrenWithCleanup(true);

	GameControler.InitGame();

	Menunode->setVisible(false);
	pWinSprite->setVisible(false);
	pLoseSprite->setVisible(false);
}


////////////////////////////////////////////////////////
//
// TouchesPerformTest1
//
////////////////////////////////////////////////////////

void HelloWorld::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelloWorld::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return true;
}

void HelloWorld::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
}

void HelloWorld::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(GameControler.IsGameEnable())
	{
		CCPoint location = touch->locationInView();
		POINT theSite = {(int)location.x / 40,(int)location.y / 40};
		
		if(SetPointToScreen(theSite) && GameControler.IsGameEnable())
		{
			//AI落子
			//if(!(GameControler.AI_Sample(&theSite) && SetPointToScreen(theSite)))	//测试用：随机落子
			if(!(GameControler.AI_Level_1(&theSite) && SetPointToScreen(theSite)))	//初级AI：
			{
				GameControler.MakeGameDisable();
			}
			//AI落子结束
		}
	}
	else
	{
		CCSprite* targetSprite = NULL;
		(GameControler.GetGameResult() == PLAYER_WIN) ? targetSprite = pWinSprite : targetSprite = pLoseSprite;
		(Menunode->isVisible() && targetSprite) ? (Menunode->setVisible(false),targetSprite->setVisible(false)) : (Menunode->setVisible(true),targetSprite->setVisible(true));
	}
}

bool HelloWorld::SetPointToScreen(POINT theSite)
{
	CCPoint location;
	if(CCPointToSite(&location,theSite))
	{
		if(GameControler.SetChessPoint(theSite))
		{
			#ifdef OUTPUT_DEBUG_STRING
			char tempCh[512] = "";
			sprintf(tempCh,"GameControler.GetChessPlayer() = %d\ntheSite.x = %d ; theSite.y = %d",GameControler.GetChessPlayer(),theSite.x,theSite.y);
			printf("%s\n",tempCh);
			CString wStr = tempCh;
			OutputDebugString(wStr);
			#endif

			location = CCDirector::sharedDirector ()->convertToGL (location);
			addNewSpriteWithCoords(location);

			GameControler.SetGameResult();
			if(GameControler.CheckGameState())
			{
				GameControler.MakeGameDisable();			//使游戏停止响应
				Menunode->setVisible(true);
				this->reorderChild(Menunode,0);

				(GameControler.GetGameResult() == PLAYER_WIN) ? pWinSprite->setVisible(true) : pLoseSprite->setVisible(true);
			}
			return true;
		}
	}
	return false;
}

void HelloWorld::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
}


////////////////////////////////////////////////////////
//
// SpriteBatchNode
//
////////////////////////////////////////////////////////

void HelloWorld::SpriteBatchNodeInit()
{
	CCSpriteBatchNode* BatchNode_Black = CCSpriteBatchNode::create("Black.png", 50);
	this->addChild(BatchNode_Black, 0, kTagSpriteBatchNode_Black);
	CCSpriteBatchNode* BatchNode_White = CCSpriteBatchNode::create("White.png", 50);
	this->addChild(BatchNode_White, 0, kTagSpriteBatchNode_White);
}

void HelloWorld::addNewSpriteWithCoords(CCPoint p)
{
	int addTag = 0;
	(GameControler.GetChessPlayer() == PLAYER_WHITE) ? (addTag = kTagSpriteBatchNode_White) : (addTag = kTagSpriteBatchNode_Black);
	CCSpriteBatchNode* BatchNode = (CCSpriteBatchNode*) getChildByTag(addTag);

	CCSprite* newPoint = CCSprite::createWithTexture(BatchNode->getTexture());
	newPoint->setScale(1.5);
	BatchNode->addChild(newPoint);
	newPoint->setPosition(ccp( p.x, p.y));
}


////////////////////////////////////////////////////////
//
// CommonFunction
//
////////////////////////////////////////////////////////

bool HelloWorld::CCPointToSite(CCPoint * thePoint,POINT targetPoint)
{
	thePoint->x = targetPoint.x * 40 + 20;
	thePoint->y = targetPoint.y * 40 + 20;
	return true;
}