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

#ifndef PhotonOnline_PhotonHashKeys_h
#define PhotonOnline_PhotonHashKeys_h

struct PhotonHashKey
{
    enum HashInt
    {
        int_PlayerIndex,
        int_GameMaster,
        int_KeyNumber,
        string_PlayerName,
        int_PeerId,
        int_IsGameMaster,
        HASH_KEY_COUNT
    };
    
    static const char* getString( HashInt key );

protected:
    static const char* HashString[HASH_KEY_COUNT];
};

struct PhotonNoteKey
{
    enum NoteInt
    {
        ConnectReturn,
        DisconnectReturn,
        CreateRoomReturn,
        JoinRoomReturn,
        JoinSpecificRoomReturn,
        JoinRandomRoomReturn,
        LeaveRoomReturn,
        GotQueuedReturn,
        JoinLobbyReturn,
        LeaveLobbyReturn,
        NOTE_KEY_COUNT
    };
    
    static const char* getString( NoteInt key );
    
protected:
    static const char* NoteString[NOTE_KEY_COUNT];
};

#endif
