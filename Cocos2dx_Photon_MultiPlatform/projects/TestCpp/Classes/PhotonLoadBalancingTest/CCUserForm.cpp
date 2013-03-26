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

#include "CCUserForm.h"
#include "CCLobbyView.h"
#include "../MessageTest/CCControlAlertMessage.h"

USING_NS_CC;
USING_NS_CC_EXT;


CCUserForm::CCUserForm()
{
    CCPoint visibleOrigin = CCEGLView::sharedOpenGLView()->getVisibleOrigin();
    CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
    
    CCSprite* pBg = CCSprite::create("HelloWorld.png");
    pBg->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
    addChild(pBg);
    
    // Back Menu
    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(CCUserForm::keyBackClicked));
    itemBack->setPosition(ccp(visibleOrigin.x + 50, visibleOrigin.y+25));
    CCMenu *menuBack = CCMenu::create(itemBack, NULL);
    addChild(menuBack);
    
    CCMenuItemFont *itemOkay = CCMenuItemFont::create("Okay", this, menu_selector(CCUserForm::forward));
    itemOkay->setPosition(ccp(visibleOrigin.x + visibleSize.width - 50, visibleOrigin.y+25));
    CCMenu *menuOkay = CCMenu::create(itemOkay, NULL);
    menuOkay->setPosition(CCPointZero);
    addChild(menuOkay);
    
    CCSize editBoxSize = CCSizeMake(visibleSize.width - 100, 60);

    // top
    m_pEditName = CCEditBox::create(editBoxSize, CCScale9Sprite::create("Images/green_edit.png"));
    m_pEditName->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4));
    m_pEditName->setFontColor(ccRED);
    m_pEditName->setPlaceHolder("Name:");
    m_pEditName->setMaxLength(8);
    m_pEditName->setReturnType(kKeyboardReturnTypeDone);
    m_pEditName->setDelegate(this);
    addChild(m_pEditName);
    
    // middle
    m_pEditPassword = CCEditBox::create(editBoxSize, CCScale9Sprite::create("Images/orange_edit.png"));
    m_pEditPassword->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
    m_pEditPassword->setFontColor(ccGREEN);
    m_pEditPassword->setPlaceHolder("Password:");
    m_pEditPassword->setMaxLength(6);
    m_pEditPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditPassword->setInputMode(kEditBoxInputModeSingleLine);
    m_pEditPassword->setDelegate(this);
    addChild(m_pEditPassword);
    
    // bottom
    m_pEditEmail = CCEditBox::create(CCSizeMake(editBoxSize.width, editBoxSize.height), CCScale9Sprite::create("Images/yellow_edit.png"));
    m_pEditEmail->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4));
    m_pEditEmail->setPlaceHolder("Email:");
    m_pEditEmail->setInputMode(kEditBoxInputModeEmailAddr);
    m_pEditEmail->setDelegate(this);
    addChild(m_pEditEmail);
}

CCUserForm::~CCUserForm()
{
    
}

void CCUserForm::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidBegin !", editBox);
}

void CCUserForm::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidEnd !", editBox);
}

void CCUserForm::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void CCUserForm::editBoxReturn(CCEditBox* editBox)
{
    CCLog("editBox %p was returned !");
    
    if (m_pEditName == editBox)
    {
        this->setName( editBox->getText() );
    }
    else if (m_pEditPassword == editBox)
    {
        this->setPassword( editBox->getText() );
    }
    else if (m_pEditEmail == editBox)
    {
        this->setEmail( editBox->getText() );
    }
}

void CCUserForm::keyBackClicked()
{
    using namespace cocos2d;
    CCDirector* director = CCDirector::sharedDirector();
    if( director )
    {
        director->popScene();
    }
}

void CCUserForm::forward()
{
    CCString email = this->getEmail();
    CCString name = this->getName();
    CCString password = this->getPassword();
    if( password.length() && name.length() )
    {
        CCUserDefault::sharedUserDefault()->setStringForKey( "Password", password.getCString() );
        CCUserDefault::sharedUserDefault()->setStringForKey( "Name", name.getCString() );
        
        if( email.length() )
        {
            //AnalyticX::flurrySetGender( gender.getCString() );
            CCUserDefault::sharedUserDefault()->setStringForKey( "Email", email.getCString() );
        }
        
        CCUserDefault::sharedUserDefault()->flush();
        CCDirector* director = CCDirector::sharedDirector();
        CCSize winSize = director->getWinSize();
        CCPoint winSizePoint = ccpFromSize( winSize );
        CCPoint center = ccpMult( winSizePoint, 0.5f );
        
        CCScene* gameScene = CCScene::create();
        gameScene->addChild( CCLobbyView::create( winSize ) );
        director->popScene();
        director->pushScene( gameScene );
        
    }
    else
    {
        this->addChild( CCControlAlertMessage::create( "Please enter your name and age." ) );
    }
}