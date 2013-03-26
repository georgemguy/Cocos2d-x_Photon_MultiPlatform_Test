/****************************************************************************
 Copyright (c) 2013 George Guy

 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "PhotonLoadBalancingTest.h"
#include "../testResource.h"
#include "CCLobbyView.h"

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \


//------------------------------------------------------------------
//
// PhotonLoadBalancingTest
//
//------------------------------------------------------------------
PhotonLoadBalancingTest::PhotonLoadBalancingTest(void) : CCLayer()
{
    this->_stateLabel = NULL;
}

PhotonLoadBalancingTest::~PhotonLoadBalancingTest(void)
{
}

std::string PhotonLoadBalancingTest::title()
{
    return "PhotonLoadBalancingTest";
}

void PhotonLoadBalancingTest::onEnter()
{
    CCLayer::onEnter();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint winCenter = ccpMult( ccpFromSize( winSize ), 0.5f );
    this->setContentSize(winSize);
    
    CCLobbyView* lobbyView = CCLobbyView::create( winSize );
    this->addChild( lobbyView );
    
    this->scheduleUpdate();
}

void PhotonLoadBalancingTest::onExit()
{
    CCLayer::onExit();
}

//------------------------------------------------------------------
//
// PhotonLoadBalancingTestScene
//
//------------------------------------------------------------------
void PhotonLoadBalancingTestScene::runThisTest()
{
    this->_photonLoadBalancingTest = new PhotonLoadBalancingTest();
    addChild(_photonLoadBalancingTest);

    CCDirector::sharedDirector()->replaceScene(this);
}
