#include "UIListener.h"

#include <string>

class StdIO_UIListener: public UIListener
{
private:
	virtual void writeString(const wchar_t* str);
	virtual bool anyKeyPressed() const;
	virtual void onLibClosed();

private:
	std::wstring lastString;
};

