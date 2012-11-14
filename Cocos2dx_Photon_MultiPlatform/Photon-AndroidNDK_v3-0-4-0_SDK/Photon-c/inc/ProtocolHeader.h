/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2012 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PROTOCOL_HEADER_H
#define __PROTOCOL_HEADER_H

namespace ExitGames
{
	namespace Photon
	{
		class ProtocolHeader
		{
		public:
			short peerID;
			nByte flags;
			nByte commandCount;
			int   sentTime;
			int   challenge;
		};
	}
}

#endif