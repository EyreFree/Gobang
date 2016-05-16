#include "TouchesPerform.h"


////////////////////////////////////////////////////////
//
// PerformBasicLayer
//
////////////////////////////////////////////////////////
PerformBasicLayer::PerformBasicLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: m_bControlMenuVisible(bControlMenuVisible)
, m_nMaxCases(nMaxCases)
, m_nCurCase(nCurCase)
{

}

void PerformBasicLayer::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    CCMenuItemFont* pMainItem = CCMenuItemFont::create("Back", this,
                                                    menu_selector(PerformBasicLayer::toMainLayer));
    pMainItem->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    CCMenu* pMenu = CCMenu::create(pMainItem, NULL);
    pMenu->setPosition( CCPointZero );

    if (m_bControlMenuVisible)
    {
        CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(PerformBasicLayer::backCallback) );
        CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(PerformBasicLayer::restartCallback) );
        CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(PerformBasicLayer::nextCallback) );
        item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

        pMenu->addChild(item1, kItemTagBasic);
        pMenu->addChild(item2, kItemTagBasic);
        pMenu->addChild(item3, kItemTagBasic);
    }
    addChild(pMenu);
}

void PerformBasicLayer::toMainLayer(CCObject* pSender)
{
    PerformanceTestScene* pScene = new PerformanceTestScene();
    pScene->runThisTest();

    pScene->release();
}

void PerformBasicLayer::restartCallback(CCObject* pSender)
{
    showCurrentTest();
}

void PerformBasicLayer::nextCallback(CCObject* pSender)
{
    m_nCurCase++;
    m_nCurCase = m_nCurCase % m_nMaxCases;

    showCurrentTest();
}

void PerformBasicLayer::backCallback(CCObject* pSender)
{
    m_nCurCase--;
    if( m_nCurCase < 0 )
        m_nCurCase += m_nMaxCases;

    showCurrentTest();
}


////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////


enum
{
    TEST_COUNT = 2,
};

static int s_nTouchCurCase = 0;

////////////////////////////////////////////////////////
//
// TouchesMainScene
//
////////////////////////////////////////////////////////
void TouchesMainScene::showCurrentTest()
{
    CCLayer* pLayer = NULL;
    switch (m_nCurCase)
    {
    case 0:
        pLayer = new TouchesPerformTest1(true, TEST_COUNT, m_nCurCase);
        break;
    case 1:
        pLayer = new TouchesPerformTest2(true, TEST_COUNT, m_nCurCase);
        break;
    }
    s_nTouchCurCase = m_nCurCase;

    if (pLayer)
    {
        CCScene* pScene = CCScene::create();
        pScene->addChild(pLayer);
        pLayer->release();

        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void TouchesMainScene::onEnter()
{
    PerformBasicLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // add title
    CCLabelTTF *label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition(ccp(s.width/2, s.height-50));

    scheduleUpdate();

    m_plabel = CCLabelBMFont::create("00.0", "fonts/arial16.fnt");
    m_plabel->setPosition(ccp(s.width/2, s.height/2));
    addChild(m_plabel);

    elapsedTime = 0;
    numberOfTouchesB = numberOfTouchesM = numberOfTouchesE = numberOfTouchesC = 0;    
}

void TouchesMainScene::update(float dt)
{
    elapsedTime += dt;

    if ( elapsedTime > 1.0f)
    {
        float frameRateB = numberOfTouchesB / elapsedTime;
        float frameRateM = numberOfTouchesM / elapsedTime;
        float frameRateE = numberOfTouchesE / elapsedTime;
        float frameRateC = numberOfTouchesC / elapsedTime;
        elapsedTime = 0;
        numberOfTouchesB = numberOfTouchesM = numberOfTouchesE = numberOfTouchesC = 0;

        char str[32] = {0};
        sprintf(str, "%.1f %.1f %.1f %.1f", frameRateB, frameRateM, frameRateE, frameRateC);
        m_plabel->setString(str);
    }
}

std::string TouchesMainScene::title()
{
    return "No title";
}

////////////////////////////////////////////////////////
//
// TouchesPerformTest1
//
////////////////////////////////////////////////////////
void TouchesPerformTest1::onEnter()
{
    TouchesMainScene::onEnter();
    setTouchEnabled(true);
}

std::string TouchesPerformTest1::title()
{
    return "Targeted touches";
}

void TouchesPerformTest1::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool TouchesPerformTest1::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    numberOfTouchesB++;
    return true;
}

void TouchesPerformTest1::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    numberOfTouchesM++;
}

void TouchesPerformTest1::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    numberOfTouchesE++;
}

void TouchesPerformTest1::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
    numberOfTouchesC++;
}
