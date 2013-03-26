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

#ifndef __TestCpp__CCCCUserForm__
#define __TestCpp__CCCCUserForm__

#include "cocos2d.h"
#include "cocos-ext.h"

class CCUserForm : public cocos2d::CCLayer, public cocos2d::extension::CCEditBoxDelegate
{
    CC_SYNTHESIZE( cocos2d::CCString, _email, Email );
    CC_SYNTHESIZE( cocos2d::CCString, _name, Name );
    CC_SYNTHESIZE( cocos2d::CCString, _password, Password );
public:
    CCUserForm();
    virtual ~CCUserForm();
    CREATE_FUNC(CCUserForm);
    
    virtual void keyBackClicked();
    virtual void forward();
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
private:
    cocos2d::extension::CCEditBox* m_pEditName;
    cocos2d::extension::CCEditBox* m_pEditPassword;
    cocos2d::extension::CCEditBox* m_pEditEmail;
};

#endif /* defined(__TestCpp__CCCCUserForm__) */
