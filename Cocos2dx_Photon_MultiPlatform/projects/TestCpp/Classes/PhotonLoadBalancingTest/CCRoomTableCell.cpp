#include "CCRoomTableCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCRoomTableCell::CCRoomTableCell()
{
    this->_label = NULL;
}

CCRoomTableCell::~CCRoomTableCell()
{
    this->setLabel( NULL );
}

bool CCRoomTableCell::init( const cocos2d::CCString& room )
{
    CCLabelTTF* label = CCLabelTTF::create( room.getCString(), "American Typewriter.ttf", 16 );
    this->setLabel( label );
    //label->setPosition( ccp( 32, 16 ) );
    label->setAnchorPoint( ccp( 0.0f, 0.0f ) );
    return true;
}

CCRoomTableCell* CCRoomTableCell::create( const cocos2d::CCString& room )
{
    CCRoomTableCell* ret = new CCRoomTableCell();
    if( ret && ret->init( room ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    return ret;
}