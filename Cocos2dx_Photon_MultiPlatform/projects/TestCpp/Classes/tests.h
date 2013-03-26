#ifndef _TESTS_H_
#define _TESTS_H_

#include "PhotonLoadBalancingTest/PhotonLoadBalancingTest.h"
#include "PhotonTest/PhotonTest.h"
#include "MessageTest/MessageTest.h"

enum
{
    TEST_MESSAGE,
    TEST_PHOTON_LOADBALANCING,
    TESTS_COUNT,    
};

const std::string g_aTestNames[TESTS_COUNT] =
{
    "MessageTest",
    "PhotonLoadBalancingTest"
};

#endif
