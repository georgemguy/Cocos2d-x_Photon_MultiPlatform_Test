//
//  ControlSafetyButton.cpp
//  Abstroku
//
//  Created by George Guy on 9/14/12.
//
//

#include "CCRecursiveAction.h"
#include "CCControlConfirmMessage.h"
#include "CCRemoveFromParent.h"
#include "CCEnable.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCControlConfirmMessage::CCControlConfirmMessage() : CCControlButton()
{
    this->_cancel = NULL;
    this->_okay = NULL;
}

CCControlConfirmMessage::~CCControlConfirmMessage()
{
    this->setCancel( NULL );
    this->setOkay( NULL );
}

CCControlConfirmMessage* CCControlConfirmMessage::create( const char* message,
                                                         const char* fontName,
                                                         const char* button1Name,
                                                         const char* button2Name,
                                                         const cocos2d::CCSize& mySize,
                                                     cocos2d::CCObject* okayTarget,
                                                     cocos2d::extension::SEL_CCControlHandler okayCallback )
{
    CCControlConfirmMessage *pRet = new CCControlConfirmMessage();
    pRet->init( message, fontName, button1Name, button2Name, mySize, okayTarget, okayCallback );
    pRet->autorelease();
    return pRet;
}

bool CCControlConfirmMessage::init( const char* message,
                                   const char* fontName,
                                   const char* button1Name,
                                   const char* button2Name,
                                   const cocos2d::CCSize& mySize,
                               cocos2d::CCObject* okayTarget,
                               cocos2d::extension::SEL_CCControlHandler okayCallback )
{
    CCDirector* director = CCDirector::sharedDirector();
    CCSize size = director->getWinSize();
    CCPoint point = ccpMult( ccpFromSize( size ), 0.5f );
    CCRect messageRect = CCRectZero;
    messageRect.size = mySize;
    
    CCLabelTTF* label = CCLabelTTF::create(
                                           message,
                                           fontName, 20,
                                           messageRect.size,
                                           kCCTextAlignmentCenter,
                                           kCCVerticalTextAlignmentCenter );
    ccColor3B color;
    color.b = 255;
    color.r = 50;
    color.g = 50;
    label->setColor( color );
    CCScale9Sprite* sprite = CCScale9Sprite::create( button2Name, messageRect );
    
    if( this->initWithLabelAndBackgroundSprite( label, sprite ) )
    {
        this->setPosition( point );
        
        color.b = 0;
        color.r = 0;
        color.g = 0;

        label = CCLabelTTF::create( "Cancel", fontName, 15 );
        label->setColor( color );
        sprite = CCScale9Sprite::create(button1Name);
        CCControlButton* button = CCControlButton::create( label, sprite );
        button->setPosition( 10, 10 );
        button->setAnchorPoint( CCPointZero );
        button->addTargetWithActionForControlEvents( this,
                                                   cccontrol_selector(CCControlConfirmMessage::controlCallbackCancel),
                                                   CCControlEventTouchUpInside );
        this->setCancel( button );
        
        label = CCLabelTTF::create( "Okay", fontName, 15 );
        label->setColor( color );
        sprite = CCScale9Sprite::create(button1Name);
        button = CCControlButton::create( label, sprite );
        button->setPosition( this->getContentSize().width - 10, 10 );
        button->setAnchorPoint( ccp(1,0) );
        button->addTargetWithActionForControlEvents( this,
                                                   cccontrol_selector(CCControlConfirmMessage::controlCallbackOkay),
                                                   CCControlEventTouchUpInside );
        button->addTargetWithActionForControlEvents( okayTarget, okayCallback, CCControlEventTouchUpInside );
        this->setOkay( button );
    }
    
    return true;
}

void CCControlConfirmMessage::controlCallbackOkay( cocos2d::CCObject* source )
{
    this->runAction( CCRemoveFromParent::create( this ) );
}

void CCControlConfirmMessage::controlCallbackCancel( cocos2d::CCObject* source )
{
    this->runAction( CCRemoveFromParent::create( this ) );
}

void CCControlConfirmMessage::onEnter()
{
    CCControl::onEnter();
    this->getParent()->runAction( CCRecursiveAction::create(CCEnable::create(false), this) );
}

void CCControlConfirmMessage::onExit()
{
    CCControl::onExit();
    this->getParent()->runAction( CCRecursiveAction::create(CCEnable::create(true), this) );
}