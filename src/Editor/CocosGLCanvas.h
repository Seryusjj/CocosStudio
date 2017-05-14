#ifndef _COCOS_GL_CANVAS_H_
#define  _COCOS_GL_CANVAS_H_

#include "stdafx.h"

class EditorScene3D;

class CocosGLCanvas : public wxGLCanvas, public cocos2d::GLView
{
public:
	int  _retinaFactor;//1 or 0
	float _frameZoomFactor;
	CocosGLCanvas(wxWindow *parent, int *attribList = NULL);

	/* override functions */
	virtual bool isOpenGLReady() override;
	virtual void end() override;
	virtual void swapBuffers() override;
	virtual void setFrameSize(float width, float height) override;
	virtual void setIMEKeyboardState(bool bOpen) override;

	virtual void setViewPortInPoints(float x, float y, float w, float h) override;
	virtual void setScissorInPoints(float x, float y, float w, float h) override;
	virtual cocos2d::Rect getScissorRect() const override;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	HWND getWin32Window() { return GetHWND(); }
#endif //(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

private:
	wxPoint inline pointToCocos(const wxPoint& originalWxPoint);
	EditorScene3D * _scene;
	cocos2d::Node* _currentSelection;

	void onResizeCanvas(float width, float height);
	bool initGl();
	bool initGlew();
	wxGLContext* m_context;
	void OnPaint(wxPaintEvent& event);

	void OnKeyDown(wxKeyEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnDrawTimer(wxTimerEvent& WXUNUSED(event));

	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseMiddleDown(wxMouseEvent& event);
	void OnMouseMiddleUp(wxMouseEvent& event);
	void OnMouseRightDown(wxMouseEvent& event);
	void OnMouseRightUp(wxMouseEvent& event);
	void OnMouseMoveEvent(wxMouseEvent& event);
	wxTimer _drawTimer;

	wxDECLARE_EVENT_TABLE();
};

#endif //_COCOS_GL_CANVAS_H_
