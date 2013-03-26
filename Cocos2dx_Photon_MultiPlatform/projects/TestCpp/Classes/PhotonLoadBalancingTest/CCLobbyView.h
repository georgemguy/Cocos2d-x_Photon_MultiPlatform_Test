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

#ifndef PhotonOnline_CCRoomMenu_h
#define PhotonOnline_CCRoomMenu_h

#include "cocos-ext.h"
#include "CCNetworkLogic.h"
#include "CCRoomTableCell.h"
//#include "CCChatRoom.h"

class CCLobbyViewDataSource;
class CCLobbyView : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDelegate, public cocos2d::extension::CCEditBoxDelegate
{
    CCLobbyViewDataSource* _lobbyViewDataSource;
    CC_SYNTHESIZE( unsigned int, _minRoomsInView, MinRoomsInView );
    CC_SYNTHESIZE( cocos2d::CCLabelTTF*, _console, Console );
    CC_SYNTHESIZE( cocos2d::extension::CCEditBox*, _editAddress, EditAddress );
    CC_SYNTHESIZE( cocos2d::CCLabelTTF*, _displayAddress, DisplayAddress );
    CC_SYNTHESIZE( cocos2d::CCMenuItemLabel*, _connect, Connect );
    CC_SYNTHESIZE( cocos2d::CCMenuItemLabel*, _joinRandomRoom, JoinRandomRoom );
    CC_SYNTHESIZE( cocos2d::CCMenuItemLabel*, _createRoom, CreateRoom );

    //CC_SYNTHESIZE_CHILD( cocos2d::CCLabelTTF*, _roomTableLabel, RoomTableLabel );
    //CC_SYNTHESIZE_CHILD( cocos2d::extension::CCTableView*, _roomTable, RoomTable );
    //CC_SYNTHESIZE_CHILD( CCChatRoom*, _chatRoom, ChatRoom );
    CC_SYNTHESIZE_RETAIN( cocos2d::extension::CCTableViewCell*, _lastCellTouched, LastCellTouched );
    CC_SYNTHESIZE( bool, _didCreateGame, DidCreateGame );
    
public:
    CCLobbyView();
    ~CCLobbyView();
    
    struct Child
    {
        enum _Tag
        {
            CCMenu_topMenu = 1,
            CCTableView_roomTable,
            CCMenu_bottomMenu,
            COUNT
        } Tag;
    };

    static CCLobbyView* create( const cocos2d::CCSize& size );
    virtual bool init( const cocos2d::CCSize& );
    virtual bool initRoomTable();
    virtual bool initBottomMenu();
    virtual bool initTopMenu();
    virtual void removeRoomTable();
    virtual void onEnter();
    virtual void onExit();
    virtual void update( float delta );
    
    virtual void joinGameButtonCallback( cocos2d::CCObject* sender );
    virtual void connectButtonCallback( cocos2d::CCObject* sender );
    virtual void createGameButtonCallback( cocos2d::CCObject* sender );
    virtual const cocos2d::CCPoint getCenter();
    virtual const cocos2d::CCPoint getTopHanger();
    virtual const cocos2d::CCPoint getBottomHanger();
    virtual void onJoinGame( bool isGameMaster );
    virtual void eventJoinGame( cocos2d::CCObject* sender );
    
    /**
     * Delegate to respond touch event
     *
     * @param table table contains the given cell
     * @param cell  cell that is touched
     */
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    virtual void joinRoom(cocos2d::CCObject* sender);
    
    //CC_IMPLEMENT_BACK_BUTTON_FOR_LAYER_PLEASE_ENABLE_KEYPAD;
    inline virtual void keyBackClicked()
    {
        using namespace cocos2d;
        CCDirector* director = CCDirector::sharedDirector();
        if( director )
        {
            director->popScene();
        }
    }
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

class CCLobbyViewDataSource : public cocos2d::extension::CCTableViewDataSource, public cocos2d::CCObject
{
    CCLobbyView* _lobbyView;
public:
    CCLobbyViewDataSource( CCLobbyView* lobbyView );

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
