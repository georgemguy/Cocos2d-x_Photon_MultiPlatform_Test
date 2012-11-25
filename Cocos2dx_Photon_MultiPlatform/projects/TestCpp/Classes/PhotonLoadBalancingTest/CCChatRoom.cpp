//
//  CCChatRoom.cpp
//  TestCpp
//
//  Created by George Guy on 11/17/12.
//
//

#include "CCChatRoom.h"
#include "CCChatTableCell.h"
#include "CCRecursiveAction.h"
#include "CCEnable.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCChatRoom::CCChatRoom() : CCLayer()
{
    this->_network = NULL;
    this->_editBox = NULL;
    this->_lastSentLabel = NULL;
    this->_lastReceivedLabel = NULL;
    this->_chatRoomDataSource = NULL;
    this->_chatTable = NULL;
}

CCChatRoom::~CCChatRoom()
{
    this->setNetwork( NULL );
    this->setEditBox( NULL );
    this->setLastSentLabel( NULL );
    this->setLastReceivedLabel( NULL );
    this->setChatTable( NULL );
    CC_SAFE_RELEASE_NULL( this->_chatRoomDataSource );
}

bool CCChatRoom::init( CCNetworkLogic* network )
{
    if( CCLayer::init() )
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        const CCPoint& center = ccpMult( ccpFromSize( winSize ), 0.5f );
        CCPoint position = center;
        
        int fontSize = 24;
        int length = 19;
        CCSize size = CCSize( length * fontSize * 0.7f, fontSize * 1.7f );
        CCEditBox* edit = CCEditBox::create( size, CCScale9Sprite::create( "extensions/green_edit.png" ) );
        edit->setPosition( center );
        edit->setFontColor(ccBLACK);
        edit->setPlaceHolder("chat");
        edit->setMaxLength( 19 );
        edit->setReturnType(kKeyboardReturnTypeDone);
        edit->setDelegate(this);
        position.y -= fontSize * 4;
        edit->setPosition( position );
        this->setEditBox( edit );
        
        CCSprite* s = CCSprite::create("Images/r1.png");
        s->retain();
        CCRect rect = CCRectZero;
        rect.size = s->getContentSize();
        s->release();
        
        fontSize = 12;
        CCLabelTTF* label = CCLabelTTF::create( "                                          ", "fonts/American Typewriter.ttf", fontSize );
        position.y -= fontSize * 4;
        label->setColor( ccc3( 0, 0, 0 ) );
        label->setPosition( position );
        this->setLastSentLabel( label );

        label = CCLabelTTF::create( "                                          ", "fonts/American Typewriter.ttf", fontSize );
        label->setColor( ccc3( 0, 0, 0 ) );
        position.y -= fontSize * 1;
        label->setPosition( position );
        this->setLastReceivedLabel( label );
        
        this->_chatRoomDataSource = CCChatRoomDataSource::create( this );
        this->_chatRoomDataSource->retain();

        size = this->_chatRoomDataSource->cellSizeForTable( NULL );
        size.height *= 3;
        CCTableView* table = CCTableView::create( this->_chatRoomDataSource, size );
        table->setContentOffset( CCPointZero );
        table->setDirection(kCCScrollViewDirectionVertical);
        position = center;
        position.x -= size.width * 0.5f;
        position.y -= size.height * 0.17f;
        table->setPosition( position );
        table->setDelegate( this );
        table->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->setChatTable( table );
        table->reloadData();

        this->setNetwork( network );
        
        return true;
    }
    
    return false;
}

CCChatRoom* CCChatRoom::create(CCNetworkLogic *network)
{
    CCChatRoom* ret = new CCChatRoom();
    
    if( ret && ret->init( network ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}

void CCChatRoom::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidBegin !", editBox);
}

void CCChatRoom::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("editBox %p DidEnd !", editBox);
}

void CCChatRoom::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void CCChatRoom::editBoxReturn(CCEditBox* editBox)
{
    CCLog("editBox %p was returned !");
    if( this->getEditBox() == editBox )
    {
        CCString text = editBox->getText();
        int minIPAddressLength = 12;
        if( text.length() >= minIPAddressLength )
        {
            const char* address = text.getCString();
            this->getLastSentLabel()->setString( address );
            ExitGames::Common::Hashtable ev;
            ev.put( (nByte) CHATBYTE_STRING, ExitGames::Common::JString(address));
            this->getNetwork()->opRaiseEvent( (nByte) true, ev, (nByte) EVENT_CHAT);
        }
    }
}

CCChatRoomDataSource::CCChatRoomDataSource() : CCObject()
{
    this->_chatMessages = NULL;
}

CCChatRoomDataSource::~CCChatRoomDataSource()
{
    this->setChatMessages( NULL );
}

CCSize CCChatRoomDataSource::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake( _chatView->getContentSize().width * 0.9f, 16);
}

bool CCChatRoomDataSource::init( CCChatRoom* chatView )
{
    _chatView = chatView;
    this->initMessages();
    this->setMaxMessages( 64 );
    
    //this->submitMessage( "Welcome to Cocos2d-x chat with Photon!" );
    return true;
}

CCChatRoomDataSource* CCChatRoomDataSource::create( CCChatRoom* chatView )
{
    CCChatRoomDataSource* ret = new CCChatRoomDataSource();
    
    if( ret && ret->init( chatView ) )
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( ret );
    }
    
    return ret;
}

CCArray* CCChatRoomDataSource::initMessages()
{
    if( ! this->_chatMessages )
    {
        _chatMessages = CCArray::create();
    }
    
    return _chatMessages;
}

int CCChatRoomDataSource::submitMessage( const char* str )
{
    this->initMessages();
    
    CCLabelTTF* message = CCLabelTTF::create( str, "fonts/American Typewriter.ttf", 12 );
    _chatMessages->addObject( message );
    
    if( _chatMessages->count() >= this->getMaxMessages() )
    {
        _chatMessages->removeObjectAtIndex( 0 );
    }
    
    return _chatMessages->count();
}

CCTableViewCell* CCChatRoomDataSource::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    this->initMessages();
    CCChatTableCell *cell = (CCChatTableCell*) table->dequeueCell();
    CCLabelTTF* label = (CCLabelTTF*) _chatMessages->objectAtIndex(idx);

    if( !cell )
    {
        if ( label->getParent())
        {
            label->removeFromParentAndCleanup(false);
        }
        cell = CCChatTableCell::create( label );
    }
    else
    {
        label = (CCLabelTTF*) _chatMessages->objectAtIndex(cell->getIdx());
        CCNode* oldLabel = cell->getChildByTag( CCChatTableCell::Child::CCLabelTTF_message );
        if( oldLabel != label )
        {
            cell->removeChild( oldLabel, true );
            label->setTag(CCChatTableCell::Child::CCLabelTTF_message);
            cell->addChild( label );
        }
    }
    /*else
    {
        CCNode* oldLabel = cell->getChildByTag( 14631 );
        if( label != oldLabel )
        {
            CC_SAFE_RETAIN( label );
            CC_SAFE_RETAIN( oldLabel );

            if( label->getParent() )
            {
                label->removeFromParentAndCleanup( false );
            }
            
            bool releaseOld = !_chatMessages->containsObject( oldLabel );
            cell->removeChild( oldLabel, !releaseOld );
            cell->addChild( label );
            
            CC_SAFE_RELEASE( label );
            if( releaseOld )
            {
                CC_SAFE_RELEASE( oldLabel );
            }
        }
    }*/
    
    return cell;
}

unsigned int CCChatRoomDataSource::numberOfCellsInTableView(CCTableView *table)
{
    this->initMessages();
    return _chatMessages->count();
}

void CCChatRoom::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
    
}

void CCChatRoom::scrollViewDidScroll( cocos2d::extension::CCScrollView* view)
{
    
}

void CCChatRoom::scrollViewDidZoom( cocos2d::extension::CCScrollView* view)
{
    
}

void CCChatRoom::onEnter()
{
    CCLayer::onEnter();
    this->getParent()->runAction( CCRecursiveAction::create(CCEnable::create(false), this) );
}

void CCChatRoom::onExit()
{
    this->getParent()->runAction( CCRecursiveAction::create(CCEnable::create(true), this) );
    CCLayer::onExit();
}