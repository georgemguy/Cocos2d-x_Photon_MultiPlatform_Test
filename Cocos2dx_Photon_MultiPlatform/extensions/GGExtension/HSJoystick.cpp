#include <iostream>

////////////////////////////////// HSJoystick.cpp

#include "HSJoystick.h" 

/*#define JOYSTICK_OFFSET_X 5.0f
#define JOYSTICK_OFFSET_Y 5.0f

#define JOYSTICK_RADIUS 64.0f

#define THUMB_RADIUS 26.0f*/

static CCPoint convertCoordinate(CCPoint point){
    return CCDirector::sharedDirector()->convertToGL(point);
}

static bool isPointInCircle(CCPoint point, CCPoint center, float radius){
    float dx = (point.x - center.x);
    float dy = (point.y - center.y);
    return (radius >= sqrt((dx*dx)+(dy*dy)));
}

HSJoystick* HSJoystick::create( CCPoint position, CCPoint off, float rad, float thumbRad )
{
    HSJoystick* ret = new HSJoystick();
    
    if( ret && ret->init( position, off, rad, thumbRad ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE( ret );
    }
    return ret;
}

bool HSJoystick::init( CCPoint position, CCPoint off, float rad, float thumbRad )
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        CC_BREAK_IF(!CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////
        this->radius = rad;
        this->offset = off;
        this->setPosition( position );
        this->thumbRadius = thumbRad;
        
        kCenter=CCPoint( this->radius + this->offset.x,
                        this->radius + this->offset.y );
        
        this->setTouchEnabled(true);
        velocity = CCPointZero;
        
        CCSprite *bg = CCSprite::create("hud3.png");
        bg->setPosition(kCenter);
        this->addChild(bg,0);
        
        thumb = CCSprite::create("CloseNormal.png");
        thumb->setPosition(kCenter);
        this->addChild(thumb,1);
        
        kCenter = ccpAdd( kCenter, this->getPosition() );
        bRet=true;
        
    }while(0);
    
    return bRet;
}

void HSJoystick::updateVelocity(CCPoint point)
{
    CCPoint worldCenter = this->convertToWorldSpace( this->kCenter );

    // calculate Angle and length
    float dx = point.x - this->kCenter.x;
    float dy = point.y - this->kCenter.y;
    
    float distance = sqrt(dx*dx + dy*dy);
    float angle = atan2(dy,dx); // in radians
    
    if(distance > this->radius){
        dx = cos(angle) * this->radius;
        dy = sin(angle) * this->radius;
    }
    
    velocity = CCPointMake(dx/this->radius, dy/this->radius);
    
    if(distance>this->thumbRadius)
    {
        point.x = this->kCenter.x + cos(angle) * this->thumbRadius;
        point.y = this->kCenter.y + sin(angle) * this->thumbRadius;
    }
    
    thumb->setPosition( this->convertToNodeSpace( point ) );
}

void HSJoystick::resetJoystick()
{
    this->updateVelocity(kCenter);
}

bool HSJoystick::handleLastTouch()
{
    bool wasPressed = isPressed;
    if(wasPressed){
        this->resetJoystick();
        isPressed = false;
    }
    return (wasPressed ? true : false);
}

void HSJoystick::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint point = touch->locationInView();
    point = convertCoordinate(point);
    
    if(isPointInCircle(point,kCenter,this->radius)){
        isPressed = true;
        this->updateVelocity(point);
    }
}

void HSJoystick::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
    if(isPressed){
        CCTouch *touch = (CCTouch*)pTouches->anyObject();
        CCPoint point = touch->locationInView();
        point = convertCoordinate(point);
        this->updateVelocity(point);
    }
}

void HSJoystick::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
    this->handleLastTouch();
}

void HSJoystick::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
    this->handleLastTouch();
}
