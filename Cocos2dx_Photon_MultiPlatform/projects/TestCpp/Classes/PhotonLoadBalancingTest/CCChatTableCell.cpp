//
//  CCChatTableCell.cpp
//  TestCpp
//
//  Created by George Guy on 11/20/12.
//
//

#include "CCChatTableCell.h"
USING_NS_CC;
USING_NS_CC_EXT;

CCChatTableCell::CCChatTableCell() : CCTableViewCell()
{
}

CCChatTableCell::~CCChatTableCell()
{
}

bool CCChatTableCell::init( const char* message )
{
    CCAssert( message, "CCChatTableCell::init() -- message is NULL" );
    if( this->init( CCLabelTTF::create( message, "American Typewriter.ttf", 12 ) ) )
    {
        return true;
    }
    
    return false;
}

CCChatTableCell* CCChatTableCell::create( const char* message )
{
    CCChatTableCell* ret = new CCChatTableCell();
    
    if( ret && ret->init( message ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}

bool CCChatTableCell::init( cocos2d::CCLabelTTF* message )
{
    CCAssert( message, "CCChatTableCell::init() -- message is NULL" );
    this->addChild( message, 0, Child::CCLabelTTF_message );
    return true;
}

CCChatTableCell* CCChatTableCell::create( cocos2d::CCLabelTTF* message )
{
    CCChatTableCell* ret = new CCChatTableCell();
    
    if( ret && ret->init( message ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}