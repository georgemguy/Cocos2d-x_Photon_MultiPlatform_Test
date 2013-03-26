//
//  CCMainMenu.cpp
//  SumNationOnline
//
//  Created by George Guy on 11/26/12.
//
//

#include "MainMenu.h"
#include "cocos-ext.h"
#include "PMSGameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

CC_INITIALIZE_SINGLETON(MainMenu);

MainMenu::MainMenu()
{
    CC_CONSTRUCT_SINGLETON(MainMenu);
}

MainMenu::~MainMenu()
{
    CC_DESTROY_SINGLETON(MainMenu);
}

bool MainMenu::initPassAndPlay()
{
    this->removeChildByTag( Child::CCMenuItem_passAndPlay, true );
    
    CCMenuItem* item = CCMenuItem::create( this, menu_selector( MainMenu::passAndPlayCallback ) );
    CCSprite* sprite = CCSprite::create( "button_passAndPlay.png" );
    sprite->setAnchorPoint(CCPointZero);
    item->setContentSize( sprite->getContentSize() );
    item->addChild( sprite );
    CCLabelTTF* label = CCLabelTTF::create("Pass and Play", "American Typewritter.ttf", 24);
    label->setAnchorPoint(CCPointZero);
    label->setPosition( ccp( sprite->getContentSize().width * 0.25, sprite->getContentSize().height * 0.5 ) );
    item->addChild(label);
    
    this->addChild( item, 0, Child::CCMenuItem_passAndPlay );
    return true;
}

bool MainMenu::initQuit()
{
    this->removeChildByTag( Child::CCMenuItem_quit, true );
    
    CCMenuItem* item = CCMenuItem::create( this, menu_selector( MainMenu::quitCallback ) );
    CCSprite* sprite = CCSprite::create( "button_EXIT.png" );
    sprite->setAnchorPoint(CCPointZero);
    item->setContentSize( sprite->getContentSize() );
    item->addChild( sprite );
    CCLabelTTF* label = CCLabelTTF::create("Quit Game", "American Typewritter.ttf", 24);
    label->setAnchorPoint(CCPointZero);
    label->setPosition( ccp( sprite->getContentSize().width * 0.25, sprite->getContentSize().height * 0.5 ) );
    item->addChild(label);
    

    this->addChild( item, 0, Child::CCMenuItem_quit );
    return true;
}

bool MainMenu::init()
{
    if( CCMenu::init() && this->initPassAndPlay() && this->initQuit() )
    {
        CCDirector* director = CCDirector::sharedDirector();
        CCSize winSize = director->getWinSize();
        CCPoint winSizePoint = ccpFromSize( winSize );
        CCPoint center = ccpMult( winSizePoint, 0.5f );
        /*char str[128] = { '\0' };
        sprintf( str, "width %lf, height %lf", winSize.width, winSize.height );
        CCLabelTTF* label = CCLabelTTF::create( str, "American Typewriter.ttf",  16 );
        label->setPosition( center );
        this->getChildByTag( Child::CCMenuItem_playOnline )->addChild( label );*/
        this->alignItemsVertically();
        return true;
    }
    return false;        
}

void MainMenu::passAndPlayCallback( cocos2d::CCObject* sender )
{    
    CCDirector* director = CCDirector::sharedDirector();
    CCScene* gameScene = PMSGameScene::create();
    director->pushScene( gameScene );
}

void MainMenu::quitCallback( cocos2d::CCObject* sender )
{
    CCDirector::sharedDirector()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}