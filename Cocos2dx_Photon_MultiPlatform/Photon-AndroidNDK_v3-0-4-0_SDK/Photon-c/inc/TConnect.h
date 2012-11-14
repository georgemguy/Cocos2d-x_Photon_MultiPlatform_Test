/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2012 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __T_CONNECT_H
#define __T_CONNECT_H

#include "TPeer.h"

namespace ExitGames
{
	namespace Photon
	{
		class TConnect : public PhotonConnect
		{
		public:
			TConnect(TPeer* pPeer);
			~TConnect(void);
		private:
			typedef PhotonConnect super;

			int socket(void);
			unsigned short getDefaultPort(void);
			bool checkConnection(void);
			int recvBuffer(nByte** ppBuff, int* pBytesRead);
		};
	}
}

#endif