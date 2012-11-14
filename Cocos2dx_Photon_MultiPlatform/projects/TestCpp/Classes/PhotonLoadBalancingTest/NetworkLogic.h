#ifndef __NETWORK_LOGIC_H
#define __NETWORK_LOGIC_H

#include "OutputListener.h"
#include "LoadBalancingListener.h"
#include "LoadBalancingClient.h"
#include "LoadBalancingPlayer.h"

typedef enum _State
{
	STATE_INITIALIZED = 0,
    STATE_WAITING,
	STATE_CONNECTING,
	STATE_CONNECTED,
	STATE_JOINING,
	STATE_JOINED,
	STATE_LEAVING,
	STATE_LEFT,
	STATE_DISCONNECTING,
	STATE_DISCONNECTED
} State;

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
private:
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
};

#endif
