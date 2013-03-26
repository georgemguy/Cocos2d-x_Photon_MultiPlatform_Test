//
//  ControlOptions.h
//  Abstroku
//
//  Created by George Guy on 9/14/12.
//
//

#ifndef Abstroku_CCRadioMenu_h
#define Abstroku_CCRadioMenu_h

#include "cocos2d.h"
#include "CCControlToggle.h"

NS_CC_EXT_BEGIN

class CCRadioMenu : public cocos2d::CCMenu
{    
    CC_SYNTHESIZE_RETAIN(cocos2d::extension::CCInvocation*, _onSelectInvocation, OnSelectInvocation)

public:
    CCRadioMenu();
    virtual ~CCRadioMenu();
    
    virtual CCControlToggle* getSelectedControl();
    virtual CCControlToggle* getControlByTag( int tag );
    virtual CCControlToggle* setSelectedControlByTag( int tag );
    virtual void controlCallbackFixSwitches( cocos2d::CCObject* sender );
    
    virtual void addChild(cocos2d::CCNode* child, int zOrder, int tag);
    inline virtual void addChild(cocos2d::CCNode* child,int zOrder){addChild(child,zOrder,0);};
    inline virtual void addChild(cocos2d::CCNode* child){addChild(child,0,0);};
    
    static CCRadioMenu* create( cocos2d::extension::CCInvocation* invocation, cocos2d::CCMenuItem* item, ...);
    static CCRadioMenu* create( cocos2d::extension::CCInvocation* invocation );
    static CCRadioMenu* create( cocos2d::CCObject* target, cocos2d::extension::SEL_CCControlHandler action );
    CREATE_FUNC(CCRadioMenu);
    
protected:
    static const int TOGGLE_TAG;
};

NS_CC_EXT_END

#endif
