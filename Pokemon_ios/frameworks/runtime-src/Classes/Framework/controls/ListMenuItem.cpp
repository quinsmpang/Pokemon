#include "ListMenuItem.h"

using namespace cocos2d;

namespace framework
{
	ssize_t ListMenuItem::INVALID_INDEX = -1;

	ListMenuItem::ListMenuItem()
		: Node()
		, _showIndex(INVALID_INDEX)
	{
	}

	ListMenuItem::~ListMenuItem()
	{
	}

	void ListMenuItem::reset()
	{
		this->_showIndex = INVALID_INDEX;
	}
}