//
//  CCEventSpriteBatch.cpp
//  PhotonOnline
//
//  Created by George Guy on 12/25/12.
//
//

#include "CCEventSpriteBatch.h"
USING_NS_CC;

bool CCEventSpriteBatch::init( const char* eventName )
{
    if( eventName && CCSpriteBatchNode::init() )
    {
        this->setEventName( eventName );
        return true;
    }
    return false;
}

CCEventSpriteBatch* CCEventSpriteBatch::create( const char* eventName )
{
    CCEventSpriteBatch* ret = new CCEventSpriteBatch();
    
    if( ret && ret->init(eventName) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL(ret);
    }
    return ret;
}

void CCEventSpriteBatch::onEnter()
{
    super::onEnter();
    CCNotificationCenter* publisher = CCNotificationCenter::sharedNotificationCenter();
    
    const CCString& eventName = this->getEventName();
    publisher->addObserver( this, callfuncO_selector( CCEventSpriteBatch::addSpriteEvent ), eventName.getCString(), NULL );
}

void CCEventSpriteBatch::onExit()
{
    super::onExit();
    CCNotificationCenter* publisher = CCNotificationCenter::sharedNotificationCenter();
    
    const CCString& eventName = this->getEventName();
    publisher->removeObserver( this, eventName.getCString() );
}

void CCEventSpriteBatch::addSpriteEvent( cocos2d::CCObject* spriteObject )
{
    CCSprite* sprite = (CCSprite*) spriteObject;
    if( !sprite->getParent() )
    {
        if( sprite->getTexture()->getName() == this->getTexture()->getName() )
        {
            this->addChild( sprite );
        }
    }
}