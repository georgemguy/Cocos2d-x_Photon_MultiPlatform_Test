#include "ControlPhoton.h"
#include "PhotonTest.h"
#include "Photon_lib.h"
#include "PhotonTest.h"
#include "../testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ExitGames;
using namespace Photon;

ConnectButton::ConnectButton()
{
}

ConnectButton::~ConnectButton()
{
}

bool ConnectButton::init()
{
    CCLabelTTF* label = CCLabelTTF::create( "Connect", f_AmericanTypewriter, 16 );
    CCScale9Sprite* sprite = CCScale9Sprite::create("Images/r1.png");
    
    if( CCControlButton::initWithLabelAndBackgroundSprite( label, sprite ) )
    {
        this->addTargetWithActionForControlEvents( this, cccontrol_selector( ConnectButton::touchUpInsideAction ), CCControlEventTouchUpInside );
        this->scheduleUpdate();
        return true;
    }
    return false;
}

void ConnectButton::touchUpInsideAction( CCObject *sender, CCControlEvent controlEvent )
{
    /*PhotonLib& photonLib = PhotonTestScene::sharedPhotonLib();
    photonLib.connectIfInitialized();*/
}

bool ConnectButton::isConnected()
{
    /*PhotonLib& photonLib = PhotonTestScene::sharedPhotonLib();
    PhotonLib::State::States currentState = photonLib.getState();
    
    return currentState > PhotonLib::State::CONNECTING &&
        currentState < PhotonLib::State::DISCONNECTED;*/
    return false;
}

void ConnectButton::update(float delta)
{
    static bool wasConnected = this->isConnected();
    
    if( this->isConnected() )
    {
        if( ! wasConnected ) this->setTitleLabel( CCLabelTTF::create( "Disconnect", f_AmericanTypewriter, 16 ) );
    }
    else
    {
        if( wasConnected ) this->setTitleLabel( CCLabelTTF::create( "Connect", f_AmericanTypewriter, 16 ) );
    }
    
    wasConnected = this->isConnected();
}

SendButton::SendButton()
{
}

SendButton::~SendButton()
{
}

bool SendButton::init()
{
    CCLabelTTF* label = CCLabelTTF::create( "Send", f_AmericanTypewriter, 16 );
    CCScale9Sprite* sprite = CCScale9Sprite::create("Images/r1.png");
    
    if( CCControlButton::initWithLabelAndBackgroundSprite( label, sprite ) )
    {
        this->addTargetWithActionForControlEvents( this, cccontrol_selector( SendButton::touchUpInsideAction ), CCControlEventTouchUpInside );
        this->scheduleUpdate();
        return true;
    }
    return false;
}

void SendButton::touchUpInsideAction( CCObject *sender, CCControlEvent controlEvent )
{
    /*PhotonLib& photonLib = PhotonTestScene::sharedPhotonLib();
    photonLib.sendDataIfJoined();*/
}

bool SendButton::canSend()
{
    /*PhotonLib& photonLib = PhotonTestScene::sharedPhotonLib();
    PhotonLib::State::States currentState = photonLib.getState();
    
    return currentState == PhotonLib::State::JOINED;*/
}

void SendButton::update(float delta)
{
    this->setEnabled( this->canSend() );
}