#include "stdafx.h"

class EditorGrid : public cocos2d::Node
{
public:
	EditorGrid();
	~EditorGrid();
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	virtual bool init() override;
	cocos2d::CustomCommand _customGrid;
	CREATE_FUNC(EditorGrid);

protected:
	//draw a grid of a certain size centered on the 0,0,0
	void drawGrid(int gridSize);
private:
};
