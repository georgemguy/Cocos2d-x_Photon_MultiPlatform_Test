/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2012 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __ENET_PEER_H
#define __ENET_PEER_H

#include "PeerBase.h"
#include "EnetChannel.h"

namespace ExitGames
{
	namespace Photon
	{
		class EnetPeer: public PeerBase
		{
		public:
			EnetPeer(SPhotonPeer* pPeer);
			~EnetPeer(void);
		private:
			typedef PeerBase super;

			void cleanupNonHierarchical(void);
			void cleanup(void);
			void reset(void);
			bool connect(const EG_CHAR* ipAddr, const nByte appID[32]);
			bool startConnection(char* ipAddr);
			void disconnect(void);
			void stopConnection(void);
			void sendOutgoingCommands(void);
			void copyCommandToBuffer(nByte* pDst, const nByte* pSrc, int& size);
			bool dispatchIncomingCommands(void);
			void fetchServerTimestamp(void);
			void onConnectCallback(int nError);
			void onReceiveDataCallback(nByte* pBuf, int iCount, int nError);

			int getIncomingReliableCommandsCount(void);
			int getQueuedIncomingCommands(void);
			int getQueuedOutgoingCommands(void);

			void send(nByte cType, nByte* payload, unsigned int payloadSize, nByte channelId);
			bool sendInFragments(nByte* payload, unsigned int payloadSize, nByte channelId);
			void queueOutgoingReliableCommand(EnetCommand* command);
			void queueOutgoingUnreliableCommand(EnetCommand* command);
			void queueOutgoingAcknowledgement(EnetCommand* command);
			bool queueIncomingCommand(EnetCommand* command);
			void queueSentReliableCommand(EnetCommand* command);
			int serializeToBuffer(EG_Vector**);
			void execute(EnetCommand* command);
			void removeSentReliableCommand(int ackReceivedReliableSequenceNumber,  int ackReceivedChannel, EnetCommand** command);
			void sortLastElementInQueue(EG_Vector** argQueue, bool sortByReliableSequenceNumber);
			void clearAllQueues(void);

			EG_Vector* outgoingAcknowledgements;
			EG_Vector* sentReliableCommands;
			EnetChannel** channels;						
			int windowSize;  
			int* unsequencedWindow;
			int outgoingUnsequencedGroupNumber;
			int incomingUnsequencedGroupNumber;
			nByte commandCount;
			nByte* buffer;
			int bufferIndex;
			int commandSize;

			friend void EnetCommand::init(EnetPeer* const  pEnetPeer, nByte cType, const nByte* const payload, int payloadLen);
		};
	}
}

#endif