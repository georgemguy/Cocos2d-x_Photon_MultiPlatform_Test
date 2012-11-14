#ifndef __SumNationOnline__CCNetworkLogic__
#define __SumNationOnline__CCNetworkLogic__

#include "NetworkLogic.h"
#include "OutputListener.h"
#include "cocos2d.h"
#include <iostream>

class CCNetworkLogic: public NetworkLogic, public OutputListener, public NetworkLogicListener, public cocos2d::CCObject
{
    CC_SYNTHESIZE( State, _networkState, NetworkState );
    CC_SYNTHESIZE_READONLY( cocos2d::CCString, _output, Output );
    CC_SYNTHESIZE_READONLY( ExitGames::Common::JString, _address, Address );

public:
	CCNetworkLogic();
        
	virtual void write(const ExitGames::Common::JString& str);
	
	virtual void writeLine(const ExitGames::Common::JString& str);
    
	virtual void stateUpdate(State newState);
    
    virtual ExitGames::Common::JString getStateString( State state );
    
    virtual void setAddress( const char* address );
};

#endif /* defined(__SumNationOnline__CCNetworkLogic__) */
