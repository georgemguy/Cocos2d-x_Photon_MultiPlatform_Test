//
//  ControlOptions.cpp
//  Abstroku
//
//  Created by George Guy on 9/14/12.
//
//

#include "CCRadioMenu.h"

NS_CC_EXT_BEGIN

const int CCRadioMenu::TOGGLE_TAG = 1;

CCRadioMenu::CCRadioMenu() : CCMenu()
{
    this->_onSelectInvocation = NULL;
}

CCRadioMenu::~CCRadioMenu()
{
    this->setOnSelectInvocation( NULL );
}

CCControlToggle* CCRadioMenu::getControlByTag( int tag )
{
    CCNode* child = this->getChildByTag( tag );
    
    if( child )
    {
        return ( CCControlToggle* ) child->getChildByTag( TOGGLE_TAG );
    }
    
    return false;
}

CCControlToggle* CCRadioMenu::setSelectedControlByTag( int tag )
{
    CCControlToggle* toggle = this->getControlByTag( tag );
    
    if( toggle )
    {
        toggle->setSelected( true );
    }
    
    return toggle;
}

CCControlToggle* CCRadioMenu::getSelectedControl()
{
    CCMenuItem* item = NULL;
    CCControlToggle* control = NULL;
    CCObject* child = NULL;
    CCARRAY_FOREACH(this->getChildren(), child)
    {
        item = (CCMenuItem*)(child);
        control = (CCControlToggle*) item->getChildByTag( TOGGLE_TAG );
        if( control && control->isSelected() )
        {
            return control;
        }
    }
    return NULL;
}

void CCRadioMenu::controlCallbackFixSwitches( cocos2d::CCObject* sender )
{
    CCControlToggle* control = (CCControlToggle*)(sender);
    
    if( control )
    {
        CCMenuItem* item = NULL;
        CCObject* child = NULL;
        CCARRAY_FOREACH(this->getChildren(), child)
        {
            item = (CCMenuItem*)(child);
            control = (CCControlToggle*) item->getChildByTag( TOGGLE_TAG );
            if( control && control != sender )
            {
                control->setSelected( false );
            }
        }
    }
}

void CCRadioMenu::addChild(CCNode* child, int zOrder, int tag)
{
    CCControlToggle* control = dynamic_cast<CCControlToggle*>(child);
    CCAssert( control, "CCRadioMenu::addChild() -- CCRadioMenu only supports CCControlToggles as children." );
    
    control->setSelected( false );
    control->addTargetWithActionForControlEvents(
                                                this,
                                                cccontrol_selector(CCRadioMenu::controlCallbackFixSwitches),
                                                CCControlEventTouchUpInside );
    
    CCInvocation* invocation = this->getOnSelectInvocation();
    if( invocation )
    {
        control->addTargetWithActionForControlEvents(
                                                    invocation->getTarget(),
                                                    invocation->getAction(),
                                                    invocation->getControlEvent() );
    }
    
    if( tag == 0 )
    {
        tag = child->getTag();
    }
    
    CCMenuItem* item = CCMenuItem::create();
    item->setContentSize( control->getContentSize() );
    item->addChild( control, 0, TOGGLE_TAG );
    CCMenu::addChild( item, zOrder, tag );
}

CCRadioMenu * CCRadioMenu::create( CCInvocation* invocation )
{
    CCRadioMenu *pRet = new CCRadioMenu();
    if (pRet && pRet->init())
    {
        pRet->setOnSelectInvocation( invocation );
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCRadioMenu * CCRadioMenu::create( CCObject* target, SEL_CCControlHandler action )
{
    CCRadioMenu *pRet = new CCRadioMenu();
    if (pRet && pRet->init())
    {
        CCInvocation* invocation = new CCInvocation( target, action, CCControlEventTouchUpInside );
        invocation->autorelease();
        pRet->setOnSelectInvocation( invocation );
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}
/*
CCRadioMenu * CCRadioMenu::create( CCInvocation* invocation, CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    CCRadioMenu *pRet = new CCRadioMenu();
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
}
*/
NS_CC_EXT_END