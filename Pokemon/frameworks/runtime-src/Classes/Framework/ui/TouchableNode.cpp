#include "TouchableNode.h"

using namespace cocos2d;

namespace framework
{

/*********************public functions*********************/
bool TouchableNode::init()
{
	return Node::init();
}

/*********************private functions*********************/
TouchableNode::TouchableNode()
	: Node()
{
}

TouchableNode::~TouchableNode()
{
	if (this->_defaultImage)
	{
		CC_SAFE_RELEASE_NULL(_defaultImage);
	}
}

}