/****************************************************************************
 Copyright (c) 2013 George Guy

 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCConfirmMessage.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCConfirmMessage::CCConfirmMessage() : CCConfirmMessage::super(),
_inTransition(NULL),
_outTransition(NULL)
{
}

CCConfirmMessage::~CCConfirmMessage()
{
    CC_SAFE_RELEASE_NULL( _inTransition );
    CC_SAFE_RELEASE_NULL( _outTransition );
}

CCConfirmMessage* CCConfirmMessage::create(
                                           CCNode* background,
                                           CCNode* label,
                                           CCControl* cancel,
                                           CCControl* okay,
                                           CCFiniteTimeAction* inTransition,
                                           CCFiniteTimeAction* outTransition )
{
    CCConfirmMessage *pRet = new CCConfirmMessage();
    pRet->init( background, label, cancel, okay, inTransition, outTransition );
    pRet->autorelease();
    return pRet;
}

bool CCConfirmMessage::init(
                               CCNode* background,
                               CCNode* label,
                               CCControl* cancel,
                               CCControl* okay,
                               CCFiniteTimeAction* inTransition,
                               CCFiniteTimeAction* outTransition )
{
    if( label && background && okay && cancel && super::init() )
    {
        this->removeAllChildrenWithCleanup( true );
        
        CCDirector* director = CCDirector::sharedDirector();
        const CCSize winSize = director->getWinSize();
        const CCPoint winCenter = ccpMidpoint( CCPointZero, ccpFromSize( winSize ) );
        
        const CCSize backroundSize = background->getContentSize();
        const CCPoint backgroundScale = ccpMult( ccpFromSize( backroundSize ), background->getScale() );
        const CCSize labelSize = label->getContentSize();
        const CCPoint labelScale = ccpMult( ccpFromSize( labelSize ), label->getScale() );
        const CCSize okaySize = okay->getContentSize();
        const CCPoint okayScale = ccpMult( ccpFromSize( okaySize ), okay->getScale() );
        const CCSize cancelSize = cancel->getContentSize();
        const CCPoint cancelScale = ccpMult( ccpFromSize( cancelSize ), cancel->getScale() );
        const CCPoint backgroundCenter = ccpMidpoint( CCPointZero, backgroundScale );
        
        const float horizontalPadding = ((backgroundScale.x - okayScale.x) - cancelScale.x) * 0.5f;
        const CCSize optionsSize = CCSizeMake( backgroundScale.x - (horizontalPadding * 0.5f), fmaxf( okayScale.y, cancelScale.y ) );
        const float verticalPadding = ((backgroundScale.y - optionsSize.height) - labelScale.y) * 0.5f;
        
        const CCPoint labelPoint = ccp( backgroundCenter.x, backgroundCenter.y + (verticalPadding * 0.5f) );
        const CCPoint cancelPoint = ccp( (horizontalPadding + cancelScale.x) * 0.5f, (verticalPadding + optionsSize.height) * 0.5f );
        const CCPoint okayPoint = ccp( (horizontalPadding * 1.5f) + cancelScale.x + (okayScale.x * 0.5f), (verticalPadding + optionsSize.height) * 0.5f );
        label->setPosition( labelPoint );
        cancel->setPosition( cancelPoint );
        okay->setPosition( okayPoint );
        
        cancel->addTargetWithActionForControlEvents( this, cccontrol_selector(CCConfirmMessage::transitionOut), CCControlEventTouchUpInside );
        okay->addTargetWithActionForControlEvents( this, cccontrol_selector(CCConfirmMessage::transitionOut), CCControlEventTouchUpInside );
        
        this->setContentSize( backroundSize );
        background->setPosition( backgroundCenter );
        
        this->addChild( background, Child::Z::background, Child::CCNode_background );
        this->addChild( label, Child::Z::label, Child::CCNode_label );
        this->addChild( cancel, Child::Z::options, Child::CCControl_cancel );
        this->addChild( okay, Child::Z::options, Child::CCControl_okay );
        
        this->setInTransition( inTransition );
        this->setOutTransition( outTransition );
    }
    
    return true;
}

void CCConfirmMessage::onEnter()
{
    super::onEnter();
    CCFiniteTimeAction* transition = this->getInTransition();
    if( transition && !transition->getTarget() )
    {
        this->setTouchEnabled( false );
        CCCallFunc* enter = CCCallFuncND::create( this, callfuncND_selector(CCConfirmMessage::setTouchEnabled), (void*)true );
        this->runAction( CCSequence::createWithTwoActions( transition, enter ) );
    }
}

void CCConfirmMessage::transitionOut()
{
    CCFiniteTimeAction* transition = this->getOutTransition();
    if( transition && !transition->getTarget() )
    {
        CCCallFunc* exit = CCCallFunc::create( this, callfunc_selector(CCConfirmMessage::removeFromParentAndCleanup) );
        this->runAction( CCSequence::createWithTwoActions( transition, exit ) );
    }
}