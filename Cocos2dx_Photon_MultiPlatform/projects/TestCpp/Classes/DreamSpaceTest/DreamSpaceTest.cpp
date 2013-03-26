#include "DreamSpaceTest.h"
#include "../testResource.h"
#include "cocos2d.h"
#include "PMSGameScene.h"

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \


//------------------------------------------------------------------
//
// PhotonLoadBalancingTest
//
//------------------------------------------------------------------
DreamSpaceTest::DreamSpaceTest(void) : CCLayer()
{
    this->_stateLabel = NULL;
}

DreamSpaceTest::~DreamSpaceTest(void)
{
}

std::string DreamSpaceTest::title()
{
    return "DreamSpaceTest";
}

/*PhotonLib& PhotonLoadBalancingTestScene::sharedPhotonLib()
{
    CCDirector* director = CCDirector::sharedDirector();
    PhotonLoadBalancingTestScene* scene = dynamic_cast<PhotonLoadBalancingTestScene*>( director->getRunningScene() );
    
    CCAssert( scene, "PhotonLoadBalancingTestScene::sharedPhotonLib() -- PhotonLoadBalancingTest is not running" );
    return scene->getPhotonLoadBalancingTest()->getPhotonLib();
}*/

void DreamSpaceTest::onEnter()
{
    CCLayer::onEnter();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint winCenter = ccpMult( ccpFromSize( winSize ), 0.5f );
    //_listener = new StdIO_UIListener();
    this->setContentSize(winSize);
    
    PMSGameScene* lobbyView = PMSGameScene::create();
    this->addChild( lobbyView );
    /*ConnectButton* connect = ConnectButton::create();
    CCPoint position = ccpMult( ccpFromSize( winSize ), 0.5f );
    position.x -= 100;
    position.y -= 100;
    connect->setPosition( position );
    this->addChild( connect );
    
    SendButton* send = SendButton::create();
    position.x += 200;
    send->setPosition( position );
    this->addChild( send );*/
    
    this->scheduleUpdate();
}

void DreamSpaceTest::onExit()
{
    CCLayer::onExit();
    
    //_listener->onLibClosed();
    //delete _listener;
}

/*PhotonLib& PhotonLoadBalancingTest::getPhotonLib()
{
    return this->_photonLib;
}*/

//------------------------------------------------------------------
//
// PhotonLoadBalancingTestScene
//
//------------------------------------------------------------------
DreamSpaceTestScene::DreamSpaceTestScene() : TestScene()
{
    
}

void DreamSpaceTestScene::runThisTest()
{
    this->_dreamSpaceTest = new DreamSpaceTest();
    addChild(_dreamSpaceTest);

    CCDirector::sharedDirector()->replaceScene(this);
}
