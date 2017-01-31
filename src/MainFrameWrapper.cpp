#include "MainFrameWrapper.h"
#include "MyApp.h"

//helpers

enum
{
	SpinTimer = wxID_HIGHEST + 1
};

enum { NEW_STEREO_WINDOW = wxID_HIGHEST + 1 };

static void CheckGLError()
{
	GLenum errLast = GL_NO_ERROR;

	for (;; )
	{
		GLenum err = glGetError();
		if (err == GL_NO_ERROR)
			return;

		// normally the error is reset by the call to glGetError() but if
		// glGetError() itself returns an error, we risk looping forever here
		// so check that we get a different error than the last time
		if (err == errLast)
		{
			wxLogError(wxT("OpenGL error state couldn't be reset."));
			return;
		}

		errLast = err;

		wxLogError(wxT("OpenGL error %d"), err);
	}
}

static wxImage DrawDice(int size, unsigned num)
{
	wxASSERT_MSG(num >= 1 && num <= 6, wxT("invalid dice index"));

	const int dot = size / 16;        // radius of a single dot
	const int gap = 5 * size / 32;      // gap between dots

	wxBitmap bmp(size, size);
	wxMemoryDC dc;
	dc.SelectObject(bmp);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	dc.SetBrush(*wxBLACK_BRUSH);

	// the upper left and lower right points
	if (num != 1)
	{
		dc.DrawCircle(gap + dot, gap + dot, dot);
		dc.DrawCircle(size - gap - dot, size - gap - dot, dot);
	}

	// draw the central point for odd dices
	if (num % 2)
	{
		dc.DrawCircle(size / 2, size / 2, dot);
	}

	// the upper right and lower left points
	if (num > 3)
	{
		dc.DrawCircle(size - gap - dot, gap + dot, dot);
		dc.DrawCircle(gap + dot, size - gap - dot, dot);
	}

	// finally those 2 are only for the last dice
	if (num == 6)
	{
		dc.DrawCircle(gap + dot, size / 2, dot);
		dc.DrawCircle(size - gap - dot, size / 2, dot);
	}

	dc.SelectObject(wxNullBitmap);

	return bmp.ConvertToImage();
}

wxString glGetwxString(GLenum name)
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

//GLCONTEXT

CocosGLContext::CocosGLContext(wxGLCanvas *canvas)
	: wxGLContext(canvas)
{
	SetCurrent(*canvas);

	// set up the parameters we want to use
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	// add slightly more light, the default lighting is rather dark
	GLfloat ambient[] = { 0.5, 0.5, 0.5, 0.5 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// set viewing projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);

	// create the textures to use for cube sides: they will be reused by all
	// canvases (which is probably not critical in the case of simple textures
	// we use here but could be really important for a real application where
	// each texture could take many megabytes)
	glGenTextures(WXSIZEOF(m_textures), m_textures);

	for (unsigned i = 0; i < WXSIZEOF(m_textures); i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		const wxImage img(DrawDice(256, i + 1));

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.GetWidth(), img.GetHeight(),
			0, GL_RGB, GL_UNSIGNED_BYTE, img.GetData());
	}

	CheckGLError();
}

void CocosGLContext::DrawRotatedCube(float xangle, float yangle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(xangle, 1.0f, 0.0f, 0.0f);
	glRotatef(yangle, 0.0f, 1.0f, 0.0f);

	// draw six faces of a cube of size 1 centered at (0, 0, 0)
	glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[2]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[3]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[4]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_textures[5]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glFlush();

	CheckGLError();
}

//GLCANVAS

wxBEGIN_EVENT_TABLE(CocosGLCanvas, wxGLCanvas)
EVT_PAINT(CocosGLCanvas::OnPaint)
EVT_KEY_DOWN(CocosGLCanvas::OnKeyDown)
EVT_TIMER(SpinTimer, CocosGLCanvas::OnSpinTimer)
wxEND_EVENT_TABLE()

//void CocosGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
//{
//
//
//}

void CocosGLCanvas::OnPaint(wxPaintEvent & event)
{
	// This is required even though dc is not used otherwise.
	wxPaintDC dc(this);

	// Set the OpenGL viewport according to the client size of this canvas.
	// This is done here rather than in a wxSizeEvent handler because our
	// OpenGL rendering context (and thus viewport setting) is used with
	// multiple canvases: If we updated the viewport in the wxSizeEvent
	// handler, changing the size of one canvas causes a viewport setting that
	// is wrong when next another canvas is repainted.
	const wxSize ClientSize = GetClientSize();

	CocosGLContext& canvas = GetCurrentApp().GetContext(this, m_useStereo);
	glViewport(0, 0, ClientSize.x, ClientSize.y);

	// Render the graphics and swap the buffers.
	GLboolean quadStereoSupported;
	glGetBooleanv(GL_STEREO, &quadStereoSupported);
	if (quadStereoSupported)
	{
		glDrawBuffer(GL_BACK_LEFT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-0.47f, 0.53f, -0.5f, 0.5f, 1.0f, 3.0f);
		canvas.DrawRotatedCube(m_xangle, m_yangle);
		CheckGLError();
		glDrawBuffer(GL_BACK_RIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-0.53f, 0.47f, -0.5f, 0.5f, 1.0f, 3.0f);
		canvas.DrawRotatedCube(m_xangle, m_yangle);
		CheckGLError();
	}
	else
	{
		canvas.DrawRotatedCube(m_xangle, m_yangle);
		if (m_useStereo && !m_stereoWarningAlreadyDisplayed)
		{
			m_stereoWarningAlreadyDisplayed = true;
			wxLogError("Stereo not supported by the graphics card.");
		}
	}
	SwapBuffers();
}

void CocosGLCanvas::Spin(float xSpin, float ySpin)
{
	m_xangle += xSpin;
	m_yangle += ySpin;

	Refresh(false);
}

void CocosGLCanvas::OnKeyDown(wxKeyEvent& event)
{
	float angle = 5.0;

	switch (event.GetKeyCode())
	{
	case wxKeyCode::WXK_CONTROL_D:
		Spin(0.0, -angle);
		m_spinTimer.StartOnce();
		break;

	case WXK_CONTROL_A:
		Spin(0.0, angle);
		m_spinTimer.StartOnce();
		break;

	case WXK_CONTROL_S:
		Spin(-angle, 0.0);
		m_spinTimer.StartOnce();
		break;

	case WXK_CONTROL_W:
		Spin(angle, 0.0);
		m_spinTimer.StartOnce();
		break;

	case WXK_SPACE:
		if (m_spinTimer.IsRunning())
			m_spinTimer.Stop();
		else
			m_spinTimer.Start(25);
		break;

	default:
		event.Skip();
		return;
	}
}

void CocosGLCanvas::OnSpinTimer(wxTimerEvent& WXUNUSED(event))
{
	Spin(0.0, 4.0);
}

CocosGLCanvas::CocosGLCanvas(wxWindow *parent, int *attribList)
// With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
// flag should always be set, because even making the canvas smaller should
// be followed by a paint event that updates the entire canvas with new
// viewport settings.
	: wxGLCanvas(parent, wxID_ANY, attribList,
		wxDefaultPosition, wxDefaultSize,
		wxFULL_REPAINT_ON_RESIZE),
	m_xangle(30.0),
	m_yangle(30.0),
	m_spinTimer(this, SpinTimer),
	m_useStereo(false),
	m_stereoWarningAlreadyDisplayed(false)
{
	if (attribList)
	{
		int i = 0;
		while (attribList[i] != 0)
		{
			if (attribList[i] == WX_GL_STEREO)
				m_useStereo = true;
			++i;
		}
	}
}

//MAIN FRAME

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
	//SetIcon(wxICON(sample));

	//Make a menubar
	//wxMenu *menu = new wxMenu;
	//menu->Append(wxID_NEW);
	//menu->Append(NEW_STEREO_WINDOW, "New Stereo Window");
	//menu->AppendSeparator();
	//menu->Append(wxID_CLOSE);
	//wxMenuBar *menuBar = new wxMenuBar;
	//menuBar->Append(menu, wxT("&Cube"));

	//SetMenuBar(menuBar);

	//CreateStatusBar();

	//SetClientSize(400, 400);
	//Show();

	// test IsDisplaySupported() function:
	static const int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };
	wxLogStatus("Double-buffered display %s supported",
		wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");

	if (stereoWindow)
	{
		const wxString vendor = glGetwxString(GL_VENDOR).Lower();
		const wxString renderer = glGetwxString(GL_RENDERER).Lower();
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