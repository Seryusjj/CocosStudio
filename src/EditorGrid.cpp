#include "stdafx.h"
#include "EditorGrid.h"

USING_NS_CC;

EditorGrid::EditorGrid()
{
}

EditorGrid::~EditorGrid()
{
}

void EditorGrid::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	//super.draw
	Node::draw(renderer, transform, flags);

	auto color = Color4F::RED;
	glColor4f(color.r, color.g, color.b, color.a);

	//Create commands
	_customGrid.func = [&]
	{
		drawGrid(60);
	};

	//add to renderer
	renderer->addCommand(&_customGrid);
}

bool EditorGrid::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void EditorGrid::drawGrid(int gridSize)
{
	int halfGrid = gridSize / 2;

	//from -size to 0
	for (int x = -halfGrid; x < halfGrid; x++) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(x, 0, 0);
		glVertex3f(x, 0, -halfGrid);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(x, 0, 0);
		glVertex3f(x, 0, halfGrid);
		glEnd();
	}
	for (int z = -halfGrid; z < halfGrid; z++) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, z);
		glVertex3f(-halfGrid, 0, z);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, z);
		glVertex3f(halfGrid, 0, z);
		glEnd();
	}
}