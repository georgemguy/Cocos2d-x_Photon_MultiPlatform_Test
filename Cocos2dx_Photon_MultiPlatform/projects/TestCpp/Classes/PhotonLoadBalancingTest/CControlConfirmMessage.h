//
//  ControlConfirmMessage.h
//  Abstroku
//
//  Created by George Guy on 9/14/12.
//
//

#ifndef Abstroku_ControlConfirmMessage_h
#define Abstroku_ControlConfirmMessage_h

#include "CaTUtil.h"
#include "cocos2d.h"
#include "CCControlExtensions.h"

class ControlConfirmMessage : public cocos2d::extension::CCControlButton
{
    CAT_SYNTHESIZE_CONTROL(_cancel, Cancel);
    CAT_SYNTHESIZE_CONTROL(_okay, Okay);

public:
    ControlConfirmMessage();
    ~ControlConfirmMessage();
    
    virtual bool init(
                      const char* message,
                      cocos2d::CCObject* okayTarget,
                      cocos2d::extension::SEL_CCControlHandler okayCallback );

    static ControlConfirmMessage* create(
                                         const char* message,
                                         cocos2d::CCObject* okayTarget,
                                         cocos2d::extension::SEL_CCControlHandler okayCallback );
    
    virtual void onEnter();
    virtual void onExit();
};

#endif
