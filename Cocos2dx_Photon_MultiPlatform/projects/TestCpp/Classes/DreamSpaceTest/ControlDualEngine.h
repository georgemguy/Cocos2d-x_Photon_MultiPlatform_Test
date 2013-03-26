//
//  ControlDualEngine.h
//  SumNationOnline
//
//  Created by George Guy on 12/28/12.
//
//

#ifndef __SumNationOnline__ControlDualEngine__
#define __SumNationOnline__ControlDualEngine__

#include "GGUtil.h"

class ControlDualEngine : public cocos2d::CCLayer
{
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCString, _backgroundName, BackgroundName );
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCString, _progressIndicatorName, ProgressIndicatorName );
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCString, _demandIndicatorName, DemandIndicatorName );
    
public:
    typedef cocos2d::CCLayer super;
    
    struct Child
    {
        enum _Tag
        {
            ControlEngine_left,
            ControlEngine_right,
            CHILD_TAG_COUNT
        } Tag;
        
        struct Z
        {
            enum _ZOrder
            {
                engines = 0,
                MAX_Z_ORDER
            } ZOrder;
        };
    };
    
    virtual bool initEngine( int tag, cocos2d::CCPoint point, cocos2d::CCPoint anchor );
    virtual bool init( const char* background, const char* progressIndicator, const char* demandIndicator );
    static ControlDualEngine* create( const char* background, const char* progressIndicator, const char* demandIndicator );
};

#endif /* defined(__SumNationOnline__ControlDualEngine__) */
