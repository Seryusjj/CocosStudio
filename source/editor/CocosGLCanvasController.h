#pragma once

#include "stdafx.h"

class CocosGLCanvasController
{
protected:
	std::stack<cocos2d::Node*> _selection;
	wxGLCanvas* _parent;
	cocos2d::Scene* _currentScene;

public:
	virtual void InitController() = 0;
	virtual void OnKeyDown(wxKeyEvent& event) = 0;
	virtual void OnMouseWheel(wxMouseEvent & event) = 0;
	virtual void OnMouseLeftDown(wxMouseEvent & event) = 0;
	virtual void OnMouseLeftUp(wxMouseEvent & event) = 0;
	virtual void OnMouseRightDown(wxMouseEvent & event) = 0;
	virtual void OnMouseRightUp(wxMouseEvent & event) = 0;
	virtual void OnMouseMoveEvent(wxMouseEvent & event) = 0;

	virtual void OnMouseMiddleDown(wxMouseEvent & event) = 0;

	virtual void OnMouseMiddleUp(wxMouseEvent & event) = 0;

	inline cocos2d::Scene* GetCurrentScene()
	{
		return _currentScene;
	};

	inline virtual wxGLCanvas* GetParent()
	{
		return _parent;
	};

	inline virtual void SetParent(wxGLCanvas* parent)
	{
		_parent = parent;
	};

protected:
	template <class  T>
	inline T* GetCurrentLogicLayerInternal()
	{
		auto layer = GetCurrentScene()->getChildByTag(0);
		auto sceneLogicLayer = dynamic_cast<T*>(layer);
		return sceneLogicLayer;
	}

	void AdjustSpeed(float* x, float* y, float speed)
	{
		float valueX = *x;
		float valueY = *y;
		if (valueX > 0)	*x = speed;
		if (valueX < 0)	*x = -speed;
		if (valueY > 0)	*y = speed;
		if (valueY < 0)	*y = -speed;
	}

	wxPoint PointToCocos(const wxPoint& originalWxPoint)
	{
		auto realFrameSize = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
		auto screenSize = cocos2d::Director::getInstance()->getWinSize();

		float y = (originalWxPoint.y * screenSize.height) / realFrameSize.height;
		float x = (originalWxPoint.x * screenSize.width) / realFrameSize.width;
		auto result = wxPoint(x, y);
		return result;
	}
};
