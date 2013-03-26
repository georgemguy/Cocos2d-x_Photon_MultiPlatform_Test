//
//  ControlDualEngine.cpp
//  SumNationOnline
//
//  Created by George Guy on 12/28/12.
//
//

#include "ControlDualEngine.h"
#include "ControlEngine.h"

USING_NS_CC;

bool ControlDualEngine::initEngine( int tag, cocos2d::CCPoint point, cocos2d::CCPoint anchor )
{
    ControlEngine* engine = ControlEngine::create(
                                                  this->getBackgroundName().getCString(),
                                                  this->getProgressIndicatorName().getCString(),
                                                  this->getDemandIndicatorName().getCString() );
    
    if( engine )
    {
        engine->setAnchorPoint( anchor );
        engine->setPosition( point );
        this->addChild( engine, ControlDualEngine::Child::Z::engines, tag );
        return true;
    }
    return false;
}

bool ControlDualEngine::init( const char* background, const char* progressIndicator, const char* demandIndicator )
{
    if( super::init() )
    {
        this->setBackgroundName( background );
        this->setProgressIndicatorName( progressIndicator );
        this->setDemandIndicatorName( demandIndicator );
        
        CCDirector* director = CCDirector::sharedDirector();
        CCSize winSize = director->getWinSize();
        CCPoint winSizePoint = ccpFromSize( winSize );
        CCPoint center = ccpMult( winSizePoint, 0.5f );
        this->setContentSize( winSize );
        
        this->initEngine( Child::ControlEngine_left, ccp( 0, center.y ), ccp( 0, 0.5f ) );
        this->initEngine( Child::ControlEngine_right, ccp( winSize.width, center.y ), ccp( 1, 0.5f ) );
        return true;
    }
    return false;
}

ControlDualEngine* ControlDualEngine::create( const char* background, const char* progressIndicatorSprite, const char* demandIndicator )
{
    ControlDualEngine* ret = new ControlDualEngine();
    if( ret && ret->init( background, progressIndicatorSprite, demandIndicator ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL(ret);
    }
    return ret;
}