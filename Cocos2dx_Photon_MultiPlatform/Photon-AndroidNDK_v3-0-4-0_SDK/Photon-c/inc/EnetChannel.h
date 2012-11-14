/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2012 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __ENET_CHANNEL_H
#define __ENET_CHANNEL_H

#include "Constants.h"
#include "data_structures.h"
#include "EnetCommand.h"

namespace ExitGames
{
	namespace Photon
	{
		class EnetChannel
		{
		public:
			EnetChannel(nByte channelNumber);
			~EnetChannel(void);
			EnetCommand* getReliableCommandFromQueue(int reliableSequenceNumber);
			EnetCommand* getUnreliableCommandFromQueue(int unreliableSequenceNumber);
			bool removeReliableCommandFromQueue(int reliableSequenceNumber);
			bool removeUnreliableCommandFromQueue(int unreliableSequenceNumber);
		private:
			nByte mChannelNumber;

			EG_Vector* mIncomingReliableCommands;
			EG_Vector* mIncomingUnreliableCommands;

			int mIncomingReliableSequenceNumber;		// sequencenr of last dispatched command
			int mIncomingUnreliableSequenceNumber;

			EG_Vector* mOutgoingReliableCommands;
			EG_Vector* mOutgoingUnreliableCommands;

			int mOutgoingReliableSequenceNumber;
			int mOutgoingUnreliableSequenceNumber;

			friend class PeerBase;
			friend class EnetPeer;
		};
	}
}

#endif