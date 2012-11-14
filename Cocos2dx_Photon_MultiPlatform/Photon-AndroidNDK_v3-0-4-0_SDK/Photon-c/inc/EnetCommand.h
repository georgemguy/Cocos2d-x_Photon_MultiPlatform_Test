/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2012 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __ENET_COMMAND_H
#define __ENET_COMMAND_H

#include "platformLayer.h"
#include "Constants.h"
#include "PhotonPlatformLayer.h"
#include "PhotonConstants.h"
#include "Photon.h"

#ifdef __cplusplus
extern "C"
{
#endif
	void PhotonCommand_release(void* po);
#ifdef __cplusplus
}
#endif

namespace ExitGames
{
	namespace Photon
	{
		class EnetPeer;

		class EnetCommand
		{
		public:
			EnetCommand(EnetPeer* const pEnetPeer, nByte cType, const nByte* const payload, int payloadSize);
			EnetCommand(EnetPeer* const pEnetPeer, nByte* pBuffer, unsigned int bufferSize, int* nRead, int sentTime);
			~EnetCommand(void);

			EnetCommand(const EnetCommand& toCopy);
			EnetCommand& operator=(const EnetCommand& toCopy);

			void init(void);
			void init(EnetPeer* const pEnetPeer, nByte cType, const nByte* const payload, int payloadLen);

			EnetCommand* createAck(void);
			void serialize(nByte** buf, int* size);
		//private:
			EnetPeer* mpEnetPeer;

			nByte mCommandFlags;
			nByte mCommandType;

			//variables from CommandHeader
			nByte mCommandChannelID;

			//variables for fragments (not used otherwise)
			int mStartSequenceNumber;
			int mFragmentCount;
			int mFragmentNumber;
			int mTotalLength;
			int mFragmentOffset;
			int mFragmentsRemaining;

			int mReliableSequenceNumber;
			int mUnreliableSequenceNumber;
			int mUnsequencedGroupNumber;
			nByte mReservedByte;

			nByte* mCommandPayload; // replaces "Packet"
			int mCommandPayloadLen;
			int mCommandSentTime; //last time the command was sent
			int mCommandOriginalSentTime; //first time the command was sent
			nByte mCommandSentCount; //counts the number of retries (before calling it a loss)
			int mAckReceivedReliableSequenceNumber; //for ACK commands
			int mAckReceivedSentTime; //for ACK commands
			int mRoundTripTimeout; // milliseconds until the command is resent
		};
	}
}

#endif