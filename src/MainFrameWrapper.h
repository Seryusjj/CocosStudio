#pragma once

#include "noname.h"
#include "wx/glcanvas.h"
#include "wx/timer.h"
#include "wx/dcmemory.h"
#include "wx/dcclient.h"

#include "wx/frame.h"
#include "wx/statusbr.h"
#include "wx/menu.h"

//GLCONTEXT
// the rendering context used by all GL canvases
class CocosGLContext : public wxGLContext
{
public:
	CocosGLContext(wxGLCanvas *s);

	// render the cube showing it at given angles
	void DrawRotatedCube(float xangle, float yangle);

private:
	// textures for the cube faces
	GLuint m_textures[6];
};

//GLCANVAS
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

//Main Frame
class MainFrameWrapper : public MainFrame {
protected:
	CocosGLCanvas* cocosglCanvas;
public:
	MainFrameWrapper(bool stereoWindow);

	~MainFrameWrapper();

	void OnClose(wxCommandEvent& event);
	void OnNewWindow(wxCommandEvent& event);
	void OnNewStereoWindow(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};
