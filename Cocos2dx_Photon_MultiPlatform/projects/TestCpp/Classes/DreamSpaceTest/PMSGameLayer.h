//
//  PMSGameLayer.h
//  SumNationOnline
//
//  Created by George Guy on 12/25/12.
//
//

#ifndef __SumNationOnline__PMSGameLayer__
#define __SumNationOnline__PMSGameLayer__

#include "cocos2d.h"
#include "CCBoxUtil.h"
#include "CCBodySprite.h"

using namespace CCBoxExtension;


class PMSGameLayer : public cocos2d::CCLayer
{
    CC_SYNTHESIZE_READONLY(b2World*, _model, Model);
    CC_SYNTHESIZE(int32, _velocityIterations, VelocityIterations);
    CC_SYNTHESIZE(int32, _positionIterations, PositionIterations);
    CC_SYNTHESIZE_READONLY(b2Body*, _bounder, Bounder);
    CC_SYNTHESIZE_READONLY(unsigned int, _lastBatchTag, LastBatchTag);
public:
    typedef cocos2d::CCLayer super;

    struct Child
    {
        struct Z
        {
            enum _ZOrder
            {
                Z_MIN = 0,
                levelBase = Z_MIN,
                objBase,
                lowItem,
                levelTop,
                objTop,
                actor,
                mask,
                highItem,
                UPPER_LIMIT
            } ZOrder;
            static const cocos2d::CCString zOrderToEvent( _ZOrder z );
        };
    };
    
    PMSGameLayer();
    virtual ~PMSGameLayer();
    
    
    virtual void onEnter();
    virtual void setContentSize( const cocos2d::CCSize& size );
    
    void loadEventSpriteBatch( const char* plist, Child::Z::_ZOrder z, int tag );
    
    virtual bool init( const cocos2d::CCSize& bounderSize );
    static PMSGameLayer* create( const cocos2d::CCSize& bounderSize );
    
    virtual void update( float delta );
    
    virtual void activateBounder();
    virtual void deactivateBounder();
};
#endif /* defined(__SumNationOnline__PMSGameLayer__) */
