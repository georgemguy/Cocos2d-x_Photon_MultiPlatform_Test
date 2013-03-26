
#ifndef UndeadInfection_HSJoystick_h
#define UndeadInfection_HSJoystick_h

//////////////////////////////////HSJoystick.h (I ported Obj-c code : http://www.cocos2d-iphone.org/forum/topic/1418 )

#pragma once
#include "cocos2d.h" 

using namespace cocos2d;

class HSJoystick : public CCLayer
{
    
public:
    static HSJoystick* create( CCPoint position = CCPointZero, CCPoint off = ccp( 5.0f, 5.0f ), float rad = 64.0f, float thumbRad = 26.0f );
    virtual bool init( CCPoint position = CCPointZero, CCPoint off = ccp( 5.0f, 5.0f ), float rad = 64.0f, float thumbRad = 26.0f );
    CCPoint getVelocity(){return velocity;}
    const CCPoint* getVelocitySource(){return &velocity;}
    inline CCPoint getCenter() { return this->kCenter; };
    
private:
    float thumbRadius;
    float radius;
    CCPoint offset;
    CCPoint kCenter;
    CCSprite *thumb;
    bool isPressed;
    
    CCPoint velocity;
    
    void updateVelocity(CCPoint point);
    void resetJoystick();
    bool handleLastTouch();
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};

#endif
