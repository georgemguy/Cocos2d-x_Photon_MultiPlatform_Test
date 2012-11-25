//
//  CCEnable.h
//  Abstroku
//
//  Created by George Guy on 9/17/12.
//
//

#ifndef Abstroku_CCEnable_h
#define Abstroku_CCEnable_h

#include "cocos2d.h"
#include "GGUtil.h"

class CCEnable : public cocos2d::CCActionInstant
{
    CC_SYNTHESIZE(bool, _toEnable, ToEnable);
    CC_SYNTHESIZE(bool, _enableTouch, EnableTouch);
    CC_SYNTHESIZE(bool, _enableControl, EnableControl);

public:
    virtual bool init( bool toEnable, bool enableTouch, bool enableControl );
    virtual void update( float delta );
    static CCEnable* create( bool toEnable, bool enableTouch = true, bool enableControl = true );
    COPY_INIT_FUNC(CCEnable, cocos2d::CCActionInstant, init( this->getToEnable(), this->getEnableTouch(), this->getEnableControl() ) );
};

#endif
