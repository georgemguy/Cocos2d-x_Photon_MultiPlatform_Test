//
//  CCSwallowLayer.cpp
//  PhotonOnline
//
//  Created by George Guy on 12/10/12.
//
//

#include "CCSwallowLayer.h"

USING_NS_CC;

bool CCSwallowLayer::init()
{
    if( super::init() )
    {
        this->setTouchEnabled( true );
        this->scheduleUpdate();
        return true;
    }
    
    return false;
}

bool CCSwallowLayer::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
    
    if( this->boundingBox().containsPoint( touchLocation ) )
    {
        return true;
    }
    
    return true;
}
