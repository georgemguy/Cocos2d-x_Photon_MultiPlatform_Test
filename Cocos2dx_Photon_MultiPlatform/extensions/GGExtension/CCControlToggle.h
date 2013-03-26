//
//  CCControlToggle.h
//  Abstroku
//
//  Created by George Guy on 9/15/12.
//
//
#pragma once
#ifndef Abstroku_CCControlToggle_h
#define Abstroku_CCControlToggle_h

#include "GGUtil.h"
#include "cocos2d.h"
#include "cocos-ext.h"

class CCControlToggle : public cocos2d::extension::CCControlButton
{
    CCControlToggle();
    virtual ~CCControlToggle();
    CC_SYNTHESIZE(bool, _dimOnDeselect, DimOnDeselect);
    
protected:
    virtual void toggleSelected();
    
public:    
    virtual void setSelected( bool enable );
    
    virtual bool initWithLabelAndSprites(
                                         CCNode* label,
                                         cocos2d::extension::CCScale9Sprite* normalSprite );
    virtual bool initWithLabelAndSprites(
                                        CCNode* label,
                                        cocos2d::extension::CCScale9Sprite* normalSprite,
                                        cocos2d::extension::CCScale9Sprite* selectedSprite );
    static CCControlToggle* create(
                                 CCNode* label,
                                 cocos2d::extension::CCScale9Sprite* normalSprite );
    static CCControlToggle* create(
                                 CCNode* label,
                                 cocos2d::extension::CCScale9Sprite* normalSprite,
                                 cocos2d::extension::CCScale9Sprite* selectedSprite );
};

#endif
