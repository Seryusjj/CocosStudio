#include "stdafx.h"
#include "CocosGLCanvas3DController.h"

bool middleDragAction = false;
bool rightDragAction = false;
wxPoint pointOnDragStart;

CocosGLCanvas3DController::CocosGLCanvas3DController()
{
	_sceneLogicLayer = nullptr;
}

CocosGLCanvas3DController::~CocosGLCanvas3DController()
{
	CC_SAFE_RELEASE(_currentScene);
}

void CocosGLCanvas3DController::OnKeyDown(wxKeyEvent & event)
{
}

void CocosGLCanvas3DController::OnMouseWheel(wxMouseEvent & event)
{
	if (!middleDragAction && !rightDragAction) {
		int rotation = event.GetWheelRotation();
		if (rotation != 0) {
			float zoomFactor = 1.0f;
			if (rotation < 0)
				zoomFactor *= -1;

			GetCurrentLogicLayer()->zoom(zoomFactor);
			GetParent()->Refresh(true);
		}
	}
}

void CocosGLCanvas3DController::OnMouseLeftDown(wxMouseEvent & event)
{
	wxPoint point = PointToCocos(event.GetPosition());
	if (_selection.size() > 0)
	{
		auto currentSelection = _selection.top();
		GetCurrentLogicLayer()->removeBoundingBox(currentSelection);
		_selection.pop();
	}

	auto selection = GetCurrentLogicLayer()->select(point.x, point.y);
	GetCurrentLogicLayer()->addBoundingBox(selection);
	_selection.push(selection);
	GetParent()->Refresh(true);
}

void CocosGLCanvas3DController::OnMouseLeftUp(wxMouseEvent & event)
{
	GetParent()->SetFocus();
}

void CocosGLCanvas3DController::OnMouseRightDown(wxMouseEvent & event)
{
	pointOnDragStart = event.GetPosition();
	rightDragAction = true;
}

void CocosGLCanvas3DController::OnMouseRightUp(wxMouseEvent & event)
{
	rightDragAction = false;
	GetParent()->SetFocus();
}

void CocosGLCanvas3DController::OnMouseMoveEvent(wxMouseEvent & event)
{
	if (event.Dragging())
	{
		if (middleDragAction)
		{
			wxPoint point = event.GetPosition();
			float x = point.x - pointOnDragStart.x;
			float y = point.y - pointOnDragStart.y;
			AdjustSpeed(&x, &y, 0.1f);
			GetCurrentLogicLayer()->pan(-x, y);
			//redraw view
			GetParent()->Refresh(true);
			pointOnDragStart = event.GetPosition();
		}
		else if (rightDragAction)
		{
			wxPoint point = event.GetPosition();
			float x = point.x - pointOnDragStart.x;
			float y = point.y - pointOnDragStart.y;
			AdjustSpeed(&x, &y, 0.2f);
			GetCurrentLogicLayer()->rotateView(x, -y);
			//redraw view
			GetParent()->Refresh(true);
			pointOnDragStart = event.GetPosition();
		}
	}
	else
	{
		rightDragAction = false;
		middleDragAction = false;
	}
}

void CocosGLCanvas3DController::OnMouseMiddleDown(wxMouseEvent & event)
{
	pointOnDragStart = event.GetPosition();
	middleDragAction = true;
}

void CocosGLCanvas3DController::OnMouseMiddleUp(wxMouseEvent & event)
{
	middleDragAction = false;
	GetParent()->SetFocus();
}

void CocosGLCanvas3DController::InitController()
{
	_currentScene = EditorScene3D::createScene();
	_currentScene->retain();
}