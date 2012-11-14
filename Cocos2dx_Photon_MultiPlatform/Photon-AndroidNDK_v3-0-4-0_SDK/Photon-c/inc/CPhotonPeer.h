/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2012 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __C_PHOTON_PEER_H
#define __C_PHOTON_PEER_H

#include "CEventData.h"
#include "COperationResponse.h"
#include "COperationRequest.h"
#include "Callbacks.h"

/* <title SPhotonPeer structure>
   <toctitle SPhotonPeer structure>
   
      SPhotonPeer is the struct that holds basic data related to
   Photon based functions*/
struct _SPhotonPeer
{
    void* mpPeerBase;
};

#ifdef __cplusplus
extern "C"
{
#endif
	// public API functions
	int PhotonPeer_new(SPhotonPeer** ppMod, bool useTcp);
	unsigned int PhotonPeer_release(SPhotonPeer* pPeer);
	bool PhotonPeer_connect(SPhotonPeer* pPeer, const EG_CHAR* ipAddr, const nByte appID[32]);
	void PhotonPeer_disconnect(SPhotonPeer* pPeer);
	void PhotonPeer_service(SPhotonPeer* pPeer);
	void PhotonPeer_serviceBasic(SPhotonPeer* pPeer);
	void PhotonPeer_serviceWithoutDispatching(SPhotonPeer* pPeer);
	void PhotonPeer_sendOutgoingCommands(SPhotonPeer* pPeer);
	bool PhotonPeer_dispatchIncomingCommands(SPhotonPeer* pPeer);
	bool PhotonPeer_opCustom(SPhotonPeer* pPeer, COperationRequest* pOperationRequest, bool sendReliable, nByte channelId, bool encrypt);
	void PhotonPeer_fetchServerTimestamp(SPhotonPeer* pPeer);
	bool PhotonPeer_establishEncryption(SPhotonPeer* pPeer);

	// public API callback setters
	void PhotonPeer_setCBOnOperationResponse(SPhotonPeer* pPeer, CB_ON_OPERATION_RESPONSE cb, void* pUser);
	void PhotonPeer_setCBOnStatusChanged(SPhotonPeer* pPeer, CB_ON_STATUS_CHANGED cb, void* pUser);
	void PhotonPeer_setCBOnEvent(SPhotonPeer* pPeer,CB_ON_EVENT cb, void* pUser);
	void PhotonPeer_setCBDebugReturn(SPhotonPeer* pPeer, CB_DEBUG_RETURN cb, void* pUser);

	// public API getter/setter functions
	int PhotonPeer_getServerTimeOffset(SPhotonPeer* pPeer);
	int PhotonPeer_getServerTime(SPhotonPeer* pPeer);
	int PhotonPeer_getBytesOut(SPhotonPeer* pPeer);
	int PhotonPeer_getBytesIn(SPhotonPeer* pPeer);
	PeerState PhotonPeer_getPeerState(SPhotonPeer* pPeer);
	int PhotonPeer_getSentCountAllowance(SPhotonPeer* pPeer);
	void PhotonPeer_setSentCountAllowance(SPhotonPeer* pPeer, int setSentCountAllowance);
	int PhotonPeer_getTimePingInterval(SPhotonPeer* pPeer);
	void PhotonPeer_setSentCountAllowance(SPhotonPeer* pPeer, int setSentCountAllowance);
	void PhotonPeer_setTimePingInterval(SPhotonPeer* pPeer, int setTimePingInterval);
	int PhotonPeer_getRoundTripTime(SPhotonPeer* pPeer);
	int PhotonPeer_getRoundTripTimeVariance(SPhotonPeer* pPeer);
	int PhotonPeer_getIncomingReliableCommandsCount(SPhotonPeer* pPeer);
	PhotonPeer_DebugLevel PhotonPeer_getDebugOutputLevel(SPhotonPeer* pPeer);
	bool PhotonPeer_setDebugOutputLevel(SPhotonPeer* pPeer, PhotonPeer_DebugLevel debugLevel);
	short PhotonPeer_getPeerID(SPhotonPeer* pPeer);
	int PhotonPeer_getSentTimeAllowance(SPhotonPeer* pPeer);
	void PhotonPeer_setSentTimeAllowance(SPhotonPeer* pPeer, int setSentTimetAllowance);
	int PhotonPeer_getQueuedIncomingCommands(SPhotonPeer* pPeer);
	int PhotonPeer_getQueuedOutgoingCommands(SPhotonPeer* pPeer);
	char* PhotonPeer_getServerAdress(SPhotonPeer* pPeer);
	bool PhotonPeer_getIsEncryptionAvailable(SPhotonPeer* pPeer);
	unsigned short PhotonPeer_getPeerCount(void);

	// public debugging API
#	ifdef EG_DEBUGGER
#		define PhotonPeer_sendDebugOutput(peer, debugLevel, ...) PhotonPeer_internal_sendDebugOutput(peer, debugLevel, __WFILE__, __WFUNCTION__, true, __LINE__, __VA_ARGS__)
#		define PhotonPeer_vsendDebugOutput(peer, debugLevel, dbgMsg, args) PhotonPeer_internal_vsendDebugOutput(peer, debugLevel, __WFILE__, __WFUNCTION__, true, __LINE__, dbgMsg, args)
#	else
#		define PhotonPeer_sendDebugOutput(peer, debugLevel, ...) ((void)0)
#		define PhotonPeer_vsendDebugOutput(peer, debugLevel, dbgMsg, args) ((void)0)
#	endif

	void PhotonPeer_internal_sendDebugOutput(SPhotonPeer* pPeer, PhotonPeer_DebugLevel debugLevel, const EG_CHAR* const file, const EG_CHAR* const function, bool printBrackets, unsigned int line, const EG_CHAR* dbgMsg, ...);
	void PhotonPeer_internal_vsendDebugOutput(SPhotonPeer* pPeer, PhotonPeer_DebugLevel debugLevel, const EG_CHAR* const file, const EG_CHAR* const function, bool printBrackets, unsigned int line, const EG_CHAR* dbgMsg, va_list args);
#ifdef __cplusplus
}
#endif

#endif //__C_PHOTON_PEER_H__