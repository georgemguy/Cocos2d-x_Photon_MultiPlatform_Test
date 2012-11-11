#include "Photon_lib.h"
#include "limits.h"

#define MAX_SENDCOUNT 100

PhotonLib::PhotonLib(void)
{
	mLitePeer = new ExitGames::Photon::LitePeer(this);
	mLitePeer->setDebugOutputLevel(DEBUG_LEVEL_INFO);
	mState = State::INITIALIZED;
	mSendCount = 0;
	mReceiveCount = 0;
}

PhotonLib::~PhotonLib(void)
{
	delete mLitePeer;
}

void PhotonLib::update(void)
{
	ExitGames::Common::JString gameName(L"Hello World");

	switch(mState)
	{
        /*case State::INITIALIZED:
			mLitePeer->connect(L"50.0.206.109:5055");
			mState = State::CONNECTING;
			break;
		case State::CONNECTED:
			mLitePeer->opJoin(gameName);
			mState = State::JOINING;
			break;
        case State::JOINED:
			sendData();
			break;*/
        case State::CONNECTING:
			mLitePeer->connect(L"192.168.1.4:5055");
            mState = State::WAITING;
			break;
		case State::CONNECTED:
			mLitePeer->opJoin(gameName);
			//mState = State::SENDING_DATA;
			break;
		case State::SENDING_DATA:
			sendData();
			break;
		case State::RECEIVED_DATA:
			mLitePeer->opLeave(gameName);
			mState = State::LEAVING;
			break;
		case State::LEFT:
			mLitePeer->disconnect();
			mState = State::DISCONNECTING;
			break;
		case State::DISCONNECTED:
			mState = State::INITIALIZED;
			break;
		default:
			break;
	}
	mLitePeer->service();
}

ExitGames::Common::JString PhotonLib::getStateString(void)
{
	switch(mState)
	{
		case State::INITIALIZED:
			return L"disconnected";
        case State::WAITING:
            return L"connecting";
		case State::CONNECTING:
			return L"connecting";
		case State::CONNECTED:
			return L"connected";
		case State::JOINING:
			return L"joining";
		case State::JOINED:
			return L"joined";
		case State::SENDING_DATA:
			return ExitGames::Common::JString(L"ingame\nsent event Nr. ") + mSendCount + L"\nreceived event Nr. " + mReceiveCount;
		case State::SENT_DATA:
			return ExitGames::Common::JString(L"sending completed") + L"\nreceived event Nr. " + mReceiveCount;
		case State::RECEIVED_DATA:
			return L"receiving completed";
		case State::LEAVING:
			return L"leaving";
		case State::LEFT:
			return L"left";
		case State::DISCONNECTING:
			return L"disconnecting";
		case State::DISCONNECTED:
			return L"disconnected";
		default:
			return L"unknown state";
	}
}

bool PhotonLib::sendDataIfJoined()
{
    if( mState == State::JOINED )
    {
        mState = State::SENDING_DATA;
        return true;
    }
    return false;
}

bool PhotonLib::connectIfInitialized()
{
    if( mState == State::INITIALIZED )
    {
        mState = State::CONNECTING;
        return true;
    }
    return false;
}

void PhotonLib::sendData(void)
{
	ExitGames::Common::Hashtable event;
	event.put(static_cast<nByte>(0), ++mSendCount);
	mLitePeer->opRaiseEvent(true, event, 101, 0, &mActorNumber, 1);
	if(mSendCount >= MAX_SENDCOUNT)
		mState = State::SENT_DATA;
}



// inherited listener interface:

void PhotonLib::onOperationResponse(const ExitGames::Photon::OperationResponse& operationResponse)
{
	switch(operationResponse.getOperationCode())
	{
	case OPC_RT_JOIN:
		mActorNumber = ((ExitGames::Common::ValueObject<int>)operationResponse.getParameterForCode(P_ACTORNR)).getDataCopy();
		mState = State::JOINED;
		break;
	case OPC_RT_LEAVE:
		mState = State::LEFT;
		break;
	default:
		break;
	}
}

void PhotonLib::onStatusChanged(int statusCode)
{
	switch(statusCode)
	{
	case SC_CONNECT:
		mState = State::CONNECTED;
		break;
	case SC_DISCONNECT:
		mState = State::DISCONNECTED;
		break;
	default:
		break;
	}
}

void PhotonLib::onEvent(const ExitGames::Photon::EventData& eventData)
{
	ExitGames::Common::ValueObject<ExitGames::Common::Hashtable> objEventDataContent = eventData.getParameterForCode(P_DATA);
	ExitGames::Common::Hashtable* eventDataContent = objEventDataContent.getDataAddress();
	switch(eventData.getCode())
	{
	case 101:
		if(eventDataContent->getValue((nByte)0))
			mReceiveCount = ((ExitGames::Common::ValueObject<int64>*)(eventDataContent->getValue((nByte)0)))->getDataCopy();
		if(mState == State::SENT_DATA && mReceiveCount >= mSendCount)
		{
			mState = State::RECEIVED_DATA;
			mSendCount = 0;
			mReceiveCount = 0;
		}
		break;
	default:
		break;
	}
}

void PhotonLib::debugReturn(PhotonPeer_DebugLevel /*debugLevel*/, const ExitGames::Common::JString& string)
{
	fprintf(stderr, "%s\n", string.ANSIRepresentation().cstr());
}

PhotonLib::State::States PhotonLib::getState()
{
    return this->mState;
}