#ifndef _TESTS_H_
#define _TESTS_H_

#include "PhotonTest/PhotonTest.h"
#include "PhotonLoadBalancingTest/PhotonLoadBalancingTest.h"

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
