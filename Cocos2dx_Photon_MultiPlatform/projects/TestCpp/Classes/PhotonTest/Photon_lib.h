#define DBGPRINTF_LEVEL 6

#include "LitePeer.h"

class PhotonLib : public ExitGames::Photon::PhotonListener
{
public:
	PhotonLib(void);
	~PhotonLib(void);
	void update(void);
	ExitGames::Common::JString getStateString(void);
    virtual bool sendDataIfJoined();
    virtual bool connectIfInitialized();
    
    class State
	{
	public:
		enum States
		{
			INITIALIZED = 0,
			CONNECTING,
            WAITING,
			CONNECTED,
			JOINING,
			JOINED,
            SENDING_DATA,
			SENT_DATA,
			RECEIVED_DATA,
			LEAVING,
			LEFT,
			DISCONNECTING,
			DISCONNECTED
		};
	};

private:
	void sendData(void);

	void onOperationResponse(const ExitGames::Photon::OperationResponse& operationResponse);
	void onStatusChanged(int statusCode);
	void onEvent(const ExitGames::Photon::EventData& eventData);
	void debugReturn(PhotonPeer_DebugLevel debugLevel, const ExitGames::Common::JString& string);

	State::States mState;
	ExitGames::Photon::LitePeer* mLitePeer;
	int mActorNumber;
	int64 mSendCount;
	int64 mReceiveCount;
    
public:
    State::States getState();
};