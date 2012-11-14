#include "PhotonLoadBalancingTest.h"
#include "../testResource.h"
#include "cocos2d.h"
#include "CCLobbyView.h"

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
PhotonLoadBalancingTest::PhotonLoadBalancingTest(void)
{
    this->_stateLabel = NULL;
}

PhotonLoadBalancingTest::~PhotonLoadBalancingTest(void)
{
}

std::string PhotonLoadBalancingTest::title()
{
    return "PhotonLoadBalancingTest";
}

/*PhotonLib& PhotonLoadBalancingTestScene::sharedPhotonLib()
{
    CCDirector* director = CCDirector::sharedDirector();
    PhotonLoadBalancingTestScene* scene = dynamic_cast<PhotonLoadBalancingTestScene*>( director->getRunningScene() );
    
    CCAssert( scene, "PhotonLoadBalancingTestScene::sharedPhotonLib() -- PhotonLoadBalancingTest is not running" );
    return scene->getPhotonLoadBalancingTest()->getPhotonLib();
}*/

void PhotonLoadBalancingTest::onEnter()
{
    CCLayer::onEnter();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint winCenter = ccpMult( ccpFromSize( winSize ), 0.5f );
    //_listener = new StdIO_UIListener();
    this->setContentSize(winSize);
    
    CCLobbyView* lobbyView = CCLobbyView::create( new CCNetworkLogic(), winSize );
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

void PhotonLoadBalancingTest::onExit()
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
void PhotonLoadBalancingTestScene::runThisTest()
{
    this->_photonLoadBalancingTest = new PhotonLoadBalancingTest();
    addChild(_photonLoadBalancingTest);

    CCDirector::sharedDirector()->replaceScene(this);
}
