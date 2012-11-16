#ifndef __NETWORK_LOGIC_H
#define __NETWORK_LOGIC_H

#include "OutputListener.h"
#include "LoadBalancingListener.h"
#include "LoadBalancingClient.h"
#include "LoadBalancingPlayer.h"

/*
 * Any Photon client is in one of these states at any given time. NetworkLogic
 * stores the client's state on its StateAccessor object "mStateAccessor".
 * No public method of NetworkLogic should alter the State of the NetworkLogic
 * except NetworkLogic::run(). Anything else that may involve a change of state
 * should be handled with an Input, an Operation, or a private method of
 * NetworkLogic.
 */
typedef enum _State
{
    // The client is ready to connect, having just either finished starting, or
    // finished disconnecting.
	STATE_INITIALIZED = 0,
    // The client has received the input INPUT_CONNECT, and is about to try
    // connecting.
	STATE_CONNECTING,
    // The client has attempted to connect, and is waiting for a response from
    // the server.
    STATE_WAITING,
    // The client has connected.
	STATE_CONNECTED,
    // The client has asked to join a game, but has not yet received a
    // response.
	STATE_JOINING,
    // The client has joined a game.
	STATE_JOINED,
    // The client has asked to join a game, but has not yet received a
    // response.
	STATE_LEAVING,
    // The client has just left a room.
	STATE_LEFT,
    // The client is attempting to disconnect.
	STATE_DISCONNECTING,
    // The client has just disconnected.
	STATE_DISCONNECTED
} State;

/*
 * An Input is a command that is represented by one of the Input enumerations, rather than a method. To use an Input, call NetworkLogic::setLastInput(), which will store the given input on NetworkLogic::mLastInput. For instance, to connect, use "networkLogic->setLastInput( INPUT_CONNECT )". The effects of the last input set within a given tick are executed in NetworkLogic::run(). At the end of NetworkLogic::run(), mLastInput is reset to INPUT_NON.
 */
typedef enum _Input
{
	INPUT_NON = 0,
    INPUT_CONNECT,
	INPUT_CREATE_GAME,
	INPUT_JOIN_RANDOM_GAME,
	INPUT_LEAVE_GAME,
	INPUT_EXIT
} Input;



class NetworkLogicListener : public ExitGames::Common::ToString
{
public:
	using ExitGames::Common::ToString::toString;
	virtual void stateUpdate(State newState) = 0;
	virtual ExitGames::Common::JString& toString(ExitGames::Common::JString& retStr, bool withTypes=false) const;
};



class StateAccessor
{
public:
	State getState(void) const;
	void setState(State newState);
	void registerForStateUpdates(NetworkLogicListener* listener);

private:
	State mState;
	ExitGames::Common::JVector<NetworkLogicListener*> mStateUpdateListeners;
};



class NetworkLogic : private ExitGames::Common::BaseListener, ExitGames::LoadBalancing::Listener
{
public:
	NetworkLogic(OutputListener* listener, const char* appVersion);
	void registerForStateUpdates(NetworkLogicListener* listener);
	virtual void run(void);
    virtual void connect();
	virtual void opCreateRoom(void);
	virtual void opJoinRandomRoom(void);
	virtual void disconnect(void);
	virtual void sendEvent(void);

	Input getLastInput(void) const;
	void setLastInput(Input newInput);
	State getState(void) const;
    virtual void setServerAddress( const char* address );
    virtual const ExitGames::Common::JVector<ExitGames::LoadBalancing::Room>& getRoomList();

protected:
	//From Common::BaseListener
	// receive and print out Photon datatypes debug out here
	virtual void debugReturn(const ExitGames::Common::JString& string);

	//From LoadBalancing::LoadBalancingListener
	// receive and print out Photon LoadBalancing debug out here
	virtual void debugReturn(PhotonPeer_DebugLevel debugLevel, const ExitGames::Common::JString& string);

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr);
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Hashtable& eventContent);

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void gotQueuedReturn(void);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);

	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	ExitGames::Common::JString mGameID;
	StateAccessor mStateAccessor;
	Input mLastInput;
	OutputListener* mOutputListener;
    ExitGames::Common::JString mServerAddress;
};

#endif
