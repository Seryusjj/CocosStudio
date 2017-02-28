#include "stdafx.h"
#include "CocosGLCanvas.h"
#include <iostream>
#include "EditorScene.h"
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);

enum
{
	DrawTimer = wxID_HIGHEST + 1
};

wxBEGIN_EVENT_TABLE(CocosGLCanvas, wxGLCanvas)
EVT_PAINT(CocosGLCanvas::OnPaint)
EVT_KEY_DOWN(CocosGLCanvas::OnKeyDown)
EVT_TIMER(DrawTimer, CocosGLCanvas::OnDrawTimer)
wxEND_EVENT_TABLE()

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static bool glew_dynamic_binding()
{
	const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

	// If the current opengl driver doesn't have framebuffers methods, check if an extension exists
	if (glGenFramebuffers == nullptr)
	{
		//log("OpenGL: glGenFramebuffers is nullptr, try to detect an extension");
		if (strstr(gl_extensions, "ARB_framebuffer_object"))
		{
			//log("OpenGL: ARB_framebuffer_object is supported");

			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbuffer");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameteriv");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)wglGetProcAddress("glIsFramebuffer");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)wglGetProcAddress("glFramebufferTexture1D");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)wglGetProcAddress("glFramebufferTexture3D");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
		}
		else
			if (strstr(gl_extensions, "EXT_framebuffer_object"))
			{
				//log("OpenGL: EXT_framebuffer_object is supported");
				glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbufferEXT");
				glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbufferEXT");
				glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffersEXT");
				glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffersEXT");
				glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorageEXT");
				glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameterivEXT");
				glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)wglGetProcAddress("glIsFramebufferEXT");
				glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebufferEXT");
				glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffersEXT");
				glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffersEXT");
				glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatusEXT");
				glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)wglGetProcAddress("glFramebufferTexture1DEXT");
				glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2DEXT");
				glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)wglGetProcAddress("glFramebufferTexture3DEXT");
				glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbufferEXT");
				glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
				glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmapEXT");
			}
			else
			{
				//log("OpenGL: No framebuffers extension is supported");
				//log("OpenGL: Any call to Fbo will crash!");
				return false;
			}
	}
	return true;
}
#endif

bool CocosGLCanvas::InitGlew()
{
	wxGLCanvas::SetCurrent(*m_context);
	GLenum err = glewInit();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
	GLenum GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		//std::cerr << "Error:" << glewGetString(err) << std::endl;
		//const GLubyte* String = glewGetErrorString(err);
		wxMessageBox("GLEW is not initialized");
		return false;
	}
	bool shadersAllow = GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader;
	if (!shadersAllow)
	{
		wxMessageBox("Error: shaderes not allow");
	}

	if (!glewIsSupported("GL_VERSION_2_0"))
	{
		wxMessageBox("Error: openg 2 not supported");
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (glew_dynamic_binding() == false)
	{
		wxMessageBox("No OpenGL framebuffer support");
		return false;
	}
#endif

#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)

	return true;
}

bool initialized = false;
void CocosGLCanvas::OnPaint(wxPaintEvent & event)
{
	wxPaintDC(this);
    if(!initialized){
        InitGl();
        initialized=true;
    }
	auto size = GetClientSize();
	//setFrameSize(size.x, size.y);
	setViewPortInPoints(0, 0, size.x, size.y);
	cocos2d::Director::getInstance()->mainLoop();
	GLenum error = glGetError();
	if (error != GLEW_OK) {
		wxMessageBox("Cocos2d-x internal error");
	}
}

void CocosGLCanvas::OnKeyDown(wxKeyEvent& event)
{   
	switch (event.GetKeyCode())
	{
	case WXK_SPACE:
		if (_drawTimer.IsRunning())
			_drawTimer.Stop();
		else
			_drawTimer.Start(25);
		break;

	default:
		event.Skip();
		return;
	}
}

void CocosGLCanvas::OnDrawTimer(wxTimerEvent& WXUNUSED(event))
{
	Refresh(false);//redraw view
}

CocosGLCanvas::CocosGLCanvas(wxWindow *parent, int *attribList)
// With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
// flag should always be set, because even making the canvas smaller should
// be followed by a paint event that updates the entire canvas with new
// viewport settings.
	: wxGLCanvas(parent, wxID_ANY, attribList,
		wxDefaultPosition, wxDefaultSize,
		wxFULL_REPAINT_ON_RESIZE),
	_drawTimer(this, DrawTimer)
{
	m_context = new wxGLContext(this);
}

bool CocosGLCanvas::InitGl()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	cocos2d::GLView::setGLContextAttrs(glContextAttrs);

	auto director = cocos2d::Director::getInstance();
	while (!IsShown()) {};  // Force the Shown

	InitGlew();

	// initialize director
	auto glview = director->getOpenGLView();
	if (!glview) {
		setFrameSize(mediumResolutionSize.width, mediumResolutionSize.height);
		director->setOpenGLView(this);
	}

	setDesignResolutionSize(mediumResolutionSize.width, mediumResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// create a scene. it's an autorelease object
	auto scene = EditorScene::createScene();
	director->runWithScene(scene);
	GLenum error = glGetError();
	// run
	_drawTimer.Start(25);
	return true;
}

bool CocosGLCanvas::isOpenGLReady()
{
	return IsShown();
}

void CocosGLCanvas::end()
{
}

void CocosGLCanvas::swapBuffers()
{
	SwapBuffers();
}

void CocosGLCanvas::setFrameSize(float width, float height)
{
	_retinaFactor = 1; _frameZoomFactor = 1;
	cocos2d::Size currentsize = cocos2d::GLView::getFrameSize();
	if (width > 50 && height > 50 && (currentsize.width != width || currentsize.height != height)) {
		cocos2d::GLView::setFrameSize(width, height);
	}
}

void CocosGLCanvas::setIMEKeyboardState(bool bOpen)
{
}

void CocosGLCanvas::setViewPortInPoints(float x, float y, float w, float h)
{
	_retinaFactor = 1; _frameZoomFactor = 1;
	cocos2d::experimental::Viewport vp((float)(x * _scaleX * _retinaFactor * _frameZoomFactor + _viewPortRect.origin.x * _retinaFactor * _frameZoomFactor),
		(float)(y * _scaleY * _retinaFactor  * _frameZoomFactor + _viewPortRect.origin.y * _retinaFactor * _frameZoomFactor),
		(float)(w * _scaleX * _retinaFactor * _frameZoomFactor),
		(float)(h * _scaleY * _retinaFactor * _frameZoomFactor));
	cocos2d::Camera::setDefaultViewport(vp);
}

void CocosGLCanvas::setScissorInPoints(float x, float y, float w, float h)
{
	cocos2d::GLView::setScissorInPoints(x, y, w, h);
}

cocos2d::Rect CocosGLCanvas::getScissorRect() const
{
	return cocos2d::Rect();
}
