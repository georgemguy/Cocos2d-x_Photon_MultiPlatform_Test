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

#ifndef Abstroku_CCConfirmMessage_h
#define Abstroku_CCConfirmMessage_h

#include "cocos2d.h"
#include "CCControlExtensions.h"

class CCConfirmMessage : public cocos2d::CCLayer
{
public:
    CC_SYNTHESIZE_RETAIN( cocos2d::CCFiniteTimeAction*, _inTransition, InTransition );
    CC_SYNTHESIZE_RETAIN( cocos2d::CCFiniteTimeAction*, _outTransition, OutTransition );
    
    typedef cocos2d::CCLayer super;
    
    struct Child
    {
        enum _Tag
        {
            CCNode_label = 1,
            CCNode_background,
            CCControl_cancel,
            CCControl_okay,
            COUNT
        } Tag;
        
        struct Z
        {
            enum _ZOrder
            {
                background = -1024,
                label = -512,
                options = 0
            } ZOrder;
        };
    };
    
    CCConfirmMessage();
    ~CCConfirmMessage();
    
    virtual bool init(
                      cocos2d::CCNode* background,
                      cocos2d::CCNode* label,
                      cocos2d::extension::CCControl* cancel,
                      cocos2d::extension::CCControl* okay,
                      cocos2d::CCFiniteTimeAction* inTransition,
                      cocos2d::CCFiniteTimeAction* outTransition );

    static CCConfirmMessage* create(
                                    cocos2d::CCNode* background,
                                    cocos2d::CCNode* label,
                                    cocos2d::extension::CCControl* cancel,
                                    cocos2d::extension::CCControl* okay,
                                    cocos2d::CCFiniteTimeAction* inTransition,
                                    cocos2d::CCFiniteTimeAction* outTransition );
    
    virtual void onEnter();
    virtual void transitionOut();
};

#endif
