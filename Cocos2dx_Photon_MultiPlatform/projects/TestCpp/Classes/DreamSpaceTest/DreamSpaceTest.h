#ifndef _DREAM_SPACE_TEST_H_
#define _DREAM_SPACE_TEST_H_

#include "../testBasic.h"
//#include "StdIO_UIListener.h"
//#include "Photon_lib.h"

USING_NS_CC;

class DreamSpaceTest: public CCLayer
{
    //CC_SYNTHESIZE_READONLY(UIListener*, _listener, Listener);
    
    //PhotonLib _photonLib;
    
    CCLabelTTF* _stateLabel;
    
public:
    DreamSpaceTest(void);
    ~DreamSpaceTest(void);

    virtual std::string title();
    virtual void onEnter();
    virtual void onExit();
    //virtual void update( float delta );
    //PhotonLib& getPhotonLib();
};

class DreamSpaceTestScene : public TestScene
{
    CC_SYNTHESIZE_READONLY( DreamSpaceTest*, _dreamSpaceTest, DreamSpaceTest );
    
public:
    DreamSpaceTestScene();
    virtual void runThisTest();
    //static PhotonLib& sharedPhotonLib();
};

#endif
