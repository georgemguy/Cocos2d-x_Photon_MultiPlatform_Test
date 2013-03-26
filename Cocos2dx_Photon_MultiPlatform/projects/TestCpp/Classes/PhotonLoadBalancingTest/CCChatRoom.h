//
//  CCChatRoom.h
//  TestCpp
//
//  Created by George Guy on 11/17/12.
//
//

#ifndef TestCpp_CCChatRoom_h
#define TestCpp_CCChatRoom_h

#include "cocos-ext.h"
#include "CCNetworkLogic.h"

class CCChatRoomDataSource;
class CCChatRoom : public cocos2d::CCLayer, public cocos2d::extension::CCEditBoxDelegate, public cocos2d::extension::CCTableViewDelegate
{
    CC_SYNTHESIZE_RETAIN( CCNetworkLogic*, _network, Network );
    /*CC_SYNTHESIZE_CHILD( cocos2d::CCLabelTTF* , _lastSentLabel, LastSentLabel );
    CC_SYNTHESIZE_CHILD( cocos2d::CCLabelTTF* , _lastReceivedLabel, LastReceivedLabel );
    CC_SYNTHESIZE_CHILD( cocos2d::extension::CCEditBox* , _editBox, EditBox );
    CC_SYNTHESIZE_CHILD( cocos2d::extension::CCControlButton*, _exitButton, ExitButton );
    CC_SYNTHESIZE_CHILD( cocos2d::extension::CCTableView*, _chatTable, ChatTable );*/
    CC_SYNTHESIZE_READONLY( CCChatRoomDataSource*, _chatRoomDataSource, ChatRoomDataSource );
    
public:
    CCChatRoom();
    virtual ~CCChatRoom();
    
    virtual bool init( CCNetworkLogic* network );
    static CCChatRoom* create( CCNetworkLogic* network );
    
    virtual void onEnter();
    virtual void onExit();
    
    /**
     * This method is called when an edit box gains focus after keyboard is shown.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    
    
    /**
     * This method is called when an edit box loses focus after keyboard is hidden.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    
    /**
     * This method is called when the edit box text was changed.
     * @param editBox The edit box object that generated the event.
     * @param text The new text.
     */
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    
    /**
     * This method is called when the return button was pressed or the outside area of keyboard was touched.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);

    /**
     * Delegate to respond touch event
     *
     * @param table table contains the given cell
     * @param cell  cell that is touched
     */
    virtual void tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView* view);
    virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView* view);
};

class CCChatRoomDataSource : public cocos2d::extension::CCTableViewDataSource, public cocos2d::CCObject
{
    CC_SYNTHESIZE_RETAIN( cocos2d::CCArray* , _chatMessages, ChatMessages );
    CC_SYNTHESIZE( unsigned int, _maxMessages, MaxMessages );

protected:
    CCChatRoom* _chatView;
    
public:
    CCChatRoomDataSource();
    virtual ~CCChatRoomDataSource();
    
    virtual cocos2d::CCArray* initMessages();
    virtual bool init( CCChatRoom* chatView  );
    static CCChatRoomDataSource* create( CCChatRoom* chatView );
    
    virtual int submitMessage( const char* str );
    
    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
};
#endif
