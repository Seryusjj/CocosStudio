#ifndef _COCOS_GL_CANVAS_H_
#define  _COCOS_GL_CANVAS_H_

#include "stdafx.h"

class CocosGLCanvas : public wxGLCanvas
{
public:
	CocosGLCanvas(wxWindow *parent, int *attribList = NULL);

private:
	void OnPaint(wxPaintEvent& event);
	void Spin(float xSpin, float ySpin);
	void OnKeyDown(wxKeyEvent& event);
	void OnSpinTimer(wxTimerEvent& WXUNUSED(event));

	// angles of rotation around x- and y- axis
	float m_xangle,
		m_yangle;

	wxTimer m_spinTimer;
	bool m_useStereo,
		m_stereoWarningAlreadyDisplayed;

	wxDECLARE_EVENT_TABLE();
};

class ccwxGLView : public cocos2d::GLView
{
	CocosGLCanvas* mGLCanvas;

public:
	ccwxGLView(CocosGLCanvas* canvas) {
		setGLCanvas(canvas);
	}

	virtual ~ccwxGLView(void) {}

	static ccwxGLView* create(CocosGLCanvas* canvas) {
		auto ret = new (std::nothrow) ccwxGLView(canvas);
		if (ret) {
			ret->autorelease();
			return ret;
		}
		return nullptr;
	}

	void setGLCanvas(CocosGLCanvas* canvas) {
		mGLCanvas = canvas;
	}
	CocosGLCanvas* getGLCanvas() {
		return mGLCanvas;
	}

	HWND getWin32Window() {
		return mGLCanvas->GetParent()->GetHWND();
	}

	/** Force destroying EGL view, subclass must implement this method. */
	virtual void end() {
		mGLCanvas->Close();
		wxDELETE(mGLCanvas);
		mGLCanvas = nullptr;
	}

	/** Get whether opengl render system is ready, subclass must implement this method. */
	virtual bool isOpenGLReady() {
		return (mGLCanvas && mGLCanvas->IsShown());
	}

	/** Exchanges the front and back buffers, subclass must implement this method. */
	virtual void swapBuffers() {
		mGLCanvas->SwapBuffers();
	}

	virtual void setIMEKeyboardState(bool open) {}

	virtual bool windowShouldClose() {
		return (mGLCanvas == nullptr);
	}
};

#endif //_COCOS_GL_CANVAS_H_