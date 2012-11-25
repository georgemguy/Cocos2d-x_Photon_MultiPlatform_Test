//
//  CCChatTableCell.h
//  TestCpp
//
//  Created by George Guy on 11/20/12.
//
//

#ifndef __TestCpp__CCChatTableCell__
#define __TestCpp__CCChatTableCell__

#include "cocos-ext.h"
#include "GGUtil.h"

class CCChatTableCell : public cocos2d::extension::CCTableViewCell
{
public:
    class Child
    {
    public:
        enum _Tag
        {
            CCLabelTTF_message,
            MAX_TAG
        } Tag;
    };
    
    CCChatTableCell();
    virtual ~CCChatTableCell();
    virtual bool init( const char* message );
    static CCChatTableCell* create( const char* message );
    
    virtual bool init( cocos2d::CCLabelTTF* message );
    static CCChatTableCell* create( cocos2d::CCLabelTTF* message );
};

#endif /* defined(__TestCpp__CCChatTableCell__) */
