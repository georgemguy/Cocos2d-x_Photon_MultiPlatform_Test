//
//  PMSGameLayer.cpp
//  SumNationOnline
//
//  Created by George Guy on 12/25/12.
//
//

#include "PMSGameLayer.h"
#include "CCEventSpriteBatch.h"
USING_NS_CC;

PMSGameLayer::PMSGameLayer() : super()
{
    this->_model = NULL;
    this->_bounder = NULL;
}

PMSGameLayer::~PMSGameLayer()
{
    this->deactivateBounder();
    CC_SAFE_DELETE( this->_model );
}

const CCString PMSGameLayer::Child::Z::zOrderToEvent(PMSGameLayer::Child::Z::_ZOrder z)
{
    switch ( z )
    {
        case Child::Z::lowItem:
            return "create_low_item_event";
            
        case Child::Z::highItem:
            return "create_high_item_event";
        
        case Child::Z::actor:
        case Child::Z::mask:
        case Child::Z::objBase:
        case Child::Z::levelBase:
        case Child::Z::objTop:
        case Child::Z::levelTop:
            return "create_event";
        default:
            CCAssert( false, "PMSGameLayer::Child::Z::tagToZOrder() -- invalid tag!" );
    }
}

void PMSGameLayer::onEnter()
{
    super::onEnter();
}

void PMSGameLayer::loadEventSpriteBatch( const char *plist, Child::Z::_ZOrder z, int tag )
{
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(plist);
    CCString event = Child::Z::zOrderToEvent(z);
    CCEventSpriteBatch* batch = CCEventSpriteBatch::create( event.getCString() );
    batch->setContentSize( this->getContentSize() );
    this->addChild( batch, z, tag );
}

void PMSGameLayer::setContentSize(const cocos2d::CCSize &size)
{
    CCArray* children = this->getChildren();
    CCObject* o = NULL;
    CCSpriteBatchNode* batch = NULL;
    CCARRAY_FOREACH(children, o)
    {
        batch = (CCSpriteBatchNode*) o;
        batch->setContentSize( this->getContentSize() );
    }
}

void PMSGameLayer::update( float delta )
{
    this->getModel()->Step( delta, this->getVelocityIterations(), this->getPositionIterations() );
}

void PMSGameLayer::activateBounder()
{
    this->deactivateBounder();
    
    CCSize s = this->getContentSize();
    
    b2World* world = this->getModel();
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    this->_bounder = world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
    _bounder->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    _bounder->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    _bounder->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
    _bounder->CreateFixture(&groundBox,0);
}

void PMSGameLayer::deactivateBounder()
{
    if( this->_bounder && this->getModel() ) this->getModel()->DestroyBody( _bounder );
    this->_bounder = NULL;
}

bool PMSGameLayer::init( const cocos2d::CCSize& bounderSize )
{
    if( super::init() )
    {
        this->setContentSize( bounderSize );
        CC_SAFE_DELETE(this->_model);
        this->_model = new b2World( b2Vec2_zero );
        this->setVelocityIterations( 1 );
        this->setPositionIterations( 1 );
        this->setContentSize( bounderSize );
        this->activateBounder();
        return true;
    }
    return false;
}

PMSGameLayer* PMSGameLayer::create( const cocos2d::CCSize& bounderSize )
{
    PMSGameLayer* ret = new PMSGameLayer();
    
    if( ret && ret->init( bounderSize ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE( ret );
    }
    return ret;
}