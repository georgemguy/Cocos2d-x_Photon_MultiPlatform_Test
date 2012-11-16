#ifndef TestCpp_CCRoomTableCell_h
#define TestCpp_CCRoomTableCell_h

//#include "cocos2d.h"
#include "cocos-ext.h"
#include "GGUtil.h"

class CCRoomTableCell : public cocos2d::extension::CCTableViewCell
{
    CC_SYNTHESIZE_CHILD( cocos2d::CCLabelTTF*, _label, Label );
    
public:
    CCRoomTableCell();
    ~CCRoomTableCell();
    
    virtual bool init( const cocos2d::CCString& room );
    static CCRoomTableCell* create( const cocos2d::CCString& room );
};

#endif
