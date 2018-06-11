#pragma once

#include "AbstractCocosGLCanvasController.h"
#include "EditorScene3D.h"

class CocosGLCanvas3DController : public AbstractCocosGLCanvasController
{
private:
	EditorScene3D * _sceneLogicLayer;

public:
	CocosGLCanvas3DController();
	~CocosGLCanvas3DController();

	virtual void OnKeyDown(wxKeyEvent& event) override;
	virtual void OnMouseWheel(wxMouseEvent & event) override;
	virtual void OnMouseLeftDown(wxMouseEvent & event) override;
	virtual void OnMouseLeftUp(wxMouseEvent & event) override;
	virtual void OnMouseRightDown(wxMouseEvent & event) override;
	virtual void OnMouseRightUp(wxMouseEvent & event) override;
	virtual void OnMouseMoveEvent(wxMouseEvent & event) override;
	virtual void OnMouseMiddleDown(wxMouseEvent & event) override;
	virtual void OnMouseMiddleUp(wxMouseEvent & event) override;
	virtual void InitController() override;

	inline EditorScene3D* GetCurrentLogicLayer()
	{
		if (_sceneLogicLayer != nullptr)
			return _sceneLogicLayer;
		else
		{
			_sceneLogicLayer = AbstractCocosGLCanvasController::GetCurrentLogicLayerInternal<EditorScene3D>();
			return _sceneLogicLayer;
		}
	}
};
