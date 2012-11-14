#include "CCNetworkLogic.h"

USING_NS_CC;
using namespace ExitGames;
using namespace Common;

CCNetworkLogic::CCNetworkLogic()
: NetworkLogic(this, "1.0.0.0")
{
    registerForStateUpdates(this);
    this->setNetworkState( STATE_INITIALIZED );
    _output = "";
}

void CCNetworkLogic::setAddress( const char* address )
{
    this->_address = JString( address );
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

void CCNetworkLogic::writeLine(const ExitGames::Common::JString& str)
{
    //[mConsole writeLine:[NSString stringWithUTF8String:str.UTF8Representation().cstr()]];
    using namespace std;

    const char* cStr = str.UTF8Representation().cstr();
    string cppStr = string( cStr );
    
    //this->_output = cppStr;
    CCLOG( "%s", str.UTF8Representation().cstr() );
}

void CCNetworkLogic::stateUpdate(State newState)
{
    //[mAppDelegate stateUpdate:newState];
    this->setNetworkState( newState );
    
    this->_output = this->getStateString( newState ).ANSIRepresentation().cstr();
    //CCLOG( "State = %d", newState );
}

ExitGames::Common::JString CCNetworkLogic::getStateString(State state)
{
	switch(state)
	{
		case STATE_INITIALIZED:
			return L"disconnected";
        case STATE_WAITING:
            return L"connecting";
		case STATE_CONNECTING:
			return L"connecting";
		case STATE_CONNECTED:
			return L"connected";
		case STATE_JOINING:
			return L"joining";
		case STATE_JOINED:
			return L"joined";
		case STATE_LEAVING:
			return L"leaving";
		case STATE_LEFT:
			return L"left";
		case STATE_DISCONNECTING:
			return L"disconnecting";
		case STATE_DISCONNECTED:
			return L"disconnected";
		default:
			return L"unknown state";
	}
}