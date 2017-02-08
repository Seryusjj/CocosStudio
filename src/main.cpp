// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".

#include "MyApp.h"

wxIMPLEMENT_APP(MyApp);

CocosGLContext& MyApp::GetContext(wxGLCanvas *canvas, bool useStereo)
{
	CocosGLContext *glContext;
	if (useStereo)
	{
		if (!m_glStereoContext)
		{
			// Create the OpenGL context for the first stereo window which needs it:
			// subsequently created windows will all share the same context.
			m_glStereoContext = new CocosGLContext(canvas);
		}
		glContext = m_glStereoContext;
	}
	else
	{
		if (!m_glContext)
		{
			// Create the OpenGL context for the first mono window which needs it:
			// subsequently created windows will all share the same context.
			m_glContext = new CocosGLContext(canvas);
		}
		glContext = m_glContext;
	}

	glContext->SetCurrent(*canvas);

	return *glContext;
}

MyApp& GetCurrentApp() {
	return wxGetApp();
}

bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	MainFrameWrapper *frame = new MainFrameWrapper(false);

	frame->Show(true);
	return true;
}

int MyApp::OnExit()
{
	delete m_glContext;
	delete m_glStereoContext;

	return wxApp::OnExit();
}