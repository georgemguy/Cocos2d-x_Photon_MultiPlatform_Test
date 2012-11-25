#include "CCNetworkLogic.h"

USING_NS_CC;
using namespace ExitGames;
using namespace Common;
using namespace LoadBalancing;

CCNetworkLogic::CCNetworkLogic()
: NetworkLogic(this, "1.0.0.0")
{
    registerForStateUpdates(this);
    _output = "";
}

void CCNetworkLogic::write(const ExitGames::Common::JString& str)
{
    //[mConsole write:[NSString stringWithUTF8String:str.UTF8Representation().cstr()]];
    /*using namespace std;
    
    CCString ccOutput = this->getOutput();
    const char* cOutput = ccOutput.getCString();
    string cppOutput = string( cOutput );
    
    const char* cStr = str.UTF8Representation().cstr();
    string cppStr = string( cStr );
    
    this->_output = cppOutput + cppStr;*/
    CCLOG( "%s", str.UTF8Representation().cstr() );
}

CCRoomInfo CCNetworkLogic::getRoomInfoAtIndex( unsigned int index )
{
    return CCRoomInfo( mLoadBalancingClient.getRoomList().getElementAt( index ) );
}

void CCNetworkLogic::writeLine(const ExitGames::Common::JString& str)
{
    //[mConsole writeLine:[NSString stringWithUTF8String:str.UTF8Representation().cstr()]];
    using namespace std;

    const char* cStr = str.UTF8Representation().cstr();
    string cppStr = string( cStr );
    
    //this->_output = cppStr;
    this->_output = str.UTF8Representation().cstr();
    CCLOG( "%s", str.UTF8Representation().cstr() );
}

void CCNetworkLogic::stateUpdate(State newState)
{
    //[mAppDelegate stateUpdate:newState];
    
    //this->_output = this->getStateString( newState );
    //CCLOG( "State = %d", newState );
}

CCString CCNetworkLogic::getStateString(State state)
{
	switch(state)
	{
		case STATE_INITIALIZED:
			return "disconnected";
        case STATE_WAITING:
            return "connecting";
		case STATE_CONNECTING:
			return "connecting";
		case STATE_CONNECTED:
			return "connected";
		case STATE_JOINING:
			return "joining";
		case STATE_JOINED:
			return "joined";
		case STATE_LEAVING:
			return "leaving";
		case STATE_LEFT:
			return "left";
		case STATE_DISCONNECTING:
			return "disconnecting";
		case STATE_DISCONNECTED:
			return "disconnected";
		default:
			return "unknown state";
	}
}