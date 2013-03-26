#include "controller.h"
#include "testResource.h"
#include "tests.h"

#define LINE_SPACE          40

static CCPoint s_tCurPos = CCPointZero;

static TestScene* CreateTestScene(int nIdx)
{
    CCDirector::sharedDirector()->purgeCachedData();

    TestScene* pScene = NULL;

    switch (nIdx)
    {
        case TEST_MESSAGE:
            pScene = new MessageTestScene();
            break;
        case TEST_PHOTON_LOADBALANCING:
            pScene = new PhotonLoadBalancingTestScene();
            break;
        default:
            break;
    }

    return pScene;
}

TestController::TestController()
: m_tBeginPos(CCPointZero)
{
    // add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathClose, s_pPathClose, this, menu_selector(TestController::closeCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    pMenu->setPosition( CCPointZero );
    pCloseItem->setPosition(CCPointMake( s.width - 30, s.height - 30));

    // add menu items for tests
    m_pItemMenu = CCMenu::create();
    for (int i = 0; i < TESTS_COUNT; ++i)
    {
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//         CCLabelBMFont* label = CCLabelBMFont::create(g_aTestNames[i].c_str(),  "fonts/arial16.fnt");
// #else
        CCLabelTTF* label = CCLabelTTF::create(g_aTestNames[i].c_str(), "Arial", 16);
// #endif        
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(TestController::menuCallback));

        m_pItemMenu->addChild(pMenuItem, i + 10000);
        pMenuItem->setPosition( CCPointMake( s.width / 2, (s.height - (i + 1) * LINE_SPACE) ));
    }

    m_pItemMenu->setContentSize(CCSizeMake(s.width, (TESTS_COUNT + 1) * (LINE_SPACE)));
    m_pItemMenu->setPosition(s_tCurPos);
    addChild(m_pItemMenu);

    setTouchEnabled(true);

    addChild(pMenu, 1);

}

TestController::~TestController()
{
}

void TestController::menuCallback(CCObject * pSender)
{
    // get the userdata, it's the index of the menu item clicked
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    int nIdx = pMenuItem->getZOrder() - 10000;

    // create the test scene and run it
    TestScene* pScene = CreateTestScene(nIdx);
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
}

void TestController::closeCallback(CCObject * pSender)
{
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void TestController::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    m_tBeginPos = touch->getLocation();    
}

void TestController::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    CCPoint touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - m_tBeginPos.y;

    CCPoint curPos  = m_pItemMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (nextPos.y < 0.0f)
    {
        m_pItemMenu->setPosition(CCPointZero);
        return;
    }

    if (nextPos.y > ((TESTS_COUNT + 1)* LINE_SPACE - winSize.height))
    {
        m_pItemMenu->setPosition(ccp(0, ((TESTS_COUNT + 1)* LINE_SPACE - winSize.height)));
        return;
    }

    m_pItemMenu->setPosition(nextPos);
    m_tBeginPos = touchLocation;
    s_tCurPos   = nextPos;
}
