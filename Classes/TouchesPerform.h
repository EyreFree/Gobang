#ifndef __PERFORMANCE_TOUCHES_TEST_H__
#define __PERFORMANCE_TOUCHES_TEST_H__

#include "cocos2d.h"

class PerformBasicLayer : public CCLayer
{
public:
    PerformBasicLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);

    virtual void onEnter();

    virtual void restartCallback(CCObject* pSender);
    virtual void nextCallback(CCObject* pSender);
    virtual void backCallback(CCObject* pSender);
    virtual void showCurrentTest() = 0;

    virtual void toMainLayer(CCObject* pSender);

protected:
    bool m_bControlMenuVisible;
    int  m_nMaxCases;
    int  m_nCurCase;
};

class TouchesMainScene : public PerformBasicLayer
{
public:
    TouchesMainScene(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void showCurrentTest();
    virtual void onEnter();
    virtual std::string title();
    virtual void update(float dt);

protected:
    CCLabelBMFont * m_plabel;
    int                numberOfTouchesB;
    int                numberOfTouchesM;
    int                numberOfTouchesE;
    int                numberOfTouchesC;
    float            elapsedTime;
};

class TouchesPerformTest1 : public TouchesMainScene
{
public:
    TouchesPerformTest1(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : TouchesMainScene(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void onEnter();
    virtual std::string title();
    virtual void registerWithTouchDispatcher();

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
};

#endif
