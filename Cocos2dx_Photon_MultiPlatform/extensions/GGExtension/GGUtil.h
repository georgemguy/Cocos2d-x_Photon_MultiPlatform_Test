//
//  CCUtil.h
//
//  Created by George Guy on 8/14/12.
//  Copyright (c) 2012 Perpetual Motion Studios. All rights reserved.
//

#pragma once
#ifndef CCAndToast_CCUtil_h
#define CCAndToast_CCUtil_h
#include "cocos-ext.h"

const float DOUBLE_TOUCH_TIME = 0.75f;

#define COPY_FUNC(classname, supername) \
virtual cocos2d::CCObject* copyWithZone( cocos2d::CCZone* pZone ) \
{ \
cocos2d::CCZone *pNewZone = NULL; \
classname *pRet = NULL; \
if (pZone && pZone->m_pCopyObject) { \
pRet = (classname*) (pZone->m_pCopyObject); \
} else { \
pRet = new classname(); \
pZone = pNewZone = new cocos2d::CCZone(pRet); \
} \
supername::copyWithZone(pZone); \
CC_SAFE_DELETE(pNewZone); \
return pRet; \
}

#define COPY_OBJECT_FUNC(classname) \
virtual cocos2d::CCObject* copyWithZone( cocos2d::CCZone* pZone ) \
{ \
cocos2d::CCZone *pNewZone = NULL; \
classname *pRet = NULL; \
if (pZone && pZone->m_pCopyObject) { \
pRet = (classname*) (pZone->m_pCopyObject); \
} else { \
pRet = new classname(); \
pZone = pNewZone = new cocos2d::CCZone(pRet); \
} \
CC_SAFE_DELETE(pNewZone); \
return pRet; \
}

#define COPY_INIT_FUNC(classname, supername, initcall) \
virtual cocos2d::CCObject* copyWithZone( cocos2d::CCZone* pZone ) \
{ \
cocos2d::CCZone *pNewZone = NULL; \
classname *pRet = NULL; \
if (pZone && pZone->m_pCopyObject) { \
pRet = (classname*) (pZone->m_pCopyObject); \
} else { \
pRet = new classname(); \
pZone = pNewZone = new cocos2d::CCZone(pRet); \
} \
supername::copyWithZone(pZone); \
pRet->initcall; \
CC_SAFE_DELETE(pNewZone); \
return pRet; \
}

#define COPY_OBJECT_INIT_FUNC(classname, initcall) \
virtual cocos2d::CCObject* copyWithZone( cocos2d::CCZone* pZone ) \
{ \
cocos2d::CCZone *pNewZone = NULL; \
classname *pRet = NULL; \
if (pZone && pZone->m_pCopyObject) { \
pRet = (classname*) (pZone->m_pCopyObject); \
} else { \
pRet = new classname(); \
pZone = pNewZone = new cocos2d::CCZone(pRet); \
} \
pRet->initcall; \
CC_SAFE_DELETE(pNewZone); \
return pRet; \
}

#define CREATE_INIT_MODEL_FUNC(classname,modelclassname) \
static classname* create( modelclassname * model ) \
{ \
classname* ret = new classname(); \
if( ret && ret->init(model) ) \
{ \
ret->autorelease(); \
} \
else if( ret ) ret->release(); \
return ret; \
}

#define ACTION_CREATE_TAG_FUNC(classname, tag) \
static classname* create() \
{ \
    classname* ret = new classname(); \
    if( ret ) \
    { \
        ret->autorelease(); \
        ret->setTag( tag ); \
    } \
    return ret; \
}

#define ACTION_CREATE_INIT_TAG_FUNC(classname, tag) \
static classname* create() \
{ \
classname* ret = new classname(); \
if( ret && ret->init() ) \
{ \
ret->autorelease(); \
ret->setTag( tag ); \
} \
else if( ret ) ret->release(); \
return ret; \
}

#define CC_CONSTRUCT_SINGLETON(varType)\
CCAssert( ! _shared ##varType,\
"" #varType " -- double instantiation of singleton class" );\
_shared ##varType = this

#define CC_SYNTHESIZE_SINGLETON(varType)\
protected: static varType* _shared ##varType;\
public: inline static varType* shared ##varType()\
{\
    return varType::_shared ##varType;\
};\
public: inline static void purge ##varType()\
{\
    CC_SAFE_DELETE(varType::_shared ##varType);\
    varType::_shared ##varType = NULL;\
};

#define CC_PROPERTY_SINGLETON(funName)\
protected: static funName* _shared ##funName;\
public: static funName* shared ##funName();\
public: static void purge ##funName();\
private:

#define CC_INITIALIZE_SINGLETON(varType)\
varType * varType ::_shared ##varType = NULL

#define CC_DESTROY_SINGLETON(varType)\
if( this == _shared ##varType )\
{\
    _shared ##varType = NULL;\
}

#define CC_IMPLEMENT_BACK_BUTTON_FOR_LAYER_PLEASE_ENABLE_KEYPAD \
inline virtual void keyBackClicked() \
{ \
    using namespace cocos2d; \
    CCDirector* director = CCDirector::sharedDirector(); \
    if( director ) \
    { \
        director->popScene(); \
    } \
}

#define CC_SYNTHESIZE_CHILD(varType, varName, funName)\
private: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var)\
{\
if(varName) this->removeChild(varName,true);\
if(var)\
{\
varName = var;\
this->addChild(var);\
}\
else\
{\
varName = NULL;\
}\
}

#define CC_SYNTHESIZE_TAG_CHILD(varType, varName, funName, zOrder, tag)\
private: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var)\
{\
if(varName) this->removeChild(varName,true);\
if(var)\
{\
CCNode* old = NULL;\
while(( old = this->getChildByTag( tag ) )) this->removeChild( old, true );\
varName = var;\
this->addChild(var, zOrder, tag);\
}\
else\
{\
varName = NULL;\
}\
}

#define CC_SYNTHESIZE_ACTION(varType, varName, funName)\
private: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var)\
{\
this->stopAction( varName );\
varName = var;\
if(var) this->runAction(var);\
}

#define CC_SYNTHESIZE_CONTROL(varName,funName)\
public:\
CC_SYNTHESIZE_CHILD(cocos2d::extension::CCControl*,varName,funName);\
virtual void controlCallback##funName(cocos2d::CCObject* pSender)

#define CC_RANDOM_VARY(mean,variance) mean + ( CCRANDOM_MINUS1_1() * variance )

#define CC2DARRAY_FOREACH(__array__, __object__)\
for( int __c__ = 0, __r__ = 0;\
( __c__ < __array__->count() ) &&\
( __object__ = __array__->objectAtIndex(__c__) ) &&\
( __r__ < ( (cocos2d::CCArray*) __object__ )->count() ) &&\
( __object__ = ( (cocos2d::CCArray*) __object__ )->objectAtIndex(__r__) );\
( ( ++__r__ < ( (cocos2d::CCArray*) ( (cocos2d::CCArray*) __array__ )->objectAtIndex(__c__) )->count() ) ?\
0 : (__r__ = 0) || (__c__++) ) )

    
    inline void CCDynamicEnable( cocos2d::CCNode* child, bool enable )
    {
        cocos2d::CCMenu* targetMenu = dynamic_cast<cocos2d::CCMenu*>(child);
        if( targetMenu )
        {
            targetMenu->setTouchEnabled( enable );
        }
        else
        {
            cocos2d::extension::CCScrollView* targetScroll = dynamic_cast<cocos2d::extension::CCScrollView*>(child);
            if( targetScroll )
            {
                targetScroll->setTouchEnabled( enable );
            }
            else
            {
                cocos2d::extension::CCControl* targetControl = dynamic_cast<cocos2d::extension::CCControl*>(child);
                if( targetControl )
                {
                    targetControl->setEnabled( enable );
                }
            }
        }
    };
    
    inline void CCRecursiveEnable( cocos2d::CCNode* target, bool enable, cocos2d::CCNode* exempt = NULL )
    {
        USING_NS_CC;
        cocos2d::CCObject* o = NULL;
        cocos2d::CCNode* child = NULL;
        CCARRAY_FOREACH( target->getChildren(), o )
        {
            child = (cocos2d::CCNode*) o;
            if( child != exempt )
            {
                CCDynamicEnable( child, enable );
                CCDynamicEnable( child, enable );
            }
        }
    };
    

namespace GGUtil {

struct CCCardinal
{
    enum _Side
    {
        middle = 0,
        left = -1,
        right = 1,
        top = -1,
        bottom = 1
    } Side;
    
    enum _Compass
    {
        axis = 0,
        north,
        northEast,
        east,
        southEast,
        south,
        southWest,
        west,
        northWest
    } Compass;
};
    
};

inline cocos2d::CCNode* ScaleNodeToSize( cocos2d::CCNode* node, cocos2d::CCSize size )
{
    cocos2d::CCSize oldSize = node->getContentSize();
    
    node->setScaleX( ( size.width / oldSize.width ) / node->getScaleX() );
    node->setScaleY( ( size.height / oldSize.height ) / node->getScaleY() );
    return node;
};

inline cocos2d::CCNode* ScaleNodeAndContent( cocos2d::CCNode* node, cocos2d::CCSize size )
{
    cocos2d::CCSize oldSize = node->getContentSize();
    
    node->setContentSize( size );
    node->setScaleX( ( size.width / oldSize.width ) / node->getScaleX() );
    node->setScaleY( ( size.height / oldSize.height ) / node->getScaleY() );
    
    return node;
};

inline cocos2d::ccColor3B InverseColor3B( cocos2d::ccColor3B color )
{
    return cocos2d::ccc3( 255 - color.r, 255 - color.g, 255 - color.b );
};

inline cocos2d::CCPoint DiscretePoint( cocos2d::CCPoint point, const cocos2d::CCPoint& min, const cocos2d::CCPoint& max )
{
    point.x = floorf( point.x + 0.5f );
    point.y = floorf( point.y + 0.5f );
    cocos2d::ccpClamp( point, min, max );
    return point;
};

inline cocos2d::CCPoint DiscretePoint( cocos2d::CCPoint point )
{
    point.x = floorf( point.x + 0.5f );
    point.y = floorf( point.y + 0.5f );
    return point;
};
    
#endif
