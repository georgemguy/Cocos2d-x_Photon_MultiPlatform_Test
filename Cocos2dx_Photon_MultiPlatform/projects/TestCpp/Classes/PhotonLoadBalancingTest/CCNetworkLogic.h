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

#ifndef __PhotonOnline__CCNetworkLogic__
#define __PhotonOnline__CCNetworkLogic__

#include "NetworkLogic.h"
#include "OutputListener.h"
#include "cocos2d.h"
#include <iostream>

class CCNetworkLogic : public NetworkLogic, public OutputListener, public NetworkLogicListener, public cocos2d::CCObject
{    
    CC_SYNTHESIZE_READONLY( cocos2d::CCString, _output, Output );
    CC_PROPERTY_READONLY( cocos2d::CCString, _ccGameID, GameID );
    
public:
	CCNetworkLogic();
	virtual ~CCNetworkLogic();
    
    virtual ExitGames::Common::JString getUserName();
    
	virtual void write(const ExitGames::Common::JString& str);
	
	virtual void writeLine(const ExitGames::Common::JString& str);
    virtual void messageBox(const ExitGames::Common::JString& str );
    
	virtual void stateUpdate(State newState);
    
    virtual cocos2d::CCString getStateString( State state );
        
    virtual void update( float delta );
            
    virtual void notify( int note );
    
    virtual cocos2d::CCString getRoomPropertyString( int key );
    virtual cocos2d::CCString getRoomPropertyString( const char* key );
    virtual int getRoomPropertyInt( int key );
    virtual int getRoomPropertyInt( const char* key );
    
protected: static CCNetworkLogic* _sharedCCNetworkLogic;
public:
    static CCNetworkLogic* sharedCCNetworkLogic();
    static void purgeCCNetworkLogic();
};

#endif /* defined(__PhotonOnline__CCNetworkLogic__) */
