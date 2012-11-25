//
//  ControlSafetyButton.cpp
//  Abstroku
//
//  Created by George Guy on 9/14/12.
//
//

#include "CaTRecursiveAction.h"
#include "ControlConfirmMessage.h"
#include "CaTDegenerate.h"
#include "CaTEnableControl.h"

USING_NS_CC;
USING_NS_CC_EXT;

ControlConfirmMessage::ControlConfirmMessage()
{
    this->_cancel = NULL;
    this->_okay = NULL;
}

ControlConfirmMessage::~ControlConfirmMessage()
{
    this->setCancel( NULL );
    this->setOkay( NULL );
}

ControlConfirmMessage* ControlConfirmMessage::create( const char* message,
                                                     cocos2d::CCObject* okayTarget,
                                                     cocos2d::extension::SEL_CCControlHandler okayCallback )
{
    ControlConfirmMessage *pRet = new ControlConfirmMessage();
    pRet->init( message, okayTarget, okayCallback );
    pRet->autorelease();
    return pRet;
}

bool ControlConfirmMessage::init( const char* message,
                               cocos2d::CCObject* okayTarget,
                               cocos2d::extension::SEL_CCControlHandler okayCallback )
{
    CCDirector* director = CCDirector::sharedDirector();
    CCSize size = director->getWinSize();
    CCPoint point = ccpMult( ccpFromSize( size ), 0.5f );
    CCRect messageRect = CCRectZero;
    messageRect.size = CCSizeMake( size.width * 0.5f, size.height * 0.5f );
    
    CCLabelTTF* label = CCLabelTTF::create(
                                           message,
                                           "vtkschalk79.ttf", 20,
                                           messageRect.size,
                                           kCCTextAlignmentCenter,
                                           kCCVerticalTextAlignmentCenter );
    ccColor3B color;
    color.b = 255;
    color.r = 50;
    color.g = 50;
    label->setColor( color );
    CCScale9Sprite* sprite = CCScale9Sprite::create( "wood_pre.png", messageRect );
    
    if( this->initWithLabelAndBackgroundSprite( label, sprite ) )
    {
        this->setPosition( point );
        
        color.b = 0;
        color.r = 0;
        color.g = 0;

        label = CCLabelTTF::create( "Cancel", "vtkschalk79.ttf", 15 );
        label->setColor( color );
        sprite = CCScale9Sprite::create("CloseSelected.png");
        CCControlButton* button = CCControlButton::create( label, sprite );
        button->setPosition( 10, 10 );
        button->setAnchorPoint( CCPointZero );
        button->addTargetWithActionForControlEvent( this,
                                                   cccontrol_selector(ControlConfirmMessage::controlCallbackCancel),
                                                   CCControlEventTouchUpInside );
        this->setCancel( button );
        
        label = CCLabelTTF::create( "Okay", "vtkschalk79.ttf", 15 );
        label->setColor( color );
        sprite = CCScale9Sprite::create("CloseNormal.png");
        button = CCControlButton::create( label, sprite );
        button->setPosition( this->getContentSize().width - 10, 10 );
        button->setAnchorPoint( ccp(1,0) );
        button->addTargetWithActionForControlEvent( this,
                                                   cccontrol_selector(ControlConfirmMessage::controlCallbackOkay),
                                                   CCControlEventTouchUpInside );
        button->addTargetWithActionForControlEvent( okayTarget, okayCallback, CCControlEventTouchUpInside );
        this->setOkay( button );
    }
    
    return true;
}

void ControlConfirmMessage::controlCallbackOkay( cocos2d::CCObject* source )
{
    this->runAction( CaTDegenerate::create( this ) );
}

void ControlConfirmMessage::controlCallbackCancel( cocos2d::CCObject* source )
{
    this->runAction( CaTDegenerate::create( this ) );
}

void ControlConfirmMessage::onEnter()
{
    CCControl::onEnter();
    ((CCControl*)this->getParent())->runAction( CaTRecursiveAction::create(CaTEnableControl::create(false), this));
    //((CCControl*)this->getParent())->setEnabled( false );
}
void ControlConfirmMessage::onExit()
{
    CCControl::onExit();
    ((CCControl*)this->getParent())->runAction( CaTRecursiveAction::create(CaTEnableControl::create(true), this));
}