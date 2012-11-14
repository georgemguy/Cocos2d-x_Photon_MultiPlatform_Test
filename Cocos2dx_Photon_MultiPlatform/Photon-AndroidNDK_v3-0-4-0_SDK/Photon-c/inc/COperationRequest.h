/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __C_OPERATION_REQUEST_H
#define __C_OPERATION_REQUEST_H

#include "data_structures.h"

typedef struct _COperationRequest
{
	nByte operationCode;
	EG_Dictionary parameters;
} COperationRequest;

#ifdef __cplusplus
extern "C"
{
#endif
	// public API functions
	COperationRequest* OperationRequest_create(nByte opCode, EG_Dictionary parameters);
	COperationRequest* OperationRequest_init(COperationRequest* pOperationRequest, nByte opCode, EG_Dictionary parameters);
	void OperationRequest_delete(COperationRequest* pOperationRequest);
	void OperationRequest_clean(COperationRequest* pOperationRequest);
	EG_CHAR* OperationRequest_toString(COperationRequest* pOperationRequest, bool withParameters, bool withParameterTypes);
	EG_Object* OperationRequest_getParameterForCode(COperationRequest* pOperationRequest, nByte parameterCode);

	// public API getter/setter functions
	nByte OperationRequest_getOperationCode(COperationRequest* pOperationRequest);
	EG_Dictionary* OperationRequest_getParameters(COperationRequest* pOperationRequest);
	int OperationRequest_getParametersCount(COperationRequest* pOperationRequest);
#ifdef __cplusplus
}
#endif 

#endif