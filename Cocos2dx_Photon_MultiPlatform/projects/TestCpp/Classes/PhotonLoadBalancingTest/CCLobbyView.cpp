//
//  CCLobbyView.cpp
//  SumNationOnline
//
//  Created by George Guy on 11/9/12.
//
//

#include "CCLobbyView.h"
#include "CCControlConfirmMessage.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCLobbyView::CCLobbyView() : CCLayer()
{
    this->_lobbyViewDataSource = NULL;
    this->_network = NULL;
    this->_connectButton = NULL;
    this->_console = NULL;
    this->_createGameButton = NULL;
    this->_editAddress = NULL;
    this->_displayAddress = NULL;
    this->_roomTable = NULL;
    this->_randomGameButton = NULL;
    this->_roomTableLabel = NULL;
    //this->_chatRoom = NULL;
    this->_lastCellTouched = NULL;
}

CCLobbyView::~CCLobbyView()
{
    CC_SAFE_DELETE( this->_network );
    CC_SAFE_DELETE( this->_lobbyViewDataSource );
    this->setConsole( NULL );
    this->setConnectButton( NULL );
    this->setCreateGameButton( NULL );
    this->setEditAddress( NULL );
    this->setDisplayAddress( NULL );
    this->setRoomTable( NULL );
    this->setRandomGameButton( NULL );
    this->setRoomTableLabel( NULL );
    //this->setChatRoom( NULL );
    this->setLastCellTouched( NULL );
}

bool CCLobbyView::init( CCNetworkLogic* network, const CCSize& mySize )
{
    if( CCLayer::init() )
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        const CCPoint& center = ccpMult( ccpFromSize( mySize ), 0.5f );
        CCPoint position = CCPointZero;
        CCSize size = CCSizeZero;
        int length = 0;
        int fontSize = 0;
        
        this->setNetwork( network );
        
        CCSprite* s = CCSprite::create("Images/r1.png");
        s->retain();
        CCRect rect = CCRectZero;
        rect.size = s->getContentSize();
        s->release();
        
        fontSize = 12;
        CCLabelTTF* label = CCLabelTTF::create( "Connect", "fonts/American Typewriter.ttf", fontSize );
        label->setColor( ccc3( 0, 0, 0 ) );
        CCScale9Sprite* sprite = CCScale9Sprite::create("Images/r1.png", rect, rect );
        sprite->setScaleX( 1.4f );
        sprite->setScaleY( 0.8f );
        CCControlButton* button = CCControlButton::create( label, sprite );
        button->addTargetWithActionForControlEvents( this, cccontrol_selector( CCLobbyView::connectButtonCallback ), CCControlEventTouchUpInside);
        button->setPreferredSize( rect.size );
        position = center;
        position.y -= 136;
        position.x -= 100;
        button->setPosition( position );
        this->setConnectButton( button );
        
        label = CCLabelTTF::create( "Create Room", "fonts/American Typewriter.ttf", fontSize );
        label->setColor( ccc3( 0, 0, 0 ) );
        sprite = CCScale9Sprite::create("Images/r1.png", rect, rect );
        sprite->setScaleX( 1.4f );
        sprite->setScaleY( 0.8f );
        button = CCControlButton::create( label, sprite );
        button->addTargetWithActionForControlEvents( this, cccontrol_selector( CCLobbyView::createGameButtonCallback ), CCControlEventTouchUpInside);
        button->setPreferredSize( rect.size );
        position = center;
        position.y -= 136;
        //position.x += 0;
        button->setPosition( position );
        this->setCreateGameButton( button );
        
        label = CCLabelTTF::create( "Random Room", "fonts/American Typewriter.ttf", fontSize );
        label->setColor( ccc3( 0, 0, 0 ) );
        sprite = CCScale9Sprite::create("Images/r1.png", rect, rect );
        sprite->setScaleX( 1.6f );
        sprite->setScaleY( 0.8f );
        button = CCControlButton::create( label, sprite );
        button->addTargetWithActionForControlEvents( this, cccontrol_selector( CCLobbyView::joinGameButtonCallback ), CCControlEventTouchUpInside);
        button->setPreferredSize( rect.size );
        position = center;
        position.y -= 136;
        position.x += 100;
        button->setPosition( position );
        this->setRandomGameButton( button );
        
        this->_lobbyViewDataSource = new CCLobbyViewDataSource( this );

        fontSize = 16;
        length = mySize.width;
        size = this->_lobbyViewDataSource->cellSizeForTable( NULL );
        size.height *= 3;
        CCTableView* table = CCTableView::create( this->_lobbyViewDataSource, size );
        table->setContentOffset( CCPointZero );
        table->setDirection(kCCScrollViewDirectionVertical);
        position = center;
        position.x -= size.width * 0.5f;
        position.y -= fontSize + ( size.height * 0.17f );
        table->setPosition( position );
        table->setDelegate( this );
        table->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->setRoomTable( table );
        table->reloadData();
        
        fontSize = 16;
        label = CCLabelTTF::create("Running games:", "fonts/American Typewriter.ttf", fontSize,
                                                 winSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        position = center;
        position.x -= size.width * 0.4f;
        position.y += size.height - ( fontSize * 0.5f );
        label->setPosition( position );
        //label->setAnchorPoint( CCPointZero );
        this->setRoomTableLabel( label );
        
        fontSize = 16;
        CCLabelTTF* console = CCLabelTTF::create("disconnected", "fonts/American Typewriter.ttf", fontSize,
                                             winSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        
            
        console->setColor( ccc3(255, 255, 255) );
        console->setContentSize(winSize);
        position = center;
        position.y += 100;
        console->setPosition( position );
        this->setConsole( console );
        
        label = CCLabelTTF::create( "localhost:5055", "fonts/American Typewriter.ttf", fontSize );
        position.y += fontSize;
        label->setPosition( position );
        this->setDisplayAddress( label );
        
        // top
        fontSize = 24;
        length = 19;
        size = CCSize( length * fontSize * 0.7f, fontSize * 1.7f );
        CCEditBox* edit = CCEditBox::create( size, CCScale9Sprite::create( "extensions/green_edit.png" ) );
        edit->setPosition( center );
        edit->setFontColor(ccBLACK);
        edit->setPlaceHolder("ip:port");
        edit->setMaxLength( 19 );
        edit->setReturnType(kKeyboardReturnTypeDone);
        edit->setDelegate(this);
        position.y -= fontSize * 2;
        edit->setPosition( position );
        this->setEditAddress( edit );
        
        //CCChatRoom* chatroom = CCChatRoom::create(this->getNetwork());
        //this->setChatRoom( chatroom );
        
        this->scheduleUpdate();

        return true;
    }
    
    return false;
}

CCLobbyView* CCLobbyView::create( CCNetworkLogic* network, const CCSize& size )
{
    CCLobbyView* ret = new CCLobbyView();
    
    if( ret && ret->init( network, size ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}

void CCLobbyView::onExit()
{
    CCLayer::onExit();
    this->getNetwork()->disconnect();
}

void CCLobbyView::connectButtonCallback( CCObject* sender )
{
    CCNetworkLogic* network = this->getNetwork();
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
    CCNetworkLogic* network = this->getNetwork();
    State state = network->getState();
    if ( state == STATE_JOINED )
    {
        network->setLastInput( INPUT_LEAVE_GAME );
    }
    else
    {
        network->setLastInput( INPUT_JOIN_RANDOM_GAME );
    }
    
}

void CCLobbyView::createGameButtonCallback( CCObject* sender )
{
    CCNetworkLogic* network = this->getNetwork();
    network->setLastInput( INPUT_CREATE_GAME );
}

void CCLobbyView::update( float delta )
{
    CCLayer::update( delta );
    this->getNetwork()->run();
    
    const CCString& output = this->getNetwork()->getOutput();
    this->getConsole()->setString( output.getCString() );
    
    CCNetworkLogic* network = this->getNetwork();
    State state = network->getState();
    CCControlButton* connectButton = this->getConnectButton();
    CCControlButton* gameButton = this->getRandomGameButton();
    CCControlButton* createGameButton = this->getCreateGameButton();
    
    if( connectButton )
    {
        if( state == STATE_INITIALIZED )
        {
            connectButton->setTitleForState( new CCString( "Connect" ), CCControlStateNormal );
            createGameButton->setVisible(false);
            gameButton->setVisible(false);
        }
        else
        {
            connectButton->setTitleForState( new CCString( "Disconnect" ), CCControlStateNormal );
            gameButton->setVisible(true);
            if( state == STATE_JOINED )
            {
                gameButton->setTitleForState( new CCString( "Leave Room" ), CCControlStateNormal );
                createGameButton->setVisible(false);
            }
            else
            {
                gameButton->setTitleForState( new CCString( "Random Room" ), CCControlStateNormal );
                createGameButton->setVisible(true);
            }
        }
    }
    
    /*
    if( state == STATE_JOINED )
    {
        CCChatRoom* chatRoom = this->getChatRoom();
        
        if( ! chatRoom )
        {
            chatRoom = CCChatRoom::create( network );
            this->setChatRoom( chatRoom );
        }
    }
    else
    {
        this->setChatRoom( NULL );
    }
     */
    
    this->getRoomTable()->reloadData();
}

void CCLobbyView::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
    
    this->setLastCellTouched( cell );
    
    CCSize size = CCSize();
    size.height = 100;
    size.width = 200;
    CCControlConfirmMessage* alert = CCControlConfirmMessage::create("Join this room?", "fonts/American Typewritter.ttf", "Images/btn-play-normal.png", "Images/background.png", size, this, cccontrol_selector(CCLobbyView::joinRoom));    
    this->addChild(alert);
}

void CCLobbyView::joinRoom(CCObject* sender)
{
    CCRoomInfo* roomInfo;
    CCRoomTableCell* cell = (CCRoomTableCell*) this->getLastCellTouched();

    roomInfo = cell->getRoomInfo();
    this->getNetwork()->opJoinRoom( roomInfo->getName() );
    return;
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
    CCRoomTableCell *cell = (CCRoomTableCell*) table->dequeueCell();
    CCRoomInfo roomInfo = _lobbyView->getNetwork()->getRoomInfoAtIndex( idx );
    
    if (!cell)
    {
        cell = CCRoomTableCell::create( roomInfo );
    }
    else
    {
        cell->setRoomInfo( roomInfo );
    }
    
    return cell;
}

unsigned int CCLobbyViewDataSource::numberOfCellsInTableView(CCTableView *table)
{
    return _lobbyView->getNetwork()->getRoomList().getSize();
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
    
    if( this->getEditAddress() == editBox )
    {
        CCString text = editBox->getText();
        int minIPAddressLength = 12;
        if( text.length() >= minIPAddressLength )
        {
            const char* address = text.getCString();
            this->getDisplayAddress()->setString( address );
            this->getNetwork()->setServerAddress( address );
        }
    }
}