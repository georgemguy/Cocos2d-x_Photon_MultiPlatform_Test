#include "PhotonTest.h"
#include "../testResource.h"
#include "cocos2d.h"
#include "ControlPhoton.h"

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \

using namespace ExitGames;
using namespace Photon;

//------------------------------------------------------------------
//
// PhotonTest
//
//------------------------------------------------------------------
PhotonTest::PhotonTest(void)
{
    this->_stateLabel = NULL;
}

PhotonTest::~PhotonTest(void)
{
}

std::string PhotonTest::title()
{
    return "PhotonTest";
}

PhotonLib& PhotonTestScene::sharedPhotonLib()
{
    CCDirector* director = CCDirector::sharedDirector();
    PhotonTestScene* scene = dynamic_cast<PhotonTestScene*>( director->getRunningScene() );
    
    CCAssert( scene, "PhotonTestScene::sharedPhotonLib() -- PhotonTest is not running" );
    return scene->getPhotonTest()->getPhotonLib();
}

void PhotonTest::onEnter()
{
    CCLayer::onEnter();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _listener = new StdIO_UIListener();
    this->setContentSize(winSize);
    
    ConnectButton* connect = ConnectButton::create();
    CCPoint position = ccpMult( ccpFromSize( winSize ), 0.5f );
    position.x -= 100;
    position.y -= 100;
    connect->setPosition( position );
    this->addChild( connect );
    
    SendButton* send = SendButton::create();
    position.x += 200;
    send->setPosition( position );
    this->addChild( send );
    
    this->scheduleUpdate();
}

void PhotonTest::onExit()
{
    CCLayer::onExit();
    
    _listener->onLibClosed();
    delete _listener;
}

PhotonLib& PhotonTest::getPhotonLib()
{
    return this->_photonLib;
}

void PhotonTest::update(float delta)
{
    CCLayer::update(delta);
    
    static const float pause = 1.0f;
    static float wait = pause;
    
    if( wait > 0.0f )
    {
        wait -= delta;
    }
    else
    {
        _photonLib.update();
        this->getListener()->writeString(_photonLib.getStateString());
        wait = pause;
    }

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    Common::JString jStr = _photonLib.getStateString();
    const char* cStr = jStr.ANSIRepresentation();
    
    if( ! _stateLabel )
    {
        _stateLabel = CCLabelTTF::create(cStr, "fonts/American Typewriter.ttf", 24,
                                     winSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        this->addChild( _stateLabel );
    }
    else
    {
        _stateLabel->setString( cStr );
    }
    _stateLabel->setColor( ccc3(255, 255, 255) );
    _stateLabel->setContentSize(winSize);
    _stateLabel->setPosition( ccpMult( ccpFromSize( winSize ), 0.5f ) );    
}

//------------------------------------------------------------------
//
// PhotonTestScene
//
//------------------------------------------------------------------
void PhotonTestScene::runThisTest()
{
    this->_photonTest = new PhotonTest();
    addChild(_photonTest);
    _photonTest->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
