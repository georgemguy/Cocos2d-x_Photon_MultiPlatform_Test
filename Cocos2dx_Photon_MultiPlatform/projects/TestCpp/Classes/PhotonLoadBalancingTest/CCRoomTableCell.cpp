#include "CCRoomTableCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCRoomTableCell::CCRoomTableCell() : CCTableViewCell()
{
    this->_roomInfo = NULL;
    this->_label = NULL;
}

CCRoomTableCell::~CCRoomTableCell()
{
    CC_SAFE_RELEASE_NULL( this->_roomInfo );
    this->setLabel( NULL );
}

bool CCRoomTableCell::init( CCRoomInfo room )
{
    this->setRoomInfo( room );
    return true;
}

CCRoomTableCell* CCRoomTableCell::create( CCRoomInfo room )
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

CCRoomInfo* CCRoomTableCell::getRoomInfo()
{
    return this->_roomInfo;
}

void CCRoomTableCell::setRoomInfo( CCRoomInfo room )
{
    CC_SAFE_RELEASE_NULL( this->_roomInfo );
    
    this->_roomInfo = (CCRoomInfo*) (new CCRoomInfo( room ))->autorelease();
    _roomInfo->retain();
    CCString str = this->_roomInfo->toString();

    CCLabelTTF* label = this->getLabel();
    if( label )
    {
        label->setString( str.getCString() );
    }
    else
    {
        label = CCLabelTTF::create( str.getCString(), "American Typewriter.ttf", 16 );
        label->setAnchorPoint( ccp( 0.0f, 0.0f ) );
        this->setLabel( label );
    }
}