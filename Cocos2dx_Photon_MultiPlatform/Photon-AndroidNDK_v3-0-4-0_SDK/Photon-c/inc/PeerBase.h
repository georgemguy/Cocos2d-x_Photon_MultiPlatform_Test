/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2012 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PEER_BASE_H
#define __PEER_BASE_H

#include "Photon.h"
#include "data_structures.h"
#include "EnetCommand.h"
#include "PhotonConnect.h"

namespace ExitGames
{
	namespace Photon
	{
		class PeerBase
		{
		public:
			PeerBase(SPhotonPeer* pPeer);
			virtual ~PeerBase(void);
			virtual bool connect(const EG_CHAR* ipAddr, const nByte appID[32]) = 0;
			virtual bool startConnection(char* ipAddr) = 0;
			virtual void disconnect(void) = 0;
			virtual void stopConnection(void) = 0;
			virtual void service(bool dispatch);
			virtual void serviceBasic(void);
			virtual void sendOutgoingCommands(void) = 0;
			virtual bool dispatchIncomingCommands(void) = 0;
			virtual bool opCustom(COperationRequest* pOperationRequest, bool sendReliable, nByte channelId, bool encrypt, nByte msgType);
			virtual void fetchServerTimestamp(void) = 0;
			virtual bool establishEncryption(void);

			virtual void setCBOnOperationResponse(CB_ON_OPERATION_RESPONSE cb, void* pUser);
			virtual void setCBOnStatusChanged(CB_ON_STATUS_CHANGED cb, void* pUser);
			virtual void setCBOnEvent(CB_ON_EVENT cb, void* pUser);
			virtual void setCBDebugReturn(CB_DEBUG_RETURN cb, void* pUser);

			virtual int getServerTimeOffset(void);
			virtual int getServerTime(void);
			virtual int getBytesOut(void);
			virtual int getBytesIn(void);
			virtual PeerState getPeerState(void);
			virtual int getSentCountAllowance(void);
			virtual void setSentCountAllowance(int setSentCountAllowance);
			virtual int getTimePingInterval(void);
			virtual void setTimePingInterval(int setTimePingInterval);
			virtual int getRoundTripTime(void);
			virtual int getRoundTripTimeVariance(void);
			virtual int getIncomingReliableCommandsCount(void) = 0;
			virtual PhotonPeer_DebugLevel getDebugOutputLevel(void);
			virtual bool setDebugOutputLevel(PhotonPeer_DebugLevel debugLevel);
			virtual short getPeerID(void);
			virtual int getSentTimeAllowance(void);
			virtual void setSentTimeAllowance(int setSentTimetAllowance);
			virtual int getQueuedIncomingCommands(void) = 0;
			virtual int getQueuedOutgoingCommands(void) = 0;
			virtual char* getServerAdress(void);
			virtual bool getIsEncryptionAvailable(void);
			static unsigned short getPeerCount(void);

			void vsendDebugOutput(PhotonPeer_DebugLevel debugLevel, const EG_CHAR* const file, const EG_CHAR* const function, bool  printBrackets, unsigned int line, const EG_CHAR* dbgMsg, va_list args);

			virtual void onConnectCallback(int nError) = 0;
			virtual void onReceiveDataCallback(nByte* pBuf, int iCount, int nError) = 0;
			virtual void onSendCommands(int nError);
		protected:
			virtual void cleanup(void);
			virtual void reset(void);
			virtual void onDisconnected(void);
			virtual void send(nByte cType, nByte* payload, unsigned int payloadSize, nByte channelId) = 0;
			virtual bool serializeOperation(COperationRequest* pOperationRequest, nByte** buffer,  int* buffSize, bool encrypt, nByte msgType);
			virtual bool deserializeOperation(nByte* inBuff, int inBuffLength);
			virtual void deserializeOperationResponse(nByte* inBuff, bool isEncrypted, int waitForBytes, nByte msgType);
			virtual void deserializeEvent(nByte* inBuff, bool isEncrypted, int waitForBytes);
			virtual void updateRoundTripTimeAndVariance(int time);
			virtual void clearAllQueues(void) = 0;
			virtual bool opExchangeKeysForEncryption(void);
			virtual void deriveSharedKey(COperationResponse* pOperationResponse);
			virtual void initCallback(void);

			SPhotonPeer* mpPeer;

			static unsigned short peerCount;

			short peerID;
			int challenge;
			char* peerIpAddr;
			ConnectionState connectionState;
			nByte channelCountUserChannels; // this is the number of user-channels. There is an additional exclusive channel for system messages.
			nByte initBytes[INIT_BYTES_LENGTH];
			PhotonConnect* rt;
			int timeBase;
			int timeInt;				
			int timeoutInt;
			int sentTimeAllowance;
			int timeLastReceive;
			int sentCountAllowance;
			int timePingInterval;
			int packetsLost;
			int packetLoss;
			int packetsSent;
			int packetLossEpoch;
			int packetLossVariance;
			int packetThrottleEpoch;
			int serverTimeOffset;
			bool serverTimeOffsetIsAvailable;
			int serverSentTime;
			int roundTripTime;
			int roundTripTimeVariance;
			int lastRoundTripTime;
			int lowestRoundTripTime;
			int lastRoundTripTimeVariance;
			int highestRoundTripTimeVariance;
			int packetThrottleInterval;
			EG_Callback cbOnOperationResponse; //Pointer to callback function
			EG_Callback cbOnStatusChanged; //Pointer to callback function
			EG_Callback cbOnEvent; //Pointer to callback function
			EG_Callback cbDebugReturn;  // pointer to the udp debug callback function
			bool isSendingCommand; //Indicates if sending command is in progress
			nByte*secretKey; // Client private key
			nByte* sharedKeyHash; // Shared key hash, used as key for encrypting messages
			int secretKeySize; // Client private key size
			int  publicKeySize; // Client public key size
			bool isEncryptionAvailable;
			unsigned short warningTresholdQueueOutgoingReliable;
			unsigned short warningTresholdQueueOutgoingUnreliable;
			unsigned short warningTresholdQueueOutgoingAcks;
			unsigned short warningTresholdQueueIncomingReliable;
			unsigned short warningTresholdQueueIncomingUnreliable;
			unsigned short warningTresholdQueueSent;
			bool applicationIsInitialized;
			bool shouldScheduleDisconnectCB;
			bool debugUseShortcut;
			PhotonPeer_DebugLevel debugOutputLevel; // controls the level of debug output sent to the CB_DEBUG_RETURN callback
		#if defined _EG_MARMALADE_PLATFORM && !defined I3D_ARCH_ARM && defined EG_DEBUGGER
			bool firedMetricsWarning;
		#endif
		private:
			void cleanupNonHierarchical(void);

			friend EnetCommand::EnetCommand(EnetPeer* const pEnetPeer, nByte* pBuffer, unsigned int bufferSize, int* nRead, int sentTime);
			friend void EnetCommand::init(EnetPeer* const  pEnetPeer, nByte cType, const nByte* const payload, int payloadLen);
			friend void PhotonConnect::service(void);
			friend int PhotonConnect::sendPackage(nByte* src, int count);
		};
	}
}

#endif