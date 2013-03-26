/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __OUTPUT_LISTENER_H
#define __OUTPUT_LISTENER_H

#ifndef _EG_ANDROID_PLATFORM
#include <iostream>
#endif
#include "JString.h"

class OutputListener
{
public:
	virtual ~OutputListener(void){};
	virtual void write(const ExitGames::Common::JString& str) = 0;
	virtual void writeLine(const ExitGames::Common::JString& str) = 0;
    virtual void notify( int note ) = 0;
	virtual void debugReturn(const ExitGames::Common::JString& str)
	{
		#ifndef _EG_ANDROID_PLATFORM
			std::wcerr << str << std::endl;
		#endif
	}
};

#endif