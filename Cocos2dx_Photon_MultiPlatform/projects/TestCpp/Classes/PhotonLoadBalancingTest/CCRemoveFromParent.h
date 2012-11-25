//
//  CCRemoveFromParent.h
//  UndeadInfection
//
//  Created by George Guy on 8/9/12.
//  Copyright (c) 2012 Perpetual Motion Studios. All rights reserved.
//

#ifndef CatAndToast_CCRemoveFromParent_h
#define CaTAndToast_CCRemoveFromParent_h

#include "cocos2d.h"
#include "GGUtil.h"

class CCRemoveFromParent : public cocos2d::CCCallFuncND
{
public:
    CCRemoveFromParent() : cocos2d::CCCallFuncND() {};
    virtual ~CCRemoveFromParent() {};
    static CCRemoveFromParent* create( cocos2d::CCNode* target, bool cleanup = true );
    
    //virtual CCRemoveFromParent* copyWithZone( cocos2d::CCZone* pZone );
    COPY_FUNC( CCRemoveFromParent, cocos2d::CCCallFuncND );
};

#endif
