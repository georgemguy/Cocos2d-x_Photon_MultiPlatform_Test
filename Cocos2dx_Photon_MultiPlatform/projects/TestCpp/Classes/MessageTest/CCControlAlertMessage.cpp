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

#include "CCControlAlertMessage.h"
#include "../testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCControlAlertMessage* CCControlAlertMessage::create( const char* message )
{
    CCControlAlertMessage *pRet = new CCControlAlertMessage();
    pRet->init( message );
    pRet->autorelease();
    return pRet;
}

bool CCControlAlertMessage::init( const char* message )
{
    CCDirector* director = CCDirector::sharedDirector();
    CCSize size = director->getWinSize();
    CCPoint point = ccpMult( ccpFromSize( size ), 0.5f );
    CCRect messageRect = CCRectZero;
    messageRect.size = CCSizeMake( size.width * 0.5f, size.height * 0.5f );
    
    this->setPosition( point );
    
    CCLabelTTF* label = CCLabelTTF::create(
                                           message,
                                           f_AmericanTypewriter, 20,
                                           messageRect.size,
                                           kCCTextAlignmentCenter,
                                           kCCVerticalTextAlignmentCenter );
    ccColor3B color;
    color.b = 255;
    color.r = 50;
    color.g = 50;
    label->setColor( color );
    
    CCScale9Sprite* sprite = CCScale9Sprite::create( "wood2_1.png", messageRect );
    
    if( this->initWithLabelAndBackgroundSprite( label, sprite ) )
    {
        this->addTargetWithActionForControlEvent(
                                                 this,
                                                 cccontrol_selector(CCControlAlertMessage::controlCallbackCancel),
                                                 CCControlEventTouchUpInside );
        return true;
    }
    
    this->setTitleForState( NULL, CCControlStateNormal );
    CC_SAFE_DELETE( label );
    CC_SAFE_DELETE( sprite );
    return false;
}

void CCControlAlertMessage::controlCallbackCancel( cocos2d::CCObject* source )
{
    this->runAction( CCCallFuncND::create( this, callfuncND_selector( CCControlAlertMessage::removeFromParentAndCleanup ), (void*)true ) );
}

void CCControlAlertMessage::onEnter()
{
	CCControl::onEnter();
	this->enableChild( CCDirector::sharedDirector()->getRunningScene(), false );
	this->enableChildren( CCDirector::sharedDirector()->getRunningScene(), false );
}

void CCControlAlertMessage::onExit()
{
	CCControl::onExit();
	this->enableChild( CCDirector::sharedDirector()->getRunningScene(), true );
	this->enableChildren( CCDirector::sharedDirector()->getRunningScene(), true );
}

void CCControlAlertMessage::enableChild( CCNode* child, bool enable )
{
	CCMenu* targetMenu = dynamic_cast<CCMenu*>(child);
	if( targetMenu )
	{
		targetMenu->setTouchEnabled( enable );
	}
	else
	{
		CCScrollView* targetScroll = dynamic_cast<CCScrollView*>(child);
		if( targetScroll )
		{
			targetScroll->setTouchEnabled( enable );
		}
		else
		{
			CCControl* targetControl = dynamic_cast<CCControl*>(child);
			if( targetControl )
			{
				targetControl->setEnabled( enable );
			}
		}
	}
}

void CCControlAlertMessage::enableChildren( CCNode* target, bool enable )
{
	CCObject* o;
	CCNode* child;
	CCARRAY_FOREACH( target->getChildren(), o )
	{
		child = (CCNode*) o;
	    if( child != this )
	    {
			this->enableChild( child, enable );
			this->enableChildren( child, enable );
	    }
	}
}
