//
//  CCRoomInfo.h
//  TestCpp
//
//  Created by George Guy on 11/19/12.
//
//

#pragma once
#ifndef __TestCpp__CCRoomInfo__
#define __TestCpp__CCRoomInfo__

#include "cocos2d.h"
#include "LoadBalancingClient.h"

struct CCRoomInfo : public cocos2d::CCObject, public ExitGames::LoadBalancing::Room
{
	typedef ExitGames::LoadBalancing::Room super;
    cocos2d::CCString getNameStr();
    cocos2d::CCString getIsOpenStr();
    cocos2d::CCString getMaxPlayersStr();
    cocos2d::CCString getPlayerCountStr();
    
    CCRoomInfo( super& room );
    virtual CCRoomInfo& operator=(const CCRoomInfo &rhs);
    virtual cocos2d::CCString toString();

    virtual cocos2d::CCString getRoomPropertyString( int key );
    virtual cocos2d::CCString getRoomPropertyString( const char* key );
    virtual int getRoomPropertyInt( int key );
    virtual int getRoomPropertyInt( const char* key );
};

#endif /* defined(__TestCpp__CCRoomInfo__) */
