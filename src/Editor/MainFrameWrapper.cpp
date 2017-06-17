#include "stdafx.h"
#include "MainFrameWrapper.h"

//helpers

//MAIN FRAME
enum { NEW_STEREO_WINDOW = wxID_HIGHEST + 1 };

wxBEGIN_EVENT_TABLE(MainFrameWrapper, MainFrame)
EVT_MENU(wxID_NEW, MainFrameWrapper::OnNewWindow)
EVT_MENU(NEW_STEREO_WINDOW, MainFrameWrapper::OnNewStereoWindow)
EVT_MENU(wxID_CLOSE, MainFrameWrapper::OnClose)
wxEND_EVENT_TABLE()

MainFrameWrapper::MainFrameWrapper(bool stereoWindow) : MainFrame(nullptr)

{
	//int attribs[] = { WX_GL_FRAMEBUFFER_SRGB,WX_GL_ROBUST_ACCESS, WX_GL_DOUBLEBUFFER, 0 };
	cocosglCanvas = new CocosGLCanvas(openGLContainer);
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
	cocos2d::GLView::setGLContextAttrs(glContextAttrs);
	// Setters, allowing chained calls
	GLContextAttrs attr;
	attr.alphaBits = glContextAttrs.alphaBits;
	attr.blueBits = glContextAttrs.blueBits;
	attr.depthBits = glContextAttrs.depthBits;
	attr.greenBits = glContextAttrs.greenBits;
	attr.redBits = glContextAttrs.redBits;
	attr.stencilBits = glContextAttrs.stencilBits;

	cocosglCanvas->setGLContextAttrs(attr);
	openGLContainer->GetSizer()->Add(cocosglCanvas, 1, wxEXPAND, 5);
	openGLContainer->GetSizer()->Fit(openGLContainer);
}

MainFrameWrapper::~MainFrameWrapper() {
	cocosglCanvas->release();
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
	new MainFrameWrapper(false);
}