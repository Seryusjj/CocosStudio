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

	CREATE_FUNC(EditorGrid);

protected:

private:
};
