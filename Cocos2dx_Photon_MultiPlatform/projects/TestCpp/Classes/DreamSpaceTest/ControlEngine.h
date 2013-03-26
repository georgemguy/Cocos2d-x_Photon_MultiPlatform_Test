//
//  EngineView.h
//  SumNationOnline
//
//  Created by George Guy on 12/28/12.
//
//

#pragma once
#ifndef __SumNationOnline__ControlEngine__
#define __SumNationOnline__ControlEngine__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GGUtil.h"

class ControlEngine : public cocos2d::extension::CCControl
{
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCString, _backgroundName, BackgroundName );
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCString, _progressIndicatorName, ProgressIndicatorName );
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCString, _demandIndicatorName, DemandIndicatorName );
    
public:
    typedef cocos2d::extension::CCControl super;
    struct Child
    {
        enum _Tag
        {
            CCSprite_background,
            CCProgressTimer_foreProgressIndicator,
            CCProgressTimer_aftProgressIndicator,
            CCSprite_demandIndicator,
            CHILD_TAG_COUNT
        } Tag;
        
        struct Z
        {
            enum _ZOrder
            {
                background,
                progressIndicator,
                demandIndicator
            } ZOrder;
        };
    };
    
    virtual bool initProgressIndicator( int tag, cocos2d::CCPoint point, cocos2d::CCPoint anchor );
    virtual bool init( const char* background, const char* progressIndicator, const char* demandIndicator );
    static ControlEngine* create( const char* background, const char* progressIndicator, const char* demandIndicator );
    virtual void onEnter();
};

#endif /* defined(__SumNationOnline__EngineView__) */
