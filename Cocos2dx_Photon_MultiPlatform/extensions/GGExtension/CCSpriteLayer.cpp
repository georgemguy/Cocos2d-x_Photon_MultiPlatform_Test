//
//  CCSpriteLayer.cpp
//  PhotonOnline
//
//  Created by George Guy on 12/23/12.
//
//

#include "CCSpriteLayer.h"

USING_NS_CC;

CCSpriteLayer::CCSpriteLayer() : super()
{
}

CCSpriteLayer::~CCSpriteLayer()
{
    
}

void CCSpriteLayer::addChild(cocos2d::CCNode *node, int zOrder, int tag)
{
    CCSpriteBatchNode* batch = NULL;
    CCSprite* sprite = dynamic_cast<CCSprite*>(node);
    if( sprite )
    {
        batch = this->getBatchForSprite( sprite );
        if( batch )
        {
            batch->addChild( sprite, zOrder, tag );
            return;
        }
        CCAssert( false, "CCSpriteLayer::addChild() -- No matching batch for sprite!" );
    }
    
    batch = dynamic_cast<CCSpriteBatchNode*>(node);
    if( batch )
    {
        this->addChild( batch, zOrder, batch->getTexture()->getName() );
        return;
    }
    
    CCAssert( false, "CCSpriteLayer::addChild() -- CCSpriteLayer only supports children of classes CCSprite and CCSpriteBatchNode!" );
}

CCSpriteBatchNode* CCSpriteLayer::loadSpriteBatchNode( const char* sheetName, int zOrder )
{
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create( sheetName );
    batch->setContentSize( this->getContentSize() );
    
    this->addChild( batch, zOrder, batch->getTexture()->getName() );
    return batch;
}

CCSpriteBatchNode* CCSpriteLayer::getBatchForSprite( CCSprite* sprite )
{
    return (CCSpriteBatchNode*) this->getChildByTag( sprite->getTexture()->getName() );
}

void CCSpriteLayer::setContentSize(const cocos2d::CCSize &size)
{
    CCArray* children = this->getChildren();
    CCObject* o = NULL;
    CCSpriteBatchNode* batch = NULL;
    CCARRAY_FOREACH(children, o)
    {
        batch = (CCSpriteBatchNode*) o;
        batch->setContentSize( this->getContentSize() );
    }
}