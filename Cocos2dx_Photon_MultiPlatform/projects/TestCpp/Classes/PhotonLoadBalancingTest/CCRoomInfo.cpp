//
//  CCRoomInfo.cpp
//  TestCpp
//
//  Created by George Guy on 11/19/12.
//
//

#include "CCRoomInfo.h"

using namespace ExitGames;
using namespace LoadBalancing;
using namespace Common;
using namespace cocos2d;

CCRoomInfo::CCRoomInfo( super& room ) : Room( room )
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
    return this->getNameStr().getCString();
}

CCRoomInfo& CCRoomInfo::operator=( const CCRoomInfo &rhs )
{
    if( this != &rhs )
    {
        ( (Room) *this ) = (Room) rhs;
    }
    
    return *this;
}

int CCRoomInfo::getRoomPropertyInt( const char* key )
{
    Hashtable properties = this->getCustomProperties();

    if( properties.contains<JString>(key) )
    {
        JString jStr = properties.getValue<JString>(key)->toString();

        if( jStr.length() )
        {
            return jStr.toInt();
        }
    }
    return -1;
}

int CCRoomInfo::getRoomPropertyInt( int key )
{
    CCAssert( key >= 0 && key < SumNationHashKey::HASH_KEY_COUNT, "CCNetworkLogic::getRoomPropertyInt() -- Invalid hash key!" );
    Hashtable properties = this->getCustomProperties();

    if( properties.contains<int>(key) )
    {
        JString jStr = properties.getValue<int>(key)->toString();

        if( jStr.length() )
        {
            return jStr.toInt();
        }
    }
    return this->getRoomPropertyInt( SumNationHashKey::getString( (SumNationHashKey::HashInt) key ) );
}

cocos2d::CCString CCRoomInfo::getRoomPropertyString( const char* key )
{
    Hashtable properties = this->getCustomProperties();
    const Object* value = properties.getValue<JString>(key);

    if( value )
    {
        return value->toString().ANSIRepresentation().cstr();
    }
    return "";
}

cocos2d::CCString CCRoomInfo::getRoomPropertyString( int key )
{
    Hashtable properties = this->getCustomProperties();
    const Object* value = properties.getValue<int>(key);

    if( value )
    {
        return value->toString().ANSIRepresentation().cstr();
    }
    return "";
}
