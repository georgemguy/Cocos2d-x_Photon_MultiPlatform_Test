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

#include "CCChatTableCell.h"
#include "../testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCChatTableCell::CCChatTableCell() : CCTableViewCell()
{
}

CCChatTableCell::~CCChatTableCell()
{
}

bool CCChatTableCell::init( const char* message )
{
    CCAssert( message, "CCChatTableCell::init() -- message is NULL" );
    if( this->init( CCLabelTTF::create( message, f_AmericanTypewriter, 12 ) ) )
    {
        return true;
    }
    
    return false;
}

CCChatTableCell* CCChatTableCell::create( const char* message )
{
    CCChatTableCell* ret = new CCChatTableCell();
    
    if( ret && ret->init( message ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}

bool CCChatTableCell::init( cocos2d::CCLabelTTF* message )
{
    CCAssert( message, "CCChatTableCell::init() -- message is NULL" );
    this->addChild( message, 0, Child::CCLabelTTF_message );
    return true;
}

CCChatTableCell* CCChatTableCell::create( cocos2d::CCLabelTTF* message )
{
    CCChatTableCell* ret = new CCChatTableCell();
    
    if( ret && ret->init( message ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}