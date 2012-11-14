#ifndef _PHOTON_LOADBALANCING_TEST_H_
#define _PHOTON_LOADBALANCING_TEST_H_

#include "../testBasic.h"
//#include "StdIO_UIListener.h"
//#include "Photon_lib.h"

USING_NS_CC;

class PhotonLoadBalancingTest: public CCLayer
{
    //CC_SYNTHESIZE_READONLY(UIListener*, _listener, Listener);
    
    //PhotonLib _photonLib;
    
    CCLabelTTF* _stateLabel;
    
public:
    PhotonLoadBalancingTest(void);
    ~PhotonLoadBalancingTest(void);

    virtual std::string title();
    virtual void onEnter();
    virtual void onExit();
    //virtual void update( float delta );
    //PhotonLib& getPhotonLib();
};

class PhotonLoadBalancingTestScene : public TestScene
{
    CC_SYNTHESIZE_READONLY( PhotonLoadBalancingTest*, _photonLoadBalancingTest, PhotonLoadBalancingTest );
    
public:
    virtual void runThisTest();
    //static PhotonLib& sharedPhotonLib();
};

#endif
