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

#include "CCLobbyView.h"
#include "../MessageTest/CCConfirmMessage.h"
#include "PhotonKeys.h"
#include "../testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ExitGames;
using namespace LoadBalancing;
using namespace Common;

CCLobbyView::CCLobbyView() : CCLayer()
{
    this->_lobbyViewDataSource = NULL;
    this->_connect = NULL;
    this->_console = NULL;
    this->_createRoom = NULL;
    this->_editAddress = NULL;
    this->_displayAddress = NULL;
    this->_joinRandomRoom = NULL;
    //this->_roomTableLabel = NULL;
    //this->_chatRoom = NULL;
    this->_lastCellTouched = NULL;
}

CCLobbyView::~CCLobbyView()
{
    CC_SAFE_RELEASE_NULL( this->_lobbyViewDataSource );
    this->_connect = NULL;
    this->_console = NULL;
    this->_createRoom = NULL;
    this->_editAddress = NULL;
    this->_displayAddress = NULL;
    this->_joinRandomRoom = NULL;
    //this->_roomTableLabel = NULL;
    //this->_chatRoom = NULL;
    this->setLastCellTouched( NULL );
}

void CCLobbyView::removeRoomTable()
{
    CCNode* roomTable = NULL;
    while(( roomTable = this->getChildByTag( Child::CCTableView_roomTable ) ))
        this->removeChild( roomTable, true );
    
    CC_SAFE_RELEASE_NULL( this->_lobbyViewDataSource );
}

bool CCLobbyView::initRoomTable()
{
    const CCPoint& center = this->getCenter();
    this->removeRoomTable();
    this->_lobbyViewDataSource = new CCLobbyViewDataSource( this );
    
    if( this->_lobbyViewDataSource )
    {
        this->_lobbyViewDataSource->autorelease();
        CC_SAFE_RETAIN(this->_lobbyViewDataSource);
        CCSize tableSize = this->_lobbyViewDataSource->cellSizeForTable( NULL );
        tableSize.height *= 10.0f;
        CCTableView* table = CCTableView::create( this->_lobbyViewDataSource, tableSize );
        if( table )
        {
            table->setContentOffset( CCPointZero );
            table->setDirection(kCCScrollViewDirectionVertical);
            table->setPosition( ccp( center.x - ( tableSize.width * 0.5f ), center.y - ( tableSize.height * 0.5f ) ) );
            table->setDelegate( this );
            table->setVerticalFillOrder(kCCTableViewFillTopDown);
            table->setTouchEnabled( true );
            this->addChild( table, 0, Child::CCTableView_roomTable );
            table->reloadData();
            
            this->setMinRoomsInView( 10 );
            return true;
        }
    }
    return false;
}

const cocos2d::CCPoint CCLobbyView::getCenter()
{
    return ccpMult( ccpFromSize( this->getContentSize() ), 0.5f );
}

const cocos2d::CCPoint CCLobbyView::getTopHanger()
{
    const CCPoint& center = this->getCenter();
    return CCPointMake( center.x, center.y * 1.75f );
}

const cocos2d::CCPoint CCLobbyView::getBottomHanger()
{
    const CCPoint& center = this->getCenter();
    return CCPointMake( center.x, center.y * 0.25f );
}

bool CCLobbyView::initBottomMenu()
{
    CCDirector* director = CCDirector::sharedDirector();
    const CCSize winSize = director->getWinSize();
    const CCSize mySize = this->getContentSize();
    const CCPoint& center = ccpMult( ccpFromSize( mySize ), 0.5f );
    
    CCLabelTTF* connectLabel = CCLabelTTF::create( "Connect", f_AmericanTypewriter, 16 );
    CCMenuItemLabel* connectItem = CCMenuItemLabel::create( connectLabel, this, menu_selector( CCLobbyView::connectButtonCallback ) );
    
    CCLabelTTF* createLabel = CCLabelTTF::create( "Create Room", f_AmericanTypewriter, 16 );
    CCMenuItemLabel* createItem = CCMenuItemLabel::create( createLabel, this, menu_selector( CCLobbyView::createGameButtonCallback ) );
    
    CCLabelTTF* randomLabel = CCLabelTTF::create( "Random Room", f_AmericanTypewriter, 16 );
    CCMenuItemLabel* randomItem = CCMenuItemLabel::create( randomLabel, this, menu_selector( CCLobbyView::joinGameButtonCallback ) );
    
    CCMenu* bottomMenu = CCMenu::create( connectItem, createItem, randomItem, NULL );
    if( bottomMenu )
    {
        this->setConnect( connectItem );
        this->setJoinRandomRoom( randomItem );
        this->setCreateRoom( createItem );
        
        bottomMenu->alignItemsHorizontally();
        bottomMenu->setPosition( CCPointMake( center.x, center.y * 0.25f ) );
        this->addChild( bottomMenu, 0, Child::CCMenu_bottomMenu );
    }
    
    return bottomMenu;
}

bool CCLobbyView::initTopMenu()
{
    CCDirector* director = CCDirector::sharedDirector();
    const CCSize winSize = director->getWinSize();
    const CCSize mySize = this->getContentSize();
    const CCPoint center = ccpMult( ccpFromSize( mySize ), 0.5f );
    
    CCLabelTTF* consoleLabel = CCLabelTTF::create( "disconnected", f_AmericanTypewriter, 12, CCSizeMake( winSize.width, 24 ), kCCTextAlignmentCenter );
    consoleLabel->setColor( ccc3(255, 255, 255) );
    CCMenuItemLabel* consoleItem = CCMenuItemLabel::create( consoleLabel );
    
    CCLabelTTF* addressLabel = CCLabelTTF::create( "localhost:5055", f_AmericanTypewriter, 12 );
    CCMenuItemLabel* addressItem = CCMenuItemLabel::create( addressLabel );
    
    // bottom
    const CCSize editSize = CCSizeMake( winSize.width, 40 );
    CCMenuItem* editItem = CCMenuItem::create();
    editItem->setContentSize( editSize );
    
    CCMenu* topMenu = CCMenu::create( addressItem, consoleItem, editItem, NULL );
    if( topMenu )
    {        
        this->setDisplayAddress( addressLabel );
        this->setConsole( consoleLabel );

        topMenu->alignItemsVertically();
        topMenu->setPosition( CCPointMake( center.x, center.y * 1.75f ) );
        this->addChild( topMenu, 0, Child::CCMenu_topMenu );
        
        const CCPoint editItemPosition = editItem->getParent()->convertToWorldSpace( editItem->getPosition() );
        editItem->setContentSize( winSize );
        editItem->ignoreAnchorPointForPosition( false );
        editItem->setAnchorPoint( ccp( 0.5f, (winSize.height / (editItemPosition.y - winSize.height)) * 0.5f ) );
        
        CCScale9Sprite* editSprite = CCScale9Sprite::create("extensions/yellow_edit.png");
        CCEditBox* edit = CCEditBox::create( editSize, editSprite );
        edit->setPlaceHolder("ip:port");
        edit->setReturnType(kKeyboardReturnTypeDone);
        edit->setFontColor(ccGRAY);
        edit->setMaxLength( 20 );
        edit->setDelegate(this);
        edit->setTouchEnabled( true );
        edit->setPosition( editItemPosition );
        this->addChild( edit );
        this->setEditAddress( edit );
    }
    
    return topMenu;
}

bool CCLobbyView::init( const CCSize& mySize )
{
    if( CCLayer::init() )
    {
        this->setDidCreateGame( false );
        this->setContentSize( mySize );
        this->setKeypadEnabled( true );

        this->initBottomMenu();
        this->initRoomTable();
        this->initTopMenu();
        
        /*fontSize = 16;
        label = CCLabelTTF::create("Running games:", f_AmericanTypewriter, fontSize,
                                                 winSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        position = topHanger;
        position.y -= winSize.height * 0.15f;
        position.x -= winSize.width * 0.05f;
        label->setPosition( position );
        //label->setAnchorPoint( CCPointZero );
        this->setRoomTableLabel( label );*/
        
        /*fontSize = 12;
        label = CCLabelTTF::create("Name:", f_AmericanTypewriter, fontSize,
                                                 winSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        position = topHanger;
        position.y -= winSize.height * 0.20f;
        position.x -= winSize.width * 0.25f;
        label->setPosition( position );
        //label->setAnchorPoint( CCPointZero );
        this->setRoomTableLabel( label );*/

        /*fontSize = 12;
        CCLabelTTF* console = CCLabelTTF::create("disconnected", f_AmericanTypewriter, fontSize,
                                             winSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        console->setColor( ccc3(255, 255, 255) );
        console->setContentSize(winSize);
        position = topHanger;
        //position.y -= winSize.height * 0.00f;
        console->setPosition( position );
        this->setConsole( console );

        label = CCLabelTTF::create( "localhost:5055", f_AmericanTypewriter, fontSize );
        position = topHanger;
        position.y += winSize.height * 0.1f;
        label->setPosition( position );
        this->setDisplayAddress( label );
        
        // top
        fontSize = 24;
        length = 19;
        CCScale9Sprite* editSprite = CCScale9Sprite::create( "ZoomButton.png" );
        CCEditBox* edit = CCEditBox::create( CCSizeMake( length * fontSize * 0.7f, fontSize * 1.7f ), editSprite );
        edit->setFontColor(ccBLACK);
        edit->setPlaceHolder("ip:port");
        edit->setMaxLength( 20 );
        edit->setReturnType(kKeyboardReturnTypeDone);
        edit->setDelegate(this);
        position = topHanger;
        position.y -= winSize.height * 0.075f;
        edit->setPosition( position );
        this->setEditAddress( edit );*/
        
        this->scheduleUpdate();
        //this->runAction(CCRotateBy::create(0.0f, -M_1_PI / 2));

        return true;
    }
    
    return false;
}

CCLobbyView* CCLobbyView::create( const CCSize& size )
{
    CCLobbyView* ret = new CCLobbyView();
    
    if( ret && ret->init( size ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}

void CCLobbyView::onEnter()
{
    CCLayer::onEnter();
    this->setDidCreateGame( false );

    CCNetworkLogic* network = CCNetworkLogic::sharedCCNetworkLogic();
    CCNotificationCenter* publisher = CCNotificationCenter::sharedNotificationCenter();
    publisher->addObserver( this, callfuncO_selector( CCLobbyView::eventJoinGame ), PhotonNoteKey::getString(PhotonNoteKey::JoinRoomReturn), network );
}

void CCLobbyView::onExit()
{
    CCLayer::onExit();
    CCNotificationCenter* publisher = CCNotificationCenter::sharedNotificationCenter();
    publisher->removeObserver( this, PhotonNoteKey::getString(PhotonNoteKey::JoinRoomReturn) );
    this->setDidCreateGame(false);
}

void CCLobbyView::onJoinGame( bool isGameMaster )
{
    this->setDidCreateGame( isGameMaster );
    CCDirector* director = CCDirector::sharedDirector();
    CCScene* scene = CCScene::create();
    director->pushScene( scene );
}

void CCLobbyView::connectButtonCallback( CCObject* sender )
{
    CCNetworkLogic* network = CCNetworkLogic::sharedCCNetworkLogic();
    State state = network->getState();
    
    if( state == STATE_INITIALIZED )
    {
        network->setLastInput( INPUT_CONNECT );
    }
    else
    {
        network->setLastInput( INPUT_EXIT );
    }
}

void CCLobbyView::joinGameButtonCallback( CCObject* sender )
{;
    CCNetworkLogic* network = CCNetworkLogic::sharedCCNetworkLogic();
    State state = network->getState();
    if ( state == STATE_JOINED )
    {
        network->setLastInput( INPUT_LEAVE_GAME );
    }
    else if( state == STATE_INITIALIZED )
    {
        this->keyBackClicked();
    }
    else
    {
        network->setLastInput( INPUT_JOIN_RANDOM_GAME );
    }
}

void CCLobbyView::createGameButtonCallback( CCObject* sender )
{
    this->onJoinGame( true );
}

void CCLobbyView::update( float delta )
{
    CCLayer::update( delta );
    
    CCNetworkLogic* network = CCNetworkLogic::sharedCCNetworkLogic();
    
    const CCString& output = network->getOutput();
    this->getConsole()->setString( output.getCString() );
    
    State state = network->getState();
    CCMenuItemLabel* connectButton = this->getConnect();
    CCMenuItemLabel* gameButton = this->getJoinRandomRoom();
    CCMenuItemLabel* createGameButton = this->getCreateRoom();
    
    CCTableView* roomTable = (CCTableView*) this->getChildByTag( Child::CCTableView_roomTable );
    
    if( connectButton )
    {
        if( state == STATE_INITIALIZED )
        {
            this->removeRoomTable();
            connectButton->setString( "Connect" );
            gameButton->setVisible(true);
            gameButton->setString( "Exit Lobby" );
            createGameButton->setVisible( false );
        }
        else
        {
            if( !roomTable )
            {
                this->initRoomTable();
            }
            connectButton->setString( "Disconnect" );
            gameButton->setVisible(true);
            if( state == STATE_JOINED )
            {
                gameButton->setString( "Leave Room" );
                createGameButton->setVisible(false);
            }
            else
            {
                gameButton->setString( "Random Room" );
                createGameButton->setVisible(true);
            }
        }
    }

    roomTable = (CCTableView*) this->getChildByTag( Child::CCTableView_roomTable );
    if( roomTable )
    {
        roomTable->reloadData();
    }
}

void CCLobbyView::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    using namespace ExitGames::LoadBalancing;
    CCLog("CCLobbyView::tableCellTouched() -- cell touched at index: %i", cell->getIdx());
    
    this->setLastCellTouched( cell );
    
    CCRoomTableCell* roomCell = (CCRoomTableCell*) cell;
    
    if( roomCell->getHasRoom() )
    {
        CCSize size = CCSize();
        size.height = 100;
        size.width = 200;
        CCSprite* background = CCSprite::create( "Default.png" );
        CCLabelTTF* label = CCLabelTTF::create( "Join this room?", f_AmericanTypewriter, 24 );
        CCControlButton* cancel = CCControlButton::create( "Cancel", f_AmericanTypewriter, 16 );
        CCControlButton* okay = CCControlButton::create( "Okay", f_AmericanTypewriter, 16 );
        
        CCFadeIn* in = CCFadeIn::create(1.0f);
        CCFadeOut* out = CCFadeOut::create(1.0f);
        
        CCConfirmMessage* message = CCConfirmMessage::create( background, label, cancel, okay, in, out );
        this->addChild(message);
    }
}

void CCLobbyView::joinRoom(CCObject* sender)
{
    CCNetworkLogic* network = CCNetworkLogic::sharedCCNetworkLogic();
    CCRoomTableCell* cell = (CCRoomTableCell*) this->getLastCellTouched();
    Room* room = cell->getRoom();
    
    if( room && room->getMaxPlayers() > room->getPlayerCount() )
    {
        network->opJoinRoom( room->getName() );
    }
}

void CCLobbyView::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
    //this->getRoomTable()->scrollViewDidScroll( this->getRoomTable() );
}

void CCLobbyView::scrollViewDidZoom(cocos2d::extension::CCScrollView* view)
{
    
}

CCLobbyViewDataSource::CCLobbyViewDataSource( CCLobbyView* lobbyView )
{
    _lobbyView = lobbyView;
}

CCSize CCLobbyViewDataSource::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake( _lobbyView->getContentSize().width * 0.9f, 16);
}

CCTableViewCell* CCLobbyViewDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCNetworkLogic* network = CCNetworkLogic::sharedCCNetworkLogic();
    bool realRoom = idx < network->getRoomList().getSize();
    CCRoomTableCell *cell = (CCRoomTableCell*) table->dequeueCell();
    const JVector<Room>& roomList = network->getRoomList();
    
    if (!cell)
    {
        if( realRoom )
        {
            Room& room = roomList.getElementAt( idx );
            
            cell = CCRoomTableCell::create( room );
        }
        else
        {
            cell = CCRoomTableCell::create();
        }
    }
    else
    {
        if( realRoom )
        {
            Room& room = roomList.getElementAt( idx );
            cell->init( room );
        }
        else
        {
            cell->init();
        }
    }
    
    return cell;
}

unsigned int CCLobbyViewDataSource::numberOfCellsInTableView(CCTableView *table)
{
    CCNetworkLogic* network = CCNetworkLogic::sharedCCNetworkLogic();
    State state = network->getState();
    
    if( state == STATE_DISCONNECTED )
    {
        return 0;
    }
    else
    {
        return MAX( _lobbyView->getMinRoomsInView(), network->getRoomList().getSize() );
    }
}

void CCLobbyView::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidBegin !", editBox);
}

void CCLobbyView::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidEnd !", editBox);
}

void CCLobbyView::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void CCLobbyView::editBoxReturn(CCEditBox* editBox)
{
    CCLog("editBox %p was returned !");
    CCNetworkLogic* network = CCNetworkLogic::sharedCCNetworkLogic();
    
    if( this->getEditAddress() == editBox )
    {
        CCString text = editBox->getText();
        int minIPAddressLength = 12;
        if( text.length() >= minIPAddressLength )
        {
            const char* address = text.getCString();
            this->getDisplayAddress()->setString( address );
            network->setServerAddress( address );
        }
    }
}

void CCLobbyView::eventJoinGame( cocos2d::CCObject* sender )
{
    this->onJoinGame( false );
}
