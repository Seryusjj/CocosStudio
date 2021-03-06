#include "stdafx.h"
#include "MainFrameWrapper.h"
#include "CustomDockArt.h"
#include "CocosGLCanvas3DController.h"
//helpers

//MAIN FRAME

wxBEGIN_EVENT_TABLE(MainFrameWrapper, MainFrame)
EVT_MENU(wxID_CLOSE, MainFrameWrapper::OnClose)
wxEND_EVENT_TABLE()

MainFrameWrapper::MainFrameWrapper(bool stereoWindow) : MainFrame(nullptr)

{
	int attribs[] =
	{
		WX_GL_RGBA,
		WX_GL_DEPTH_SIZE, 16,
		WX_GL_DOUBLEBUFFER,
		WX_GL_SAMPLE_BUFFERS,1,
		WX_GL_SAMPLES,4,
	0 };

	cocosglCanvas = new CocosGLCanvas(openGLContainer, new CocosGLCanvas3DController(), attribs);

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
	//attr.RGBA().Depth(16).DoubleBuffer().SampleBuffers(1).Samplers(4);
	//SetNeedsARB();

	cocosglCanvas->setGLContextAttrs(attr);
	openGLContainer->GetSizer()->Add(cocosglCanvas, 1, wxEXPAND, 5);
	openGLContainer->GetSizer()->Fit(openGLContainer);

	m_mgr.SetArtProvider(new CustomDockArt());
}

MainFrameWrapper::~MainFrameWrapper() {
	cocosglCanvas->release();
}

void MainFrameWrapper::OnClose(wxCommandEvent & event)
{
	// true is to force the frame to close
	Close(true);
}