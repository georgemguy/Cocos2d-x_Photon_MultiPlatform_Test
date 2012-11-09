#include <iostream>

int EG_kbhit();

#ifdef _EG_WIN32_PLATFORM
#include <windows.h>
#include <conio.h>

int EG_kbhit()
{
	int res = _kbhit();
	if(res)
		_getch();
	return res;
}

#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>

int EG_kbhit()
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		return 1;
	}

	return 0;
}
#endif

#include "StdIO_UIListener.h"

void StdIO_UIListener::writeString(const wchar_t* str)
{
	if(lastString.compare(str) != 0)
	{
		std::wcout << str << std::endl;
		lastString = str;
	}
}

bool StdIO_UIListener::anyKeyPressed() const
{
	return EG_kbhit() != 0;
}

void StdIO_UIListener::onLibClosed()
{
	writeString(L"- -Press any key to quit- ------------------\n");
	//while(!anyKeyPressed());
}
