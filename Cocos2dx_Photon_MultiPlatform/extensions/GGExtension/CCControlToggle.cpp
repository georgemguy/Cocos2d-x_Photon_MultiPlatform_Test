//
//  CCControlToggle.cpp
//  Abstroku
//
//  Created by George Guy on 9/15/12.
//
//

#include "CCControlToggle.h"
#include "GGUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCControlToggle::CCControlToggle() : CCControlButton()
{
    
}

CCControlToggle::~CCControlToggle()
{
    
}

void CCControlToggle::toggleSelected()
{
    if( this->isEnabled() )
    {
        this->setSelected( ! this->isSelected() );
    }
}

void CCControlToggle::setSelected(bool enabled)
{
    CCControlButton::setSelected(enabled);

    if( this->getBackgroundSpriteDispatchTable() && this->getDimOnDeselect() )
    {
        int tintValue = !isSelected() ? 96 : 255;
        this->setOpacity( tintValue );
    }
}

bool CCControlToggle::initWithLabelAndSprites(CCNode* label, CCScale9Sprite* normalSprite)
{
    if( this->initWithLabelAndBackgroundSprite( label, normalSprite ) )
    {
        this->setDimOnDeselect( true );
        this->addTargetWithActionForControlEvent(
                                                 this,
                                                 cccontrol_selector(CCControlToggle::toggleSelected),
                                                 CCControlEventTouchUpInside );
        this->setSelected( false );
        return true;
    }
    return false;
}

bool CCControlToggle::initWithLabelAndSprites(CCNode* label, CCScale9Sprite* normalSprite, CCScale9Sprite* selectedSprite)
{
    if( this->initWithLabelAndBackgroundSprite( label, normalSprite ) )
    {
        this->setDimOnDeselect( false );
        this->setBackgroundSpriteForState( selectedSprite, CCControlStateSelected );
        this->addTargetWithActionForControlEvent(
                                                 this,
                                                 cccontrol_selector(CCControlToggle::toggleSelected),
                                                 CCControlEventTouchUpInside );
        this->setSelected( false );
        return true;
    }
    return false;
}

CCControlToggle* CCControlToggle::create(CCNode* label, CCScale9Sprite* normalSprite)
{
    CCControlToggle *pRet = new CCControlToggle();
    pRet->initWithLabelAndSprites(label, normalSprite);
    pRet->autorelease();
    return pRet;
}

CCControlToggle* CCControlToggle::create(CCNode* label, CCScale9Sprite* normalSprite, CCScale9Sprite* selectedSprite)
{
    CCControlToggle *pRet = new CCControlToggle();
    pRet->initWithLabelAndSprites(label, normalSprite, selectedSprite);
    pRet->autorelease();
    return pRet;
}