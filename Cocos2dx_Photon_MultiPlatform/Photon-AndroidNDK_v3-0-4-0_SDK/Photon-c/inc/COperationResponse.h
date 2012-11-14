/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __C_OPERATION_RESPONSE_H
#define __C_OPERATION_RESPONSE_H

#include "data_structures.h"

typedef struct _COperationResponse
{
	nByte operationCode;
	short returnCode;
	EG_CHAR* debugMessage;
	EG_HashTable parameters;
} COperationResponse;

#ifdef __cplusplus
extern "C"
{
#endif
	// public API functions
	EG_CHAR* OperationResponse_toString(COperationResponse* pOperationResponse, bool withDebugMessage, bool withParameters, bool withParameterTypes);
	EG_Object* OperationResponse_getParameterForCode(COperationResponse* pOperationResponse, nByte parameterCode);

	// public API getter/setter functions
	nByte OperationResponse_getOperationCode(COperationResponse* pOperationResponse);
	short OperationResponse_getReturnCode(COperationResponse* pOperationResponse);
	EG_CHAR* OperationResponse_getDebugMessage(COperationResponse* pOperationResponse);
	EG_HashTable* OperationResponse_getParameters(COperationResponse* pOperationResponse);
#ifdef __cplusplus
}
#endif 

#endif