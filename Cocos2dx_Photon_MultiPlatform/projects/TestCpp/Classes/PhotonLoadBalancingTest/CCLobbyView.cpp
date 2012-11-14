//
//  CCLobbyView.cpp
//  SumNationOnline
//
//  Created by George Guy on 11/9/12.
//
//

#include "CCLobbyView.h"
USING_NS_CC;
USING_NS_CC_EXT;

CCLobbyView::CCLobbyView() : CCLayer()
{
    this->_network = NULL;
    this->_connectButton = NULL;
    this->_console = NULL;
    this->_createRoomButton = NULL;
    this->_editAddress = NULL;
    this->_displayAddress = NULL;
}

CCLobbyView::~CCLobbyView()
{
    CC_SAFE_DELETE( this->_network );
    this->setConsole( NULL );
    this->setConnectButton( NULL );
    this->setCreateRoomButton( NULL );
    this->setEditAddress( NULL );
    this->setDisplayAddress( NULL );
}

bool CCLobbyView::init( CCNetworkLogic* network, const CCSize& size )
{
    if( CCLayer::init() )
    {
        const CCPoint& center = ccpMult( ccpFromSize( size ), 0.5f );
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
        sprite->setScaleX( 1.5f );
        CCControlButton* button = CCControlButton::create( label, sprite );
        button->addTargetWithActionForControlEvents( this, cccontrol_selector( CCLobbyView::connectButtonCallback ), CCControlEventTouchUpInside);
        button->setPreferredSize( rect.size );
        position = center;
        position.y -= 100;
        position.x -= 75;
        button->setPosition( position );
        this->setConnectButton( button );
        
        label = CCLabelTTF::create( "Create Room", "fonts/American Typewriter.ttf", fontSize );
        label->setColor( ccc3( 0, 0, 0 ) );
        sprite = CCScale9Sprite::create("Images/r1.png", rect, rect );
        sprite->setScaleX( 1.8f );
        button = CCControlButton::create( label, sprite );
        button->addTargetWithActionForControlEvents( this, cccontrol_selector( CCLobbyView::connectButtonCallback ), CCControlEventTouchUpInside);
        button->setPreferredSize( rect.size );
        position = center;
        position.y -= 100;
        position.x += 75;
        button->setPosition( position );
        this->setCreateRoomButton( button );
        
        CCSize tableSize = CCSizeMake( size.width * 0.9f, size.height * 0.9f );
        CCTableView* roomTable = CCTableView::create( this, tableSize );
        roomTable->setPosition( center );
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        //Common::JString jStr = _photonLib.getStateString();
        //const char* cStr = jStr.ANSIRepresentation();
        
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
    State state = network->getNetworkState();
    
    if( state == STATE_INITIALIZED )
    {
        network->connect();
    }
    else
    {
        network->disconnect();
    }
}

void CCLobbyView::update( float delta )
{
    CCLayer::update( delta );
    this->getNetwork()->run();
    
    const CCString& output = this->getNetwork()->getOutput();
    this->getConsole()->setString( output.getCString() );
    
    CCNetworkLogic* network = this->getNetwork();
    State state = network->getNetworkState();
    CCControlButton* connectButton = this->getConnectButton();
    
    if( connectButton )
    {
        if( state == STATE_INITIALIZED )
        {
            connectButton->setTitleForState( new CCString( "Connect" ), CCControlStateNormal );
        }
        else
        {
            connectButton->setTitleForState( new CCString( "Disconnect" ), CCControlStateNormal );
        }
    }
}

void CCLobbyView::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

void CCLobbyView::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
    
}

void CCLobbyView::scrollViewDidZoom(cocos2d::extension::CCScrollView* view)
{
    
}

CCSize CCLobbyView::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(60, 60);
}

CCTableViewCell* CCLobbyView::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("Images/Icon.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        cell->addChild(sprite);
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    
    return cell;
}

unsigned int CCLobbyView::numberOfCellsInTableView(CCTableView *table)
{
    return 20;
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
            this->getDisplayAddress()->setString( text.getCString() );
        }
    }
}