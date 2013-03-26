//
//  CCDispatchScene.h
//  PhotonOnline
//
//  Created by George Guy on 12/23/12.
//
//

#ifndef __PhotonOnline__CCDispatchScene__
#define __PhotonOnline__CCDispatchScene__

#include "cocos2d.h"
#include "GGUtil.h"

#include "CCSpriteLayer.h"

class CCSpriteLayer : public cocos2d::CCLayer
{    
public:
    typedef cocos2d::CCLayer super;
    CCSpriteLayer();
    virtual ~CCSpriteLayer();
    CREATE_FUNC(CCSpriteLayer);
    
    virtual cocos2d::CCSpriteBatchNode* loadSpriteBatchNode( const char* sheetName, int zOrder );
    virtual cocos2d::CCSpriteBatchNode* getBatchForSprite( cocos2d::CCSprite* sprite );
    virtual void addChild( cocos2d::CCNode* node, int zOrder, int tag );
    virtual void setContentSize( const cocos2d::CCSize& size );
};

#endif /* defined(__PhotonOnline__CCDispatchScene__) */
