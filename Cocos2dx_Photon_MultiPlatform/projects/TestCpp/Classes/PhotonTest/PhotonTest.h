#ifndef _PHOTON_TEST_H_
#define _PHOTON_TEST_H_

#include "../testBasic.h"
#include "StdIO_UIListener.h"
#include "Photon_lib.h"

USING_NS_CC;

class PhotonTest: public CCLayer
{
    CC_SYNTHESIZE_READONLY(UIListener*, _listener, Listener);
    
    PhotonLib _photonLib;
    
    CCLabelTTF* _stateLabel;
    
public:
    PhotonTest(void);
    ~PhotonTest(void);

    virtual std::string title();
    virtual void onEnter();
    virtual void onExit();
    virtual void update( float delta );
    PhotonLib& getPhotonLib();
};

class PhotonTestScene : public TestScene
{
    CC_SYNTHESIZE_READONLY( PhotonTest*, _photonTest, PhotonTest );
    
public:
    virtual void runThisTest();
    static PhotonLib& sharedPhotonLib();
};

#endif
