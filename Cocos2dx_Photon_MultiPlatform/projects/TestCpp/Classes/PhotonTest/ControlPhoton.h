#ifndef TestCpp_ConnectButton_h
#define TestCpp_ConnectButton_h

#include "cocos-ext.h"

class ConnectButton : public cocos2d::extension::CCControlButton
{
protected:
    
public:
    ConnectButton();
    ~ConnectButton();
    virtual bool init();
    CREATE_FUNC(ConnectButton);
    virtual void touchUpInsideAction(cocos2d::CCObject *sender, cocos2d::extension::CCControlEvent controlEvent);
    
    virtual void update ( float delta );
    virtual bool isConnected();
};

class SendButton : public cocos2d::extension::CCControlButton
{
protected:
    
public:
    SendButton();
    ~SendButton();
    virtual bool init();
    CREATE_FUNC(SendButton);
    virtual void touchUpInsideAction(cocos2d::CCObject *sender, cocos2d::extension::CCControlEvent controlEvent);
    
    virtual void update ( float delta );
    virtual bool canSend();
};

#endif
