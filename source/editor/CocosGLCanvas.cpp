#include "stdafx.h"
#include "CocosGLCanvas.h"
#include <iostream>
#include "EditorScene3D.h"

static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
bool _initialized = false;
bool _shown = false;
wxSize _previousSize;

enum
{
	DrawTimer = wxID_HIGHEST + 1
};

wxBEGIN_EVENT_TABLE(CocosGLCanvas, wxGLCanvas)

EVT_PAINT(CocosGLCanvas::OnPaint)
EVT_KEY_DOWN(CocosGLCanvas::OnKeyDown)
EVT_MOUSEWHEEL(CocosGLCanvas::OnMouseWheel)
EVT_MIDDLE_DOWN(CocosGLCanvas::OnMouseMiddleDown)
EVT_RIGHT_DOWN(CocosGLCanvas::OnMouseRightDown)
EVT_RIGHT_UP(CocosGLCanvas::OnMouseRightUp)
EVT_LEFT_DOWN(CocosGLCanvas::OnMouseLeftDown)
EVT_LEFT_UP(CocosGLCanvas::OnMouseLeftUp)
EVT_MIDDLE_UP(CocosGLCanvas::OnMouseMiddleUp)
EVT_MOTION(CocosGLCanvas::OnMouseMoveEvent)
EVT_TIMER(DrawTimer, CocosGLCanvas::OnDrawTimer)

wxEND_EVENT_TABLE()

static bool glew_dynamic_binding()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
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
#endif
	return true;
}

bool CocosGLCanvas::initGlew()
{
	wxGLCanvas::SetCurrent(*m_context);
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
	GLenum GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
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
		wxMessageBox("Error: opengl 2 not supported");
	}

	if (glew_dynamic_binding() == false)
	{
		wxMessageBox("No OpenGL framebuffer support");
		return false;
	}
#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)

	return true;
}

void CocosGLCanvas::OnPaint(wxPaintEvent & event)
{
	wxPaintDC(this);
	auto size = GetClientSize();

	if (!_initialized)
	{
		initGl();
		_initialized = true;
	}

	if (size.x > 50 && size.y > 50 && !_shown)
	{
		onResizeCanvas(size.x, size.y);
		_shown = true;
	}
	else
	{
		//on resize
		if (_previousSize.x != size.x || _previousSize.y != size.y)
		{
			onResizeCanvas(size.x, size.y);
		}
	}

	//draw on context using cocos
	cocos2d::Director::getInstance()->mainLoop();

	_previousSize = size;

	//check or errors
	GLenum error = glGetError();
	if (error != GLEW_OK) {
		wxMessageBox("Cocos2d-x internal error");
	}
}

void CocosGLCanvas::OnKeyDown(wxKeyEvent& event)
{
	_controller->OnKeyDown(event);
}

void CocosGLCanvas::OnMouseWheel(wxMouseEvent & event)
{
	_controller->OnMouseWheel(event);
}

void CocosGLCanvas::OnDrawTimer(wxTimerEvent& WXUNUSED(event))
{
	//redraw view
	Refresh(true);
}

void CocosGLCanvas::OnMouseLeftDown(wxMouseEvent & event)
{
	_controller->OnMouseLeftDown(event);
}

void CocosGLCanvas::OnMouseLeftUp(wxMouseEvent & event)
{
	_controller->OnMouseLeftUp(event);
}

void CocosGLCanvas::OnMouseMiddleDown(wxMouseEvent & event)
{
	_controller->OnMouseMiddleDown(event);
}

void CocosGLCanvas::OnMouseMiddleUp(wxMouseEvent & event)
{
	_controller->OnMouseMiddleUp(event);
}

void CocosGLCanvas::OnMouseRightDown(wxMouseEvent & event)
{
	_controller->OnMouseRightDown(event);
}

void CocosGLCanvas::OnMouseRightUp(wxMouseEvent & event)
{
	_controller->OnMouseRightUp(event);
}

void CocosGLCanvas::OnMouseMoveEvent(wxMouseEvent & event)
{
	_controller->OnMouseMoveEvent(event);
}

CocosGLCanvas::CocosGLCanvas(wxWindow *parent, AbstractCocosGLCanvasController* controller, int *attribList)
	: wxGLCanvas(parent, wxID_ANY, attribList,
		wxDefaultPosition, wxDefaultSize,
		wxFULL_REPAINT_ON_RESIZE),
	_drawTimer(this, DrawTimer)
{
	m_context = new wxGLContext(this);
	_frameZoomFactor = 1.0f;
	_controller = controller;
	_controller->SetParent(this);
}

bool CocosGLCanvas::initGl()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	cocos2d::GLView::setGLContextAttrs(glContextAttrs);

	auto director = cocos2d::Director::getInstance();
	//while (!IsShown()) {};  // Force the Shown

	initGlew();

	// initialize director
	auto glview = director->getOpenGLView();
	if (!glview) {
		setFrameSize(mediumResolutionSize.width, mediumResolutionSize.height);
		director->setOpenGLView(this);
	}

	setDesignResolutionSize(mediumResolutionSize.width, mediumResolutionSize.height, ResolutionPolicy::NO_BORDER);

	_controller->InitController();

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 30);

	// create a scene. it's an autorelease object
	auto scene = _controller->GetCurrentScene();
	director->runWithScene(scene);

	// run
	//getAnimationInterval is for 1s, get for 1ms
	//float callsPerMili = director->getAnimationInterval() * 1000;
	//not necessari to render every time just when changes are detected
	//_drawTimer.Start(callsPerMili);
	return true;
}

void CocosGLCanvas::onResizeCanvas(float width, float height)
{
	//resize
	if (width && height && _resolutionPolicy != ResolutionPolicy::UNKNOWN)
	{
		cocos2d::Size baseDesignSize = _designResolutionSize;
		ResolutionPolicy baseResolutionPolicy = _resolutionPolicy;

		int frameWidth = width / _frameZoomFactor;
		int frameHeight = height / _frameZoomFactor;
		setFrameSize(frameWidth, frameHeight);
		setDesignResolutionSize(baseDesignSize.width, baseDesignSize.height, baseResolutionPolicy);
		cocos2d::Director::getInstance()->setViewport();
	}
}

bool CocosGLCanvas::isOpenGLReady()
{
	return _initialized;
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