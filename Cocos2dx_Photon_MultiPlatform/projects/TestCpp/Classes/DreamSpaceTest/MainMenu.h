//
//  CCMainMenu.h
//  SumNationOnline
//
//  Created by George Guy on 11/26/12.
//
//

#ifndef __SumNationOnline__MainMenu__
#define __SumNationOnline__MainMenu__

#include "cocos2d.h"
#include "GGUtil.h"

class MainMenu : public cocos2d::CCMenu
{
public:
    MainMenu();
    virtual ~MainMenu();
    struct Child
    {
        enum _Tag
        {
            CCMenuItem_passAndPlay,
            CCMenuItem_quit,
            CHILD_TAG_COUNT
        } Tag;
    };
    
    CREATE_FUNC(MainMenu);
    CC_SYNTHESIZE_SINGLETON(MainMenu);
    virtual bool init();
    virtual bool initPassAndPlay();
    virtual bool initQuit();
    
    virtual void passAndPlayCallback( cocos2d::CCObject* sender );
    virtual void quitCallback( cocos2d::CCObject* sender );
};



#endif /* defined(__SumNationOnline__CCMainMenu__) */
