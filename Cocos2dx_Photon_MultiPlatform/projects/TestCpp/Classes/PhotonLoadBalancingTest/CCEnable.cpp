//
//  CCEnable.cpp
//  Abstroku
//
//  Created by George Guy on 9/17/12.
//
//

#include "CCEnable.h"
#include "CCControlExtensions.h"

USING_NS_CC;
USING_NS_CC_EXT;

void CCEnable::update( float delta )
{
    if( this->getEnableTouch() )
    {
        this->setEnableTouch( this->getToEnable() );
    }
    
    if( this->getEnableControl() )
    {
        CCControl* target = dynamic_cast<CCControl*>(this->getTarget());
        if( target )
        {
            target->setEnabled( this->getToEnable() );
        }
    }
}

bool CCEnable::init( bool toEnable, bool enableTouch, bool enableControl )
{
    this->setToEnable( toEnable );
    return true;
}

CCEnable* CCEnable::create( bool toEnable, bool enableTouch, bool enableControl )
{
    CCEnable* ret = new CCEnable();
    
    if( ret && ret->init( toEnable, enableTouch, enableControl ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}