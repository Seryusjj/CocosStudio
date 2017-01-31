#pragma once
#include <wx/wx.h>
#include "MainFrameWrapper.h"
#include <functional>

// Define a new application type
class MyApp : public wxApp
{
public:
	MyApp() { m_glContext = NULL; m_glStereoContext = NULL; }

	// Returns the shared context used by all frames and sets it as current for
	// the given canvas.
	CocosGLContext& GetContext(wxGLCanvas *canvas, bool useStereo);

	// virtual wxApp methods
	virtual bool OnInit() override;
	virtual int OnExit() override;

private:
	// the GL context we use for all our mono rendering windows
	CocosGLContext *m_glContext;
	// the GL context we use for all our stereo rendering windows
	CocosGLContext *m_glStereoContext;
};

MyApp& GetCurrentApp();
