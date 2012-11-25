#ifndef TestCpp_CCRoomTableCell_h
#define TestCpp_CCRoomTableCell_h

#include "CCRoomInfo.h"
#include "cocos-ext.h"
#include "GGUtil.h"

class CCRoomTableCell : public cocos2d::extension::CCTableViewCell
{
    CC_SYNTHESIZE_CHILD( cocos2d::CCLabelTTF*, _label, Label );
    CCRoomInfo* _roomInfo;
    
public:
    CCRoomTableCell();
    ~CCRoomTableCell();
    
    virtual bool init( CCRoomInfo room );
    static CCRoomTableCell* create( CCRoomInfo room );
    
    virtual void setRoomInfo( CCRoomInfo room );
    virtual CCRoomInfo* getRoomInfo();
};

#endif
