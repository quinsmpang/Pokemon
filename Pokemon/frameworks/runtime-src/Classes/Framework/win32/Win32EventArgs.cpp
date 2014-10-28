#include "Win32EventArgs.h"

namespace framework
{
	Win32EventArgs::Win32EventArgs(void *params)
		: _params(params)
	{
	}

	Win32EventArgs::~Win32EventArgs()
	{
		if (_params)
		{
			delete _params;
		}
	}
}