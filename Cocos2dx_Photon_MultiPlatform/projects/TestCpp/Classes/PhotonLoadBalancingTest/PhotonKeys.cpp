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

#include "PhotonKeys.h"
#include <assert.h>

const char* PhotonHashKey::HashString[PhotonHashKey::HASH_KEY_COUNT] =
{
    "player_index",
    "game_master",
    "key_number",
    "player_name",
    "peer_id"
};

const char* PhotonHashKey::getString( PhotonHashKey::HashInt key )
{

    assert( key >= 0 && key < PhotonHashKey::HASH_KEY_COUNT );
    return HashString[ key ];
}

const char* PhotonNoteKey::NoteString[PhotonNoteKey::NOTE_KEY_COUNT] =
{
    "connect_return",
    "disconnect_return",
    "create_room_return",
    "join_room_return",
    "join_specific_room_return",
    "join_random_room_return",
    "leave_room_return",
    "got_queued_return",
    "join_lobby_return",
    "leave_lobby_return"
};

const char* PhotonNoteKey::getString( PhotonNoteKey::NoteInt key )
{
    assert( key >= 0 && key < PhotonNoteKey::NOTE_KEY_COUNT );
    return NoteString[ key ];
}
