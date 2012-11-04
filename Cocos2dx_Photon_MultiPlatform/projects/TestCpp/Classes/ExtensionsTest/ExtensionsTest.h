#ifndef __EXTENSIONS_TEST_H__
#define __EXTENSIONS_TEST_H__

#include "../testBasic.h"
#include "PhotonPeer.h"

//using namespace ExitGames;
//using namespace Photon;

class ExtensionsMainLayer : public CCLayer
{
public:
    //PhotonPeer* peer;
    virtual void onEnter();
    void menuCallback(CCObject* pSender);
};

class ExtensionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* __EXTENSIONS_TEST_H__ */
