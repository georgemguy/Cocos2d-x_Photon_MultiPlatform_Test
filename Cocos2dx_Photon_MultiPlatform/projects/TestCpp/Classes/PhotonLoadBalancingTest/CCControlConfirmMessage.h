//
//  CCControlConfirmMessage.h
//  Abstroku
//
//  Created by George Guy on 9/14/12.
//
//

#ifndef Abstroku_CCControlConfirmMessage_h
#define Abstroku_CCControlConfirmMessage_h

#include "GGUtil.h"
#include "cocos2d.h"
#include "CCControlExtensions.h"

class CCControlConfirmMessage : public cocos2d::extension::CCControlButton
{
    CC_SYNTHESIZE_CONTROL(_cancel, Cancel);
    CC_SYNTHESIZE_CONTROL(_okay, Okay);

public:
    CCControlConfirmMessage();
    ~CCControlConfirmMessage();
    
    virtual bool init(
                      const char* message,
                      const char* fontName,
                      const char* button1Name,
                      const char* button2Name,
                      const cocos2d::CCSize& mySize,
                      cocos2d::CCObject* okayTarget,
                      cocos2d::extension::SEL_CCControlHandler okayCallback );

    static CCControlConfirmMessage* create(
                                         const char* message,
                                         const char* fontName,
                                         const char* button1Name,
                                         const char* button2Name,
                                         const cocos2d::CCSize& mySize,
                                         cocos2d::CCObject* okayTarget,
                                         cocos2d::extension::SEL_CCControlHandler okayCallback );
    
    virtual void onEnter();
    virtual void onExit();
};

#endif
