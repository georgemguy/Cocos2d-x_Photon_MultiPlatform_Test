//
//  Stage.h
//  SumNationOnline
//
//  Created by George Guy on 12/23/12.
//
//

#ifndef __PerpetualMotionStudios__GameScene__
#define __PerpetualMotionStudios__GameScene__

#include "SneakyJoystickSkinnedBase.h"
#include "SneakyButtonSkinnedBase.h"

class PMSGameScene : public cocos2d::CCScene
{
public:
    typedef cocos2d::CCScene super;
    struct Child
    {
        enum _Tag
        {
            CCPhysicsSpriteLayer_game,
            ControlDualEngine_controls,
            CHILD_TAG_COUNT,
        } Tag;
        
        struct Z
        {
            enum _ZOrder
            {
                game = 0,
                controls = 1024,
                MAX_Z_ORDER
            } ZOrder;
        };
    };
    
    PMSGameScene();
    virtual ~PMSGameScene();
    virtual bool init();
    CREATE_FUNC(PMSGameScene);
    virtual void onEnter();
};

#endif /* defined(__SumNationOnline__Stage__) */
