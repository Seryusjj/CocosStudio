#pragma once

#include "noname.h"
#include "stdafx.h"

//GLCONTEXT & GLCANVAS
#include "CocosGLContext.h"
#include "CocosGLCanvas.h"

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
