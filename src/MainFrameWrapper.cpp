#include "MainFrameWrapper.h"

//helpers

wxString glGetwxString1(GLenum name)
{
	const GLubyte *v = glGetString(name);
	if (v == 0)
	{
		// The error is not important. It is GL_INVALID_ENUM.
		// We just want to clear the error stack.
		glGetError();

		return wxString();
	}

	return wxString((const char*)v);
}

//MAIN FRAME
enum { NEW_STEREO_WINDOW = wxID_HIGHEST + 1 };

wxBEGIN_EVENT_TABLE(MainFrameWrapper, MainFrame)
EVT_MENU(wxID_NEW, MainFrameWrapper::OnNewWindow)
EVT_MENU(NEW_STEREO_WINDOW, MainFrameWrapper::OnNewStereoWindow)
EVT_MENU(wxID_CLOSE, MainFrameWrapper::OnClose)
wxEND_EVENT_TABLE()

MainFrameWrapper::MainFrameWrapper(bool stereoWindow) : MainFrame(nullptr)

{
	int stereoAttribList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_STEREO, 0 };

	auto glView = new CocosGLCanvas(openGLContainer, stereoWindow ? stereoAttribList : NULL);
	openGLContainer->GetSizer()->Add(glView, 1, wxEXPAND, 5);
	openGLContainer->GetSizer()->Fit(openGLContainer);

	// test IsDisplaySupported() function:
	static const int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };
	wxLogStatus("Double-buffered display %s supported",
		wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");

	if (stereoWindow)
	{
		const wxString vendor = glGetwxString1(GL_VENDOR).Lower();
		const wxString renderer = glGetwxString1(GL_RENDERER).Lower();
		if (vendor.find("nvidia") != wxString::npos &&
			renderer.find("quadro") == wxString::npos)
			ShowFullScreen(true);
	}
}

MainFrameWrapper::~MainFrameWrapper() {
}

void MainFrameWrapper::OnClose(wxCommandEvent & event)
{
	// true is to force the frame to close
	Close(true);
}

void MainFrameWrapper::OnNewWindow(wxCommandEvent & event)
{
	new MainFrameWrapper(false);
}

void MainFrameWrapper::OnNewStereoWindow(wxCommandEvent & event)
{
	new MainFrameWrapper(true);
}