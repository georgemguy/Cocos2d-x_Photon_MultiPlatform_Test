#ifndef _TESTS_H_
#define _TESTS_H_

#include "PhotonTest/PhotonTest.h"
#include "PhotonLoadBalancingTest/PhotonLoadBalancingTest.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
    #include "ChipmunkAccelTouchTest/ChipmunkAccelTouchTest.h"
#else
#ifdef MARMALADEUSECHIPMUNK
#if    (MARMALADEUSECHIPMUNK == 1)
    #include "ChipmunkAccelTouchTest/ChipmunkAccelTouchTest.h"
#endif
#endif
#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)

#include "ExtensionsTest/ExtensionsTest.h"
#include "MutiTouchTest/MutiTouchTest.h"

enum
{
    TEST_PHOTON = 0,
    TEST_PHOTON_LOADBALANCING,
    TESTS_COUNT,    
};

const std::string g_aTestNames[TESTS_COUNT] =
{
    "PhotonTest",
    "PhotonLoadBalancingTest",
};

#endif
