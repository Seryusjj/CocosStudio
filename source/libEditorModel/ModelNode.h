#include "DLLDefines.h"
#include <vector>

class EXPORT  ModelNode
{
public:
	ModelNode();
	~ModelNode();
	void* data;
	ModelNode* parentNode;
	std::vector<ModelNode*> GetChildren();

private:
	std::vector<ModelNode*> _children;
};



