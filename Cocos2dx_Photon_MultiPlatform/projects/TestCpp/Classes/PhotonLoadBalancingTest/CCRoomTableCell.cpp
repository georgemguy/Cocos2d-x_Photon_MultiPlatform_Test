/****************************************************************************
 Copyright (c) 2013 George Guy

 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCRoomTableCell.h"
#include "CCNetworkLogic.h"
#include "../testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ExitGames;
using namespace LoadBalancing;
using namespace Common;

bool CCRoomTableCell::getHasRoom()
{
    return this->_hasRoom;
}

void CCRoomTableCell::setHasRoom(bool hasRoom)
{
    this->_hasRoom = hasRoom;
}

CCRoomTableCell::CCRoomTableCell() : CCTableViewCell(),
_label(NULL),
_roomInfo(NULL)
{
}

CCRoomTableCell::~CCRoomTableCell()
{
    this->setLabel( NULL );
}

bool CCRoomTableCell::init()
{
    this->_roomInfo = NULL;
    this->setHasRoom( false );

    CCLabelTTF* label = CCLabelTTF::create( "No room!", f_AmericanTypewriter, 16 );
    label->setAnchorPoint( ccp( 0.0f, 0.0f ) );
    this->setLabel( label );
    return true;
}

bool CCRoomTableCell::init( Room& room )
{
    this->setHasRoom( true );
    this->setRoom( &room );
    return true;
}

CCRoomTableCell* CCRoomTableCell::create( Room& room )
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

Room* CCRoomTableCell::getRoom()
{
    return this->_roomInfo;
}

void CCRoomTableCell::setRoom( Room* room )
{
	using namespace std;

    this->_room = room;

	string stdStr = this->_room->toString().UTF8Representation().cstr();
    ostringstream capacity;
    capacity << this->_roomInfo->getMaxPlayers();
    string stdCap = capacity.str();
	stdStr = string( "Room " ) + stdStr;

    CCLabelTTF* label = this->getLabel();
    if( label )
    {
        label->setString( stdStr.c_str() );
    }
    else
    {
        label = CCLabelTTF::create( stdStr.c_str(), f_AmericanTypewriter, 16 );
        label->setAnchorPoint( ccp( 0.0f, 0.0f ) );
        this->setLabel( label );
    }
}
