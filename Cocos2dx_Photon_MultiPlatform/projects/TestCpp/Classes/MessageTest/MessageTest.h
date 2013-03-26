//
//  MessageTest.h
//  TestCpp
//
//  Created by George Guy on 3/24/13.
//
//

#ifndef __TestCpp__MessageTest__
#define __TestCpp__MessageTest__

#include "../testBasic.h"

USING_NS_CC;

class MessageTest: public CCLayer
{
    CCLabelTTF* _stateLabel;
    
public:
    MessageTest(void);
    ~MessageTest(void);
    
    virtual std::string title();
    virtual void onEnter();
    virtual void onExit();
    virtual void desertCallback( CCObject* sender );
    virtual void forestCallback( CCObject* sender );
};

class MessageTestScene : public TestScene
{
    CC_SYNTHESIZE_READONLY( MessageTest*, _MessageTest, MessageTest );
    
public:
    virtual void runThisTest();
};

#endif /* defined(__TestCpp__MessageTest__) */
