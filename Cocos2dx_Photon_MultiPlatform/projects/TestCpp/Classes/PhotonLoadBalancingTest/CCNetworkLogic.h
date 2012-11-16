#ifndef __SumNationOnline__CCNetworkLogic__
#define __SumNationOnline__CCNetworkLogic__

#include "NetworkLogic.h"
#include "OutputListener.h"
#include "cocos2d.h"
#include <iostream>

struct CCRoomInfo : public cocos2d::CCObject
{
    cocos2d::CCDictionary* customProperties;
    cocos2d::CCString name;
    cocos2d::CCString isOpen;
    cocos2d::CCString maxPlayers;
    cocos2d::CCString playerCount;
    
    CCRoomInfo()
    {
        this->customProperties = NULL;
    }
        
    ~CCRoomInfo()
    {
        CC_SAFE_RELEASE( this->customProperties );
    }
    
    CCRoomInfo( const ExitGames::LoadBalancing::Room& room );
};

class CCNetworkLogic: public NetworkLogic, public OutputListener, public NetworkLogicListener, public cocos2d::CCObject
{
    CC_SYNTHESIZE_READONLY( cocos2d::CCString, _output, Output );

public:
	CCNetworkLogic();
        
	virtual void write(const ExitGames::Common::JString& str);
	
	virtual void writeLine(const ExitGames::Common::JString& str);
    
	virtual void stateUpdate(State newState);
    
    virtual cocos2d::CCString getStateString( State state );
    
    virtual cocos2d::CCString getRoomInfoAtIndex( unsigned int index );
};

#endif /* defined(__SumNationOnline__CCNetworkLogic__) */
