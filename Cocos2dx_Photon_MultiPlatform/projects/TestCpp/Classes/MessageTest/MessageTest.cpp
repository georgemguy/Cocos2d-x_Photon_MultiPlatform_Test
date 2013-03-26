//
//  MessageTest.cpp
//  TestCpp
//
//  Created by George Guy on 3/24/13.
//
//

#include "MessageTest.h"
#include "CCConfirmMessage.h"
#include "../testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define FIX_POS(_pos, _min, _max) \
if (_pos < _min)        \
_pos = _min;        \
else if (_pos > _max)   \
_pos = _max;        \


//------------------------------------------------------------------
//
// MessageTest
//
//------------------------------------------------------------------
MessageTest::MessageTest(void) : CCLayer()
{
    this->_stateLabel = NULL;
}

MessageTest::~MessageTest(void)
{
}

std::string MessageTest::title()
{
    return "MessageTest";
}

void MessageTest::onEnter()
{
    CCLayer::onEnter();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint winCenter = ccpMult( ccpFromSize( winSize ), 0.5f );
    this->setContentSize(winSize);
    
    CCSprite* background = CCSprite::create( "Default.png" );
    CCLabelTTF* label = CCLabelTTF::create( "Do you want to go to the\ndesert, or the forest?", f_AmericanTypewriter, 24 );
    label->setColor(ccRED);
    
    const CCRect cancelRect = CCRectMake( 0, 0, 79, 46 );
    CCLabelTTF* cancelLabel = CCLabelTTF::create( "Desert", f_AmericanTypewriter, 16 );
    cancelLabel->setColor(ccBLACK);
    CCScale9Sprite* cancelSprite = CCScale9Sprite::create( "Images/b1.png", cancelRect, CCRectZero );
    CCControlButton* cancel = CCControlButton::create( cancelLabel, cancelSprite );
    cancel->setPreferredSize( cancelRect.size );
    cancel->addTargetWithActionForControlEvents( this, cccontrol_selector(MessageTest::desertCallback), CCControlEventTouchUpInside );
    
    const CCRect okayRect = CCRectMake( 0, 0, 79, 47 );
    CCLabelTTF* okayLabel = CCLabelTTF::create( "Forest", f_AmericanTypewriter, 16 );
    okayLabel->setColor(ccBLACK);
    CCScale9Sprite* okaySprite = CCScale9Sprite::create( "Images/f1.png", okayRect, CCRectZero );
    CCControlButton* okay = CCControlButton::create( okayLabel, okaySprite );
    okay->setPreferredSize( okayRect.size );
    okay->addTargetWithActionForControlEvents( this, cccontrol_selector(MessageTest::forestCallback), CCControlEventTouchUpInside );
    
    CCFiniteTimeAction* in = CCMoveBy::create( 1.0f, ccpFromSize( winSize ) );
    CCFiniteTimeAction* out = CCMoveBy::create( 1.0f, ccpNeg( ccpFromSize( winSize ) ) );
    
    CCConfirmMessage* message = CCConfirmMessage::create( background, label, cancel, okay, in, out );
    message->setPosition( ccpNeg( ccpFromSize( winSize ) ) );
    this->addChild( message );
    
    this->scheduleUpdate();
}

void MessageTest::desertCallback(cocos2d::CCObject *sender)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint winCenter = ccpMult( ccpFromSize( winSize ), 0.5f );
    this->setContentSize(winSize);
    
    CCSprite* background = CCSprite::create( "Images/landscape-1024x1024.png" );
    background->setScale( winSize.width / background->getContentSize().width );
    CCLabelTTF* label = CCLabelTTF::create( "Here's the desert!\nHow do you like it?", f_AmericanTypewriter, 24 );
    label->setColor(ccBLACK);
    
    const CCRect cancelRect = CCRectMake( 0, 0, 79, 46 );
    CCLabelTTF* cancelLabel = CCLabelTTF::create( "Bad", f_AmericanTypewriter, 16 );
    cancelLabel->setColor(ccBLUE);
    CCScale9Sprite* cancelSprite = CCScale9Sprite::create( "Images/b2.png", cancelRect, CCRectZero );
    CCControlButton* cancel = CCControlButton::create( cancelLabel, cancelSprite );
    cancel->setPreferredSize( cancelRect.size );
    
    const CCRect okayRect = CCRectMake( 0, 0, 79, 47 );
    CCLabelTTF* okayLabel = CCLabelTTF::create( "Good", f_AmericanTypewriter, 16 );
    okayLabel->setColor(ccBLACK);
    CCScale9Sprite* okaySprite = CCScale9Sprite::create( "Images/f2.png", okayRect, CCRectZero );
    CCControlButton* okay = CCControlButton::create( okayLabel, okaySprite );
    okay->setPreferredSize( okayRect.size );
    
    CCFiniteTimeAction* in = CCMoveBy::create( 1.0f, ccpFromSize( winSize ) );
    CCFiniteTimeAction* out = CCMoveBy::create( 1.0f, ccpNeg( ccpFromSize( winSize ) ) );
    
    CCConfirmMessage* message = CCConfirmMessage::create( background, label, cancel, okay, in, out );
    message->setPosition( ccpNeg( ccpFromSize( winSize ) ) );
    this->addChild( message );
}

void MessageTest::forestCallback(cocos2d::CCObject *sender)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint winCenter = ccpMult( ccpFromSize( winSize ), 0.5f );
    this->setContentSize(winSize);
    
    CCSprite* background = CCSprite::create( "Images/background.png" );
    background->setScale( winSize.width / background->getContentSize().width );
    CCLabelTTF* label = CCLabelTTF::create( "Here's the forest!\nHow do you like it?", f_AmericanTypewriter, 24 );
    label->setColor(ccWHITE);
    
    const CCRect cancelRect = CCRectMake( 0, 0, 79, 46 );
    CCLabelTTF* cancelLabel = CCLabelTTF::create( "Bad", f_AmericanTypewriter, 16 );
    cancelLabel->setColor(ccBLACK);
    CCScale9Sprite* cancelSprite = CCScale9Sprite::create( "Images/b2.png", cancelRect, CCRectZero );
    CCControlButton* cancel = CCControlButton::create( cancelLabel, cancelSprite );
    cancel->setPreferredSize( cancelRect.size );
    
    const CCRect okayRect = CCRectMake( 0, 0, 79, 47 );
    CCLabelTTF* okayLabel = CCLabelTTF::create( "Good", f_AmericanTypewriter, 16 );
    okayLabel->setColor(ccBLACK);
    CCScale9Sprite* okaySprite = CCScale9Sprite::create( "Images/f2.png", okayRect, CCRectZero );
    CCControlButton* okay = CCControlButton::create( okayLabel, okaySprite );
    okay->setPreferredSize( okayRect.size );
    
    CCFiniteTimeAction* in = CCMoveBy::create( 1.0f, ccpFromSize( winSize ) );
    CCFiniteTimeAction* out = CCMoveBy::create( 1.0f, ccpNeg( ccpFromSize( winSize ) ) );
    
    CCConfirmMessage* message = CCConfirmMessage::create( background, label, cancel, okay, in, out );
    message->setPosition( ccpNeg( ccpFromSize( winSize ) ) );
    this->addChild( message );
}

void MessageTest::onExit()
{
    CCLayer::onExit();
}

//------------------------------------------------------------------
//
// MessageTestScene
//
//------------------------------------------------------------------
void MessageTestScene::runThisTest()
{
    this->_MessageTest = new MessageTest();
    addChild(_MessageTest);
    
    CCDirector::sharedDirector()->replaceScene(this);
}
