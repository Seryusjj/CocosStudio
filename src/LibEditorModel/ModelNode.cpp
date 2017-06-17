#include "ModelNode.h"

ModelNode::ModelNode()
{
}

ModelNode::~ModelNode()
{
}

std::vector<ModelNode*> ModelNode::GetChildren()
{
	return _children;
}
