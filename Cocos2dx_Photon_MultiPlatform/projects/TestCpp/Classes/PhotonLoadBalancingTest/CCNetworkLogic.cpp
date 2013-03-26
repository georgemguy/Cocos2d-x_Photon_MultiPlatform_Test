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

#include "CCNetworkLogic.h"
#include "PhotonKeys.h"

USING_NS_CC;
using namespace ExitGames;
using namespace Common;
using namespace LoadBalancing;

CCNetworkLogic* CCNetworkLogic::_sharedCCNetworkLogic = NULL;

CCNetworkLogic::CCNetworkLogic()
: NetworkLogic(this, "1.0.0.0")
{
    registerForStateUpdates(this);
    _output = "";
}

CCNetworkLogic::~CCNetworkLogic()
{
    _sharedCCNetworkLogic->disconnect();
    if( _sharedCCNetworkLogic == this )
    {
        _sharedCCNetworkLogic = NULL;
    }
}

CCNetworkLogic* CCNetworkLogic::sharedCCNetworkLogic()
{
    if( _sharedCCNetworkLogic )
    {
        return _sharedCCNetworkLogic;
    }
    
    _sharedCCNetworkLogic = new CCNetworkLogic();
    _sharedCCNetworkLogic->autorelease();
    _sharedCCNetworkLogic->retain();
    CCDirector* director = CCDirector::sharedDirector();
    director->getScheduler()->scheduleUpdateForTarget( _sharedCCNetworkLogic, 0, false );
    
    return _sharedCCNetworkLogic;
}

void CCNetworkLogic::purgeCCNetworkLogic()
{
    CC_SAFE_RELEASE_NULL( _sharedCCNetworkLogic );
}

void CCNetworkLogic::write(const ExitGames::Common::JString& str)
{
    //[mConsole write:[NSString stringWithUTF8String:str.UTF8Representation().cstr()]];
    /*using namespace std;
    
    CCString ccOutput = this->getOutput();
    const char* cOutput = ccOutput.getCString();
    string cppOutput = string( cOutput );
    
    const char* cStr = str.UTF8Representation().cstr();
    string cppStr = string( cStr );
    
    this->_output = cppOutput + cppStr;*/
    CCLog( "%s", str.UTF8Representation().cstr() );
}

void CCNetworkLogic::messageBox(const ExitGames::Common::JString& str)
{
    //[mConsole writeLine:[NSString stringWithUTF8String:str.UTF8Representation().cstr()]];
    using namespace std;

    string cStr = str.UTF8Representation().cstr();

    //this->_output = cppStr;
    CCMessageBox( cStr.c_str(), "Photon" );
    CCLog( "%s", cStr.c_str() );
}

void CCNetworkLogic::writeLine(const ExitGames::Common::JString& str)
{
    //[mConsole writeLine:[NSString stringWithUTF8String:str.UTF8Representation().cstr()]];
    using namespace std;

    string cStr = str.UTF8Representation().cstr();
    
    //this->_output = cppStr;
    this->_output = cStr.c_str();
    CCLog( "%s", cStr.c_str() );
}

int CCNetworkLogic::getRoomPropertyInt( const char* key )
{
    MutableRoom& room = this->getCurrentRoom();
    Hashtable properties = room.getCustomProperties();
    
    if( properties.contains<JString>(key) )
    {
        JString jStr = properties.getValue<JString>(key)->toString();
        
        if( jStr.length() )
        {
            return jStr.toInt();
        }
    }
    return -1;
}

int CCNetworkLogic::getRoomPropertyInt( int key )
{
    CCAssert( key >= 0 && key < PhotonHashKey::HASH_KEY_COUNT, "CCNetworkLogic::getRoomPropertyInt() -- Invalid hash key!" );
    MutableRoom& room = this->getCurrentRoom();
    Hashtable properties = room.getCustomProperties();
    
    if( properties.contains<int>(key) )
    {
        JString jStr = properties.getValue<int>(key)->toString();
    
        if( jStr.length() )
        {
            return jStr.toInt();
        }
    }
    return this->getRoomPropertyInt( PhotonHashKey::getString( (PhotonHashKey::HashInt) key ) );
}

cocos2d::CCString CCNetworkLogic::getRoomPropertyString( const char* key )
{
    MutableRoom& room = this->getCurrentRoom();
    Hashtable properties = room.getCustomProperties();
    const Object* value = properties.getValue<JString>(key);
    
    if( value )
    {
        return value->toString().ANSIRepresentation().cstr();
    }
    return "";
}

cocos2d::CCString CCNetworkLogic::getRoomPropertyString( int key )
{
    MutableRoom& room = this->getCurrentRoom();
    Hashtable properties = room.getCustomProperties();
    const Object* value = properties.getValue<int>(key);
    
    if( value )
    {
        return value->toString().ANSIRepresentation().cstr();
    }
    return "";
}

void CCNetworkLogic::notify( int note )
{
    CCNotificationCenter* publisher = CCNotificationCenter::sharedNotificationCenter();
    publisher->postNotification( PhotonNoteKey::getString( (PhotonNoteKey::NoteInt) note ) );
}

void CCNetworkLogic::stateUpdate(State newState)
{
    //[mAppDelegate stateUpdate:newState];
    
    //this->_output = this->getStateString( newState );
    //CCLog( "State = %d", newState );
}

CCString CCNetworkLogic::getStateString(State state)
{
	switch(state)
	{
		case STATE_INITIALIZED:
			return "disconnected";
        case STATE_WAITING:
            return "connecting";
		case STATE_CONNECTING:
			return "connecting";
		case STATE_CONNECTED:
			return "connected";
		case STATE_JOINING:
			return "joining";
		case STATE_JOINED:
			return "joined";
		case STATE_LEAVING:
			return "leaving";
		case STATE_LEFT:
			return "left";
		case STATE_DISCONNECTING:
			return "disconnecting";
		case STATE_DISCONNECTED:
			return "disconnected";
		default:
			return "unknown state";
	}
}

JString CCNetworkLogic::getUserName()
{
    return CCUserDefault::sharedUserDefault()->getStringForKey( "Name" ).c_str();
}

cocos2d::CCString CCNetworkLogic::getGameID()
{
    return _ccGameID = this->_gameID.ANSIRepresentation().cstr();
}

void CCNetworkLogic::update( float delta )
{
    this->run();
}
