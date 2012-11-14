/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2012 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PHOTON_CONSTANTS_H
#define __PHOTON_CONSTANTS_H

#include "Constants.h"

// All builtin parameters for operations.
static const nByte P_GAMEID           = 255;
static const nByte P_ACTORNR          = 254;
static const nByte P_TARGET_ACTORNR   = 253;
static const nByte P_ACTOR_LIST       = 252;
static const nByte P_PROPERTIES       = 251;
static const nByte P_BROADCAST        = 250;
static const nByte P_ACTOR_PROPERTIES = 249;
static const nByte P_GAME_PROPERTIES  = 248;
static const nByte P_CACHE            = 247;
static const nByte P_RECEIVER_GROUP   = 246;
static const nByte P_DATA             = 245;
static const nByte P_CODE             = 244;

typedef enum
{
	DEBUG_LEVEL_OFF = 0,
	DEBUG_LEVEL_ERRORS = 1,
	DEBUG_LEVEL_WARNINGS = 2,
	DEBUG_LEVEL_INFO = 3,
	DEBUG_LEVEL_ALL = 4
} PhotonPeer_DebugLevel;

// operation codes
static const nByte OPC_RT_JOIN          = 255;
static const nByte OPC_RT_LEAVE         = 254;
static const nByte OPC_RT_RAISE_EV      = 253;
static const nByte OPC_RT_SETPROPERTIES = 252;
static const nByte OPC_RT_GETPROPERTIES = 251;

// event codes
static const nByte EV_RT_JOIN               = 255;
static const nByte EV_RT_LEAVE              = 254;
static const nByte EV_RT_PROPERTIES_CHANGED = 253;

// event keys
static const nByte EV_RT_KEY_ACTORNR         = 254;
static const nByte EV_RT_KEY_TARGET_ACTORNR  = 253;
static const nByte EV_RT_KEY_ACTORLIST       = 252;
static const nByte EV_RT_KEY_PROPERTIES      = 251;
static const nByte EV_RT_KEY_ACTORPROPERTIES = 249;
static const nByte EV_RT_KEY_GAMEPROPERTIES  = 248;
static const nByte EV_RT_KEY_DATA            = 245;

// status codes
static const int SC_EXCEPTION_ON_CONNECT              = 1023; // the PhotonPeer encountered an exception while opening the incoming connection to the server. The server could be down / not running.
static const int SC_CONNECT                           = 1024; // the PhotonPeer is connected.
static const int SC_DISCONNECT                        = 1025; // the PhotonPeer just disconnected.
static const int SC_EXCEPTION                         = 1026; // the PhotonPeer encountered an exception and will disconnect, too.
static const int SC_QUEUE_OUTGOING_RELIABLE_WARNING   = 1027; // PhotonPeer outgoing queue is filling up. send more often.
static const int SC_QUEUE_OUTGOING_UNRELIABLE_WARNING = 1029; // PhotonPeer outgoing queue is filling up. send more often.
static const int SC_SEND_ERROR                        = 1030; // Sending command failed. Either not connected, or the requested channel is bigger than the number of initialized channels.
static const int SC_QUEUE_OUTGOING_ACKS_WARNING       = 1031; // PhotonPeer outgoing queue is filling up. send more often.
static const int SC_QUEUE_INCOMING_RELIABLE_WARNING   = 1033; // PhotonPeer incoming reliable queue is filling up. Dispatch more often.
static const int SC_QUEUE_INCOMING_UNRELIABLE_WARNING = 1035; // PhotonPeer incoming unreliable queue is filling up. Dispatch more often.
static const int SC_QUEUE_SENT_WARNING                = 1037; // PhotonPeer sent queue is filling up. Check, why the server does not acknowldge your sent reliable commands.
static const int SC_INTERNAL_RECEIVE_EXCEPTION        = 1039; // Exception, if a server cannot be connected. Most likely, the server is not responding. Ask user to try again later.
static const int SC_TIMEOUT_DISCONNECT                = 1040; // Disconnection due to a timeout (client did no longer receive ACKs from server).
static const int SC_DISCONNECT_BY_SERVER              = 1041; // Disconnect by server due to timeout (received a disconnect command, cause server misses ACKs of client).
static const int SC_DISCONNECT_BY_SERVER_USER_LIMIT   = 1042; // Disconnect by server due to concurrent user limit reached (received a disconnect command).
static const int SC_DISCONNECT_BY_SERVER_LOGIC        = 1043; // Disconnect by server due to server's logic (received a disconnect command).
static const int SC_ENCRYPTION_ESTABLISHED            = 1048; // The encryption-setup for secure communication finished successfully.
static const int SC_ENCRYPTION_FAILED_TO_ESTABLISH    = 1049; // The encryption-setup failed for some reason. Check debug logs.

// Event Caching
static const nByte EVC_DO_NOT_CACHE  = 0;
static const nByte EVC_MERGE_CACHE   = 1;
static const nByte EVC_REPLACE_CACHE = 2;
static const nByte EVC_REMOVE_CACHE  = 3;

// ReceiverGroups
static const nByte RG_OTHERS        = 0;
static const nByte RG_ALL           = 1;
static const nByte RG_MASTER_CLIENT = 2;

// Photon library error codes
// can be returned as operationcode in callback, if the returncode indicates an error
typedef enum
{
	UL_SUCCESS       =     0, // No error
	UL_EFAILED       =     1, // General failure
	UL_ENOMEMORY     =     2, // Out of memory
	UL_EBADCLASS     =    10, // NULL class object
	UL_EBADPARM      =    14, // Invalid parameter
	UL_EITEMBUSY     =    32, // Context (system, interface, etc.) is busy

	UL_NET_SUCCESS   =     0, // No network error, successful operation  
	UL_NET_ERROR     =    -1, // Unsuccessful operation
	UL_NET_ENETNONET = 0x216, // Network subsystem unavailable
	UL_NET_MSGSIZE   = 0x21B, // Message too long. A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram was smaller than the datagram itself.
	UL_NET_ENOTCONN  = 0x21C
} PhotonLib_ErrorCodes;

// More Photon library error codes
// can be returned as return-value of an API-function
static const int SUCCESS          =  0; // No error
static const int EFAILED          =  1; // General failure
static const int ENOMEMORY        =  2; // Out of memory
static const int ECLASSNOTSUPPORT =  3; // Class not supported
static const int EBADCLASS        = 10; // NULL class object
static const int EBADPARM         = 14; // Invalid parameter
static const int EITEMBUSY        = 32; // Context (system, interface, etc.) is busy

static const int EG_PORT_UDP = 5055;
static const int EG_PORT_TCP = 4530;



// Peer state
typedef enum
{
	PS_DISCONNECTED             = 0, // The peer is disconnected and can't call Operations. Call PhotonPeer_connect().
	PS_CONNECTING               = 1, // The peer is establishing the connection: opening a socket, exchanging packages with Photon.
	PS_INITIALIZING_APPLICATION = 2, // The connection is established and now sends the application name to Photon. You set the "application name" by calling PhotonPeer_connect().
	PS_CONNECTED                = 3, // The peer is connected and initialized (selected an application). You can now use operations.
	PS_DISCONNECTING            = 4, // The peer is disconnecting. It sent a disconnect to the server, which will acknowledge closing the connection.
} PeerState;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// INTERNAL CONSTANTS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const int IN_BUFF_HEADER_LENGTH = 2;
static const int INIT_BYTES_HEADER_LENGTH = IN_BUFF_HEADER_LENGTH+7;
static const int APP_NAME_LENGTH = 32;
static const int INIT_BYTES_LENGTH = INIT_BYTES_HEADER_LENGTH+APP_NAME_LENGTH;
static const int EG_OPT_MTU_SIZE = 1200;

// Lite - Flags for "types of properties", being used as filter in OpGetProperties.
static const int PROP_NONE = 0x00;
static const int PROP_GAME = 0x01;
static const int PROP_ACTOR = 0x02;
static const int PROP_GAME_AND_ACTOR = PROP_GAME|PROP_ACTOR;

static const int WARNING_THRESHOLD_QUEUE_OUTGOING_RELIABLE_DEFAULT   = 100;
static const int WARNING_THRESHOLD_QUEUE_OUTGOING_UNRELIABLE_DEFAULT = 100;
static const int WARNING_THRESHOLD_QUEUE_OUTGOING_ACKS_DEFAULT       = 100;
static const int WARNING_THRESHOLD_QUEUE_INCOMING_RELIABLE_DEFAULT   = 100;
static const int WARNING_THRESHOLD_QUEUE_INCOMING_UNRELIABLE_DEFAULT = 100;
static const int WARNING_THRESHOLD_QUEUE_SENT_DEFAULT                = 100;

// To print out the callbacks, requests and other server interaction use EG_DEBUGGER.
//#define EG_DEBUGGER

// Connection state
typedef enum
{
	CS_DISCONNECTED             = 0,
	CS_CONNECTING               = 1,
	CS_ACKNOWLEDGING_CONNECT    = 2,
	CS_CONNECTED                = 3,
	CS_DISCONNECTING            = 4,
	CS_ACKNOWLEDGING_DISCONNECT = 5,
	CS_ZOMBIE                   = 6
} ConnectionState;


// Constants from PhotonPeer

static const int   SENTCOUNTALLOWANCE                 =         5; // number of re-send retries before a peer is considered lost/disconnected
static const int   SENTTIMEALLOWANCE                  =     10000; // max time interval in ms for re-send retries before a peer is considered lost/disconnected
static const int   TIMEPINGINTERVAL                   =      2000; // ms without reliable command, before ping will be sent
static const int   CHANNEL_COUNT_DEFAULT              =        20; // default number of channels per peer
static const int   WINDOW_SIZE                        =    (4*32);
static const int   DEBUG_IN_COMMANDS                  =     false;
static const int   DEBUG_IN_QUEUE_COMMANDS            =     false;
static const int   DEBUG_OUT_COMMANDS                 =     false;
static const int   DEBUG_ACK_COMMANDS                 =     false;
static const int   DEBUG_NEW_IN_COMMANDS              =     false;
static const int   DEBUG_DISPATCH_COMMANDS            =     false;
static const int   DEBUG_RING_COUNT                   =     false;
static const nByte UDP_PACKAGE_HEADER_LENGTH          =        12;
static const int   ENET_PEER_PACKET_LOSS_SCALE        = (1 << 16);
static const int   ENET_PEER_DEFAULT_ROUND_TRIP_TIME  =       300;
static const int   ENET_PEER_PACKET_THROTTLE_INTERVAL =      5000;


// Constants from PhotonConnect

static const int MSGT_INIT       = 0; // not used at the moment
static const int MSGT_INIT_RES   = 1;
static const int MSGT_OP         = 2; // operation request
static const int MSGT_OP_RES     = 3; // operation response
static const int MSGT_EV         = 4; // an event is coming in
static const int MSGT_INT_OP     = 6; // internal operation request (used for init encryption)
static const int MSGT_INT_OP_RES = 7; // internal operation response (used for init encryption)


// Constants from PhotonCommand

static const int FLAG_RELIABLE             = 1;
static const int FLAG_UNSEQUENCED          = 2;

static const int FV_UNRELIABLE             = 0;
static const int FV_RELIABLE               = 1;
static const int FV_UNRELIABLE_UNSEQUENCED = 2;

static const int CT_NONE           =  0;
static const int CT_ACK            =  1;
static const int CT_CONNECT        =  2;
static const int CT_VERIFYCONNECT  =  3;
static const int CT_DISCONNECT     =  4;
static const int CT_PING           =  5;
static const int CT_SENDRELIABLE   =  6;
static const int CT_SENDUNRELIABLE =  7;
static const int CT_SENDFRAGMENT   =  8;
// bandwidth limit          =  9;
// throttle config          = 10;
// unsequenced              = 11;
static const int CT_EG_SERVERTIME  = 12; //immediately acknowledged (ack sent without any other commands)

// Commands buffer max length.
static const int COMMANDS_BUF_LEN = 20;

static const int PHOTON_COMMAND_HEADER_LENGTH            =                                12;
static const int PHOTON_COMMAND_UNRELIABLE_HEADER_LENGTH =                                 4;
static const int PHOTON_COMMAND_HEADER_FRAGMENT_LENGTH   = PHOTON_COMMAND_HEADER_LENGTH + 20;
static const int MSG_HEADER_BYTES                        =                                 2;
static const int TCP_HEADER_LENGTH                       =                                 7;
static const int TCP_PING_LENGTH                         =                                 9;

static const nByte PHOTON_CODE_CLIENT_KEY     = 1;
static const nByte PHOTON_CODE_SERVER_KEY     = 1;
static const nByte PHOTON_KEY_INIT_ENCRYPTION = 0;

#endif // __PHOTON_CONSTANTS_H__