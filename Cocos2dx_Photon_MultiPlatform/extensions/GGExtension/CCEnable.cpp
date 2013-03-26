//
//  CCEnable.cpp
//  Abstroku
//
//  Created by George Guy on 9/17/12.
//
//

#include "CCEnable.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

void CCEnable::update( float delta )
{
	CCMenu* targetMenu = dynamic_cast<CCMenu*>(this->getTarget());
	if( targetMenu )
	{
		targetMenu->setTouchEnabled( this->getToEnable() );
	}
	else
	{
    	CCScrollView* targetScroll = dynamic_cast<CCScrollView*>(this->getTarget());
		if( targetScroll )
		{
			targetScroll->setTouchEnabled( this->getToEnable() );
		}
		else
		{
			CCControl* targetControl = dynamic_cast<CCControl*>(this->getTarget());
			if( targetControl )
			{
				targetControl->setEnabled( this->getToEnable() );
                targetControl->setTouchEnabled( this->getToEnable() );
			}
		}
	}
}

bool CCEnable::init( bool toEnable )
{
    this->setToEnable( toEnable );
    return true;
}

CCEnable* CCEnable::create( bool toEnable )
{
    CCEnable* ret = new CCEnable();
    
    if( ret && ret->init( toEnable ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}
