#include "TouchableNode.h"

using namespace cocos2d;

namespace framework
{

TouchableNode::TouchableNode()
	: Node()
{
}

TouchableNode::~TouchableNode()
{
}

bool TouchableNode::init()
{
	return Node::init();
}

}