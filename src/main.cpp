// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>
#include <tchar.h>

// C RunTime Header Files/#include "platform/CCStdC.h"

#define ssize_t SSIZE_T
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "cocos2d.h"
#undef ssize_t

#define ssize_t wxInt32
#include "MyApp.h"
#undef ssize_t

wxIMPLEMENT_APP(MyApp);

int WINAPI _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// create the application instance
	//AppDelegate app;
	//return Application::getInstance()->run();
	return 0;
}

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