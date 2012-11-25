#ifndef __SumNationOnline__CCNetworkLogic__
#define __SumNationOnline__CCNetworkLogic__

#include "CCRoomInfo.h"
#include "NetworkLogic.h"
#include "OutputListener.h"
#include "cocos2d.h"
#include <iostream>

class CCNetworkLogic: public NetworkLogic, public OutputListener, public NetworkLogicListener, public cocos2d::CCObject
{
    CC_SYNTHESIZE_READONLY( cocos2d::CCString, _output, Output );

public:
	CCNetworkLogic();
        
	virtual void write(const ExitGames::Common::JString& str);
	
	virtual void writeLine(const ExitGames::Common::JString& str);
    
	virtual void stateUpdate(State newState);
    
    virtual cocos2d::CCString getStateString( State state );
    
    virtual CCRoomInfo getRoomInfoAtIndex( unsigned int index );
};

#endif /* defined(__SumNationOnline__CCNetworkLogic__) */
