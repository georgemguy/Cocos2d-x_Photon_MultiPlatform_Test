//
//  CCRoomInfo.cpp
//  TestCpp
//
//  Created by George Guy on 11/19/12.
//
//

#include "CCRoomInfo.h"

CCRoomInfo::CCRoomInfo( ExitGames::LoadBalancing::Room& room ) : Room( room )
{
}

cocos2d::CCString CCRoomInfo::getNameStr()
{
    return this->getName().UTF8Representation().cstr();
}

cocos2d::CCString CCRoomInfo::getIsOpenStr()
{
    if( this->getIsOpen() ) return "open";
    else return "closed";
}

cocos2d::CCString CCRoomInfo::getMaxPlayersStr()
{
    char numStr[ 32 ] = { '\0' };
    sprintf( numStr, "%u", this->getMaxPlayers() );
    return numStr;
}

cocos2d::CCString CCRoomInfo::getPlayerCountStr()
{
    char numStr[ 32 ] = { '\0' };
    sprintf( numStr, "%u", this->getPlayerCount() );
    return numStr;
}

cocos2d::CCString CCRoomInfo::toString()
{
    using namespace std;
    string space = "     ";
    string ret = this->getNameStr().getCString() + space;
    ret += this->getIsOpenStr().getCString() + space;
    //ret += this->getMaxPlayersStr().getCString() + space;
    //ret += this->getPlayerCountStr().getCString();
    return ret.c_str();
}

CCRoomInfo& CCRoomInfo::operator=( const CCRoomInfo &rhs )
{
    if( this != &rhs )
    {
        ( (Room) *this ) = (Room) rhs;
    }
    
    return *this;
}