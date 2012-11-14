/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2012 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __T_PEER_H
#define __T_PEER_H

#include "PeerBase.h"

namespace ExitGames
{
	namespace Photon
	{
		class TPeer: public PeerBase
		{
		public:
			TPeer(SPhotonPeer* pPeer);
			~TPeer(void);
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
			bool dispatchIncomingCommands(void);
			void fetchServerTimestamp(void);

			int getIncomingReliableCommandsCount(void);
			int getQueuedIncomingCommands(void);
			int getQueuedOutgoingCommands(void);

			void onConnectCallback(int nError);
			void onReceiveDataCallback(nByte* pBuf, int iCount, int nError);

			void send(nByte cType, nByte* payload, unsigned int payloadSize, nByte channelId);
			bool serializeOperation(COperationRequest* pOperationRequest, nByte** buffer,  int* buffSize, bool encrypt, nByte msgType);
			void clearAllQueues(void);
			void initCallback(void);

			void readPingFromBuffer(nByte* pBuffer, int* nRead);
			void sendPing(void);
			void sendInit(void);

			int mTimeLastPing;
			EG_Vector* mOutgoingOpList;
			EG_Vector* mIncomingOpList;
			static const nByte mTcpHeader[TCP_HEADER_LENGTH+MSG_HEADER_BYTES];
		};
	}
}

#endif