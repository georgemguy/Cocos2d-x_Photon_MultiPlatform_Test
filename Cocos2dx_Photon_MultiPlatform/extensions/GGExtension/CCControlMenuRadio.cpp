//
//  ControlOptions.cpp
//  Abstroku
//
//  Created by George Guy on 9/14/12.
//
//

#include "CCControlMenuRadio.h"
#include "CCControlToggle.h"


USING_NS_CC;

NS_CC_EXT_BEGIN

CCControlMenuRadio::CCControlMenuRadio() : CCMenu()
{
    this->_onSelectInvocation = NULL;
}

CCControlMenuRadio::~CCControlMenuRadio()
{
    this->setOnSelectInvocation( NULL );
}



CCControl* CCControlMenuRadio::getSelectedControl()
{
    CCControlToggle* control;
    CCObject* child = NULL;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        control = dynamic_cast<CCControlToggle*>(child);
        if( control && control->isSelected() )
        {
            return control;
        }
    }
    return NULL;
}

int CCControlMenuRadio::getSelectedControlTag()
{
    CCControl* selected = this->getSelectedControl();
    if( selected )
    {
        CCNode* parent = selected->getParent();
        return parent->getTag();
    }
    return 0;
}

void CCControlMenuRadio::controlCallbackFixSwitches( cocos2d::CCObject* sender )
{
    CCControlToggle* control = dynamic_cast<CCControlToggle*>(sender);
    
    if( control )
    {
        CCObject* child = NULL;
        CCARRAY_FOREACH(this->getChildren(), child)
        {
            control = dynamic_cast<CCControlToggle*>(child);
            if( control && control != sender )
            {
                control->setSelected( false );
            }
        }
    }
}

void CCControlMenuRadio::addChild(cocos2d::CCNode *child, int zOrder, int tag )
{
    CCNode::addChild(child, zOrder, tag );
    CCControlToggle* control = dynamic_cast<CCControlToggle*>(child);
    if( control )
    {
        control->setSelected( false );
        control->addTargetWithActionForControlEvents(
                                                    this,
                                                    cccontrol_selector(CCControlMenuRadio::controlCallbackFixSwitches),
                                                    CCControlEventTouchUpInside );
        
        CCInvocation* invocation = this->getOnSelectInvocation();
        control->addTargetWithActionForControlEvents(
                                                    invocation->getTarget(),
                                                    invocation->getAction(),
                                                    invocation->getControlEvent() );
    }
}

CCControlMenuRadio * CCControlMenuRadio::create( CCInvocation* invocation )
{
    CCControlMenuRadio *pRet = new CCControlMenuRadio();
    if (pRet && pRet->init())
    {
        pRet->setOnSelectInvocation( invocation );
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCControlMenuRadio * CCControlMenuRadio::create( CCObject* target, SEL_CCControlHandler action )
{
    CCControlMenuRadio *pRet = new CCControlMenuRadio();
    if (pRet && pRet->init())
    {
        CCInvocation* invoke = new CCInvocation( target, action, CCControlEventTouchUpInside );
        invoke->autorelease();
        pRet->setOnSelectInvocation( invoke );
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}
/*
CCControlMenuRadio * CCControlMenuRadio::create( CCInvocation* invocation, CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    CCControlMenuRadio *pRet = new CCControlMenuRadio();
    if (pRet && pRet->initWithItems(item, args))
    {
        pRet->setOnSelectInvocation( invocation );
        pRet->autorelease();
        va_end(args);
        return pRet;
    }
    va_end(args);
    CC_SAFE_DELETE(pRet);
    return NULL;
}*/

NS_CC_EXT_END