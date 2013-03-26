//
//  Stage.cpp
//  SumNationOnline
//
//  Created by George Guy on 12/23/12.
//
//

#include "PMSGameScene.h"
#include "ControlDualEngine.h"
#include "PMSGameLayer.h"
#include "CCPhysicsSpriteLayer.h"

USING_NS_CC;
using namespace CCBoxExtension;

PMSGameScene::PMSGameScene() : super()
{
    
}

PMSGameScene::~PMSGameScene()
{
    
}

void PMSGameScene::onEnter()
{
    super::onEnter();
}

bool PMSGameScene::init()
{
    if( super::init() )
    {
        CCDirector* director = CCDirector::sharedDirector();
        ControlDualEngine* controls = ControlDualEngine::create( "engine_background.png", "engine_bar.png", "shot-c.png" );
        this->addChild( controls, PMSGameScene::Child::Z::controls, PMSGameScene::Child::ControlDualEngine_controls );
        
        PMSGameLayer* game = PMSGameLayer::create( director->getWinSize() );
        this->addChild( game, PMSGameScene::Child::Z::game, PMSGameScene::Child::CCPhysicsSpriteLayer_game );
        
        return true;
    }
    return false;
}