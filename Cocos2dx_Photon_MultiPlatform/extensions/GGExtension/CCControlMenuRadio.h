//
//  ControlOptions.h
//  Abstroku
//
//  Created by George Guy on 9/14/12.
//
//
#pragma once
#ifndef Abstroku_CCControlMenuRadio_h
#define Abstroku_CCControlMenuRadio_h

#include "GGUtil.h"
#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

class CCControlMenuRadio : public cocos2d::CCMenu
{
    CC_SYNTHESIZE(cocos2d::extension::CCInvocation*, _onSelectInvocation, OnSelectInvocation)
protected:
    CCControlMenuRadio();
    virtual ~CCControlMenuRadio();
    
public:
    
    virtual int getSelectedControlTag();
    virtual cocos2d::extension::CCControl* getSelectedControl();
    virtual void controlCallbackFixSwitches( cocos2d::CCObject* sender );
    virtual void addChild(cocos2d::CCNode *child, int zOrder, int tag );
    
    inline virtual void addChild(cocos2d::CCNode *child, int zOrder )
    { cocos2d::CCNode::addChild( child, zOrder ); };
    inline virtual void addChild(cocos2d::CCNode *child )
    { cocos2d::CCNode::addChild( child ); };

    static CCControlMenuRadio* create( cocos2d::extension::CCInvocation* invocation, cocos2d::CCMenuItem* item, ...);
    static CCControlMenuRadio* create( cocos2d::extension::CCInvocation* invocation );
    static CCControlMenuRadio* create( cocos2d::CCObject* target, cocos2d::extension::SEL_CCControlHandler action );
    CREATE_FUNC(CCControlMenuRadio);
};

NS_CC_EXT_END

#endif
