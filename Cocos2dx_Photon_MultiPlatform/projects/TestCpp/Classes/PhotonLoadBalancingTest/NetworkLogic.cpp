#include "NetworkLogic.h"

#if defined _EG_MARMALADE_PLATFORM
#	if defined I3D_ARCH_X86
#		if(defined _MSC_VER && !defined __clang__ && !defined __gcc__)
#			define PLAYER_NAME "Marmalade X86 Windows"
#		else
#			define PLAYER_NAME "Marmalade X86 OS X"
#		endif
#	elif defined I3D_ARCH_ARM
#		define PLAYER_NAME "Marmalade ARM"
#	else
#		define PLAYER_NAME  "unknown Marmalade platform"
#	endif
#elif defined _EG_WINDOWS_PLATFORM
#	define PLAYER_NAME "Win32"
#elif defined _EG_IPHONE_PLATFORM
#	define PLAYER_NAME "iOS"
#elif defined _EG_IMAC_PLATFORM
#	define PLAYER_NAME "OS X"
#elif defined _EG_ANDROID_PLATFORM
#	define PLAYER_NAME "Android"
#elif defined _EG_BLACKBERRY_PLATFORM
#	define PLAYER_NAME "Blackberry"
#else
#	define PLAYER_NAME "unknown platform"
#endif

using namespace ExitGames;
using namespace Common;
using namespace LoadBalancing;

ExitGames::Common::JString& NetworkLogicListener::toString(ExitGames::Common::JString& retStr, bool withTypes) const
{
	return retStr;
}



State StateAccessor::getState(void) const
{
	return mState;
}

void StateAccessor::setState(State newState)
{
	mState = newState;
	for(unsigned int i=0; i<mStateUpdateListeners.getSize(); i++)
		mStateUpdateListeners[i]->stateUpdate(newState);
}

void StateAccessor::registerForStateUpdates(NetworkLogicListener* listener)
{
	mStateUpdateListeners.addElement(listener);
}



Input NetworkLogic::getLastInput(void) const
{
	return mLastInput;
}

void NetworkLogic::setLastInput(Input newInput)
{
	mLastInput = newInput;
}

State NetworkLogic::getState(void) const
{
	return mStateAccessor.getState();
}

const ExitGames::Common::JVector<ExitGames::LoadBalancing::Room>& NetworkLogic::getRoomList()
{
    return mLoadBalancingClient.getRoomList();
}

// functions
NetworkLogic::NetworkLogic(OutputListener* listener, const char* appVersion)
#ifdef _EG_MS_COMPILER
#	pragma warning(push)
#	pragma warning(disable:4355)
#endif
	: mLoadBalancingClient(*this, "if connecting to the exitgamescloud, replace this string with the application id, that can be found after logging in at http://exitgamescloud.com/Dashboard", appVersion, PLAYER_NAME)
	, mLastInput(INPUT_NON)
	, mOutputListener(listener)
#ifdef _EG_MS_COMPILER
#	pragma warning(pop)
#endif
{
	mStateAccessor.setState(STATE_INITIALIZED);
	mLoadBalancingClient.setDebugOutputLevel(DEBUG_LEVEL_INFO);
}

void NetworkLogic::registerForStateUpdates(NetworkLogicListener* listener)
{
	mStateAccessor.registerForStateUpdates(listener);
}

void NetworkLogic::connect(void)
{
	mLoadBalancingClient.connect( mServerAddress ); // specify the ip and port of your local masterserver here; call the parameterless overload instead, if you want to connect to the  exitgamescloud
	mStateAccessor.setState(STATE_WAITING);
}

void NetworkLogic::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}

void NetworkLogic::opCreateRoom(void)
{
	// if last digits are always nearly the same, this is because of the timer calling this function being triggered every x ms with x being a factor of 10
	ExitGames::Common::JString tmp;
	mLoadBalancingClient.opCreateRoom(tmp=(int)GETTIMEMS());
	mStateAccessor.setState(STATE_JOINING);
	mOutputListener->writeLine(ExitGames::Common::JString(L"creating game \"") + tmp + L"\"");
}

void NetworkLogic::opJoinRandomRoom(void)
{
	mLoadBalancingClient.opJoinRandomRoom();
}

void NetworkLogic::opJoinRoom(const Common::JString &gameID)
{
	mLoadBalancingClient.opJoinRoom(gameID);
}

void NetworkLogic::opLeaveRoom( void )
{
	mLoadBalancingClient.opLeaveRoom();
}

void NetworkLogic::opRaiseEvent(bool reliable, const Common::Hashtable &parameters, nByte eventCode)
{
	mLoadBalancingClient.opRaiseEvent(reliable, parameters, eventCode);
	mOutputListener->writeLine(ExitGames::Common::JString(L"sending Event"));
}

void NetworkLogic::setServerAddress( const char* address )
{
    this->mServerAddress = JString( address );
}

void NetworkLogic::run(void)
{
	if(mLastInput == INPUT_EXIT && mStateAccessor.getState() != STATE_DISCONNECTING && mStateAccessor.getState() != STATE_DISCONNECTED)
	{
		disconnect();
		mStateAccessor.setState(STATE_DISCONNECTING);
		mOutputListener->writeLine(L"terminating application");
	}
	else if( mLastInput == INPUT_CONNECT && mStateAccessor.getState() == STATE_INITIALIZED )
    {
        mStateAccessor.setState( STATE_CONNECTING );
    }
    else
	{
		State state = mStateAccessor.getState();
		switch(state)
		{
		/*case STATE_INITIALIZED:
			connect();
			mStateAccessor.setState(STATE_CONNECTING);
			mOutputListener->writeLine(L"connecting");
			break;
		case STATE_CONNECTING:
			break; // wait for callback*/
        case STATE_CONNECTING:
            connect();
            mOutputListener->writeLine(L"connecting");
            break;
        case STATE_WAITING:
            break; // wait for callback
		case STATE_CONNECTED:
			switch(mLastInput)
			{
			case INPUT_CREATE_GAME: // create Game
				opCreateRoom();
                //this->setLastInput( INPUT_JOIN_RANDOM_GAME );
				//break;
			case INPUT_JOIN_RANDOM_GAME: // join Game
				opJoinRandomRoom();
				mStateAccessor.setState(STATE_JOINING);
				mOutputListener->writeLine(L"joining random game");
				break;
			default: // no or illegal input -> stay waiting for legal input
				break;
			}
			break;
		case STATE_JOINING:
			break; // wait for callback
		case STATE_JOINED:
			sendEvent();
			switch(mLastInput)
			{
			case INPUT_LEAVE_GAME: // leave Game
				mLoadBalancingClient.opLeaveRoom();
				mStateAccessor.setState(STATE_LEAVING);
				mOutputListener->writeLine(L"");
				mOutputListener->writeLine(L"leaving game room");
				break;
			default: // no or illegal input -> stay waiting for legal input
				break;
			}
			break;
		case STATE_LEAVING:
            opLeaveRoom();
			break; // wait for callback
		case STATE_LEFT:
            //change button back to Join Game
			mStateAccessor.setState(STATE_CONNECTED);
			break;
		case STATE_DISCONNECTING:
			break; // wait for callback
        case STATE_DISCONNECTED:
            mStateAccessor.setState(STATE_INITIALIZED);
            break;
		default:
			break;
		}
	}
	mLastInput = INPUT_NON;
	mLoadBalancingClient.service();
}

void NetworkLogic::sendEvent(void)
{
	mLoadBalancingClient.opRaiseEvent(false, ExitGames::Common::Hashtable(), 100);
	mOutputListener->write(L"s");
}

// protocol implementations

void NetworkLogic::debugReturn(const ExitGames::Common::JString& string)
{
	mOutputListener->debugReturn(string);
}

void NetworkLogic::debugReturn(PhotonPeer_DebugLevel debugLevel, const ExitGames::Common::JString& string)
{
	debugReturn(string);
}

void NetworkLogic::connectionErrorReturn(int errorCode)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_ERRORS, L"code: %d", errorCode);
	mOutputListener->writeLine(ExitGames::Common::JString(L"connection failed with error ") + errorCode);
	mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::clientErrorReturn(int errorCode)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_ERRORS, L"code: %d", errorCode);
	mOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + L" from client");
}

void NetworkLogic::warningReturn(int warningCode)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_WARNINGS, L"code: %d", warningCode);
	mOutputListener->writeLine(ExitGames::Common::JString(L"received warning ") + warningCode + L" from client");
}

void NetworkLogic::serverErrorReturn(int errorCode)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_ERRORS, L"code: %d", errorCode);
	mOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + " from server");
}

void NetworkLogic::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"%ls joined the game", player.getName().cstr());
	mOutputListener->writeLine(L"");
	mOutputListener->writeLine(ExitGames::Common::JString(L"player ") + playerNr + L" " + player.getName() + L" has joined the game");
}

void NetworkLogic::leaveRoomEventAction(int playerNr)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
	mOutputListener->writeLine(L"");
	mOutputListener->writeLine(ExitGames::Common::JString(L"player ") + playerNr + " has left the game");
}

void NetworkLogic::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Hashtable& eventContent)
{
	// you do not receive your own events, unless you specify yourself as one of the receivers explicitly, so you must start 2 clients, to receive the events, which you have sent, as sendEvent() uses the default receivers of opRaiseEvent() (all players in same room like the sender, except the sender itself)
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_ALL, L"");
	mOutputListener->write(L"r");
    switch (eventCode)
    {
        case EVENT_CHAT:
            mOutputListener->write(L"chat event receieved");
            
            break;
        default:
            break;
    }
    char code[2] = { '\0' };
    sprintf( code, "%d", eventCode );
    mOutputListener->write( code );

}

void NetworkLogic::connectReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
	if(errorCode)
	{
		PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_ERRORS, L"%ls", errorString.cstr());
		mStateAccessor.setState(STATE_DISCONNECTING);
		return;
	}
	mOutputListener->writeLine(L"connected");
	mStateAccessor.setState(STATE_CONNECTED);
    
    mLoadBalancingClient.opJoinLobby();
}

void NetworkLogic::disconnectReturn(void)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
	mOutputListener->writeLine(L"disconnected");
	mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
	if(errorCode)
	{
		PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_ERRORS, L"%ls", errorString.cstr());
		mOutputListener->writeLine(L"opCreateRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"localPlayerNr: %d", localPlayerNr);
	mOutputListener->writeLine(L"game room \"" + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + "\" has been created");
	mOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
	if(errorCode)
	{
		PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_ERRORS, L"%ls", errorString.cstr());
		mOutputListener->writeLine(L"opJoinRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"localPlayerNr: %d", localPlayerNr);
	mOutputListener->writeLine(L"game room \"" + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + "\" has been successfully joined");
	mOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
	if(errorCode)
	{
		PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_ERRORS, L"%ls", errorString.cstr());
		mOutputListener->writeLine(L"opJoinRandomRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"localPlayerNr: %d", localPlayerNr);
	mOutputListener->writeLine(L"game room \"" + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + "\" has been successfully joined");
	mOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
	if(errorCode)
	{
		PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_ERRORS, L"%ls", errorString.cstr());
		mOutputListener->writeLine(L"opLeaveRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_DISCONNECTING);
		return;
	}
	mOutputListener->writeLine(L"game room has been successfully left");
	mStateAccessor.setState(STATE_LEFT);
}

void NetworkLogic::gotQueuedReturn(void)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
}

void NetworkLogic::joinLobbyReturn(void)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
	mOutputListener->writeLine(L"joined lobby");
    

}

void NetworkLogic::leaveLobbyReturn(void)
{
	PhotonPeer_sendDebugOutput(&mLoadBalancingClient, DEBUG_LEVEL_INFO, L"");
	mOutputListener->writeLine(L"left lobby");
}
