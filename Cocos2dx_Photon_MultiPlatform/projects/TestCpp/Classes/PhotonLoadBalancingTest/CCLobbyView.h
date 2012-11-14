//
//  CCRoomMenu.h
//  SumNationOnline
//
//  Created by George Guy on 11/9/12.
//
//

#ifndef SumNationOnline_CCRoomMenu_h
#define SumNationOnline_CCRoomMenu_h

#include "cocos-ext.h"
#include "CCNetworkLogic.h"
#include "GGUtil.h"

class CCLobbyView : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate, public cocos2d::extension::CCEditBoxDelegate
{
    CC_SYNTHESIZE_RETAIN( CCNetworkLogic*, _network, Network );
    CC_SYNTHESIZE_CHILD( cocos2d::CCLabelTTF*, _console, Console );
    CC_SYNTHESIZE_CHILD( cocos2d::extension::CCControlButton*, _connectButton, ConnectButton );
    CC_SYNTHESIZE_CHILD( cocos2d::extension::CCControlButton*, _createRoomButton, CreateRoomButton );
    CC_SYNTHESIZE_CHILD( cocos2d::extension::CCEditBox*, _editAddress, EditAddress );
    CC_SYNTHESIZE_CHILD( cocos2d::CCLabelTTF*, _displayAddress, DisplayAddress );
    
public:
    CCLobbyView();
    ~CCLobbyView();

    static CCLobbyView* create( CCNetworkLogic* network, const cocos2d::CCSize& size );
    virtual bool init( CCNetworkLogic* network, const cocos2d::CCSize& );
    virtual void onExit();
    virtual void update( float delta );
    
    virtual void connectButtonCallback( cocos2d::CCObject* sender );
    
    /**
     * Delegate to respond touch event
     *
     * @param table table contains the given cell
     * @param cell  cell that is touched
     */
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    
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
};

#endif
