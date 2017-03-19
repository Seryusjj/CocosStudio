#pragma once

#include "stdafx.h"

#include "GridCustomCommand.h"

class EditorGrid : public cocos2d::Sprite3D
{
protected:
	friend class cocos2d::Mesh;
	friend class cocos2d::MeshCommand;
public:

	EditorGrid();
	~EditorGrid();

	virtual bool init() override;
	//virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	CREATE_FUNC(EditorGrid);

protected:
	//draw a grid of a certain size centered on the 0,0,0
	void drawGrid(int gridSize);
private:
};
