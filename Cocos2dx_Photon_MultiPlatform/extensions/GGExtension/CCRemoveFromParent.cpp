//
//  CCRemoveFromParent.cpp
//  UndeadInfection
//
//  Created by George Guy on 8/9/12.
//  Copyright (c) 2012 Perpetual Motion Studios. All rights reserved.
//

#include "CCRemoveFromParent.h"

USING_NS_CC;

CCRemoveFromParent* CCRemoveFromParent::create( CCNode* target, bool cleanup )
{
    CCRemoveFromParent* pRet = new CCRemoveFromParent();
    
    if (pRet && pRet->initWithTarget( target, callfuncND_selector(CCNode::removeFromParentAndCleanup), (void*) cleanup ) )
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE( pRet );
    }
    
    return pRet;
}