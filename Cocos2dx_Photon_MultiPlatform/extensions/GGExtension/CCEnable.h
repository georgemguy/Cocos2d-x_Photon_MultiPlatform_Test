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
    virtual ~CCEnable(){};
    CC_SYNTHESIZE(bool, _toEnable, ToEnable);

public:
    virtual bool init( bool toEnable );
    virtual void update( float delta );
    static CCEnable* create( bool toEnable );
    COPY_INIT_FUNC(CCEnable, cocos2d::CCActionInstant, init( this->getToEnable() ) );
};

#endif
