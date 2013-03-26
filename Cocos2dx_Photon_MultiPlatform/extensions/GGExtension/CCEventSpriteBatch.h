//
//  CCEventSpriteBatch.h
//  PhotonOnline
//
//  Created by George Guy on 12/25/12.
//
//

#ifndef __PhotonOnline__CCEventSpriteBatch__
#define __PhotonOnline__CCEventSpriteBatch__

#include "cocos2d.h"

class CCEventSpriteBatch : public cocos2d::CCSpriteBatchNode
{
public:
    typedef CCEventSpriteBatch super;
    CC_SYNTHESIZE_PASS_BY_REF( cocos2d::CCString, _eventName, EventName );
    virtual bool init( const char* eventName );
    static CCEventSpriteBatch* create( const char* eventName );
    virtual void onEnter();
    virtual void onExit();
    virtual void addSpriteEvent( cocos2d::CCObject* spriteObject );
};

#endif /* defined(__PhotonOnline__CCEventSpriteBatch__) */
