//
//  EngineView.cpp
//  SumNationOnline
//
//  Created by George Guy on 12/28/12.
//
//

#include "ControlEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool ControlEngine::initProgressIndicator( int tag, cocos2d::CCPoint point, cocos2d::CCPoint anchor )
{
    CCSprite* progressIndicatorSprite = CCSprite::create( this->getProgressIndicatorName().getCString() );
    if( progressIndicatorSprite )
    {
        CCProgressTimer* progressIndicator = CCProgressTimer::create( progressIndicatorSprite );
        if( progressIndicator )
        {
            progressIndicator->ignoreAnchorPointForPosition( false );
            progressIndicator->setAnchorPoint( anchor );
            progressIndicator->setPosition( point );
            this->addChild( progressIndicator, Child::Z::progressIndicator, tag );
            return true;
        }
    }
    return false;
}

bool ControlEngine::init( const char* backgroundName, const char* progressIndicatorName, const char* demandIndicatorName )
{
    if( super::init() )
    {
        this->setBackgroundName( backgroundName );
        this->setProgressIndicatorName( progressIndicatorName );
        this->setDemandIndicatorName( demandIndicatorName );
        
        CCSprite* background = CCSprite::create( backgroundName );
        CCSize size = background->getContentSize();
        CCPoint sizePoint = ccpFromSize(size);
        CCPoint center = ccpMult( sizePoint, 0.5f );
        this->setContentSize( size );
        this->ignoreAnchorPointForPosition( false );
        
        background->setPosition( center );
        this->addChild( background, Child::Z::background, Child::CCSprite_background );
        
        this->initProgressIndicator( Child::CCProgressTimer_foreProgressIndicator, center, ccp( 0.5f, 0 ) );
        this->initProgressIndicator( Child::CCProgressTimer_aftProgressIndicator, center, ccp( 0.5f, 1 ) );
        
        CCSprite* demandIndicator = CCSprite::create( demandIndicatorName );
        demandIndicator->setPosition( ccp( size.width * 0.5f, 0.0f ) );
        this->addChild( demandIndicator, Child::Z::demandIndicator, Child::CCSprite_demandIndicator );
        
        return true;
    }
    return false;
}

ControlEngine* ControlEngine::create( const char* backgroundName, const char* progressIndicatorName, const char* demandIndicatorName )
{
    ControlEngine* ret = new ControlEngine();
    if( ret && ret->init( backgroundName, progressIndicatorName, demandIndicatorName ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL(ret);
    }
    return ret;
}

void ControlEngine::onEnter()
{
    CCControl::onEnter();
}