// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include "stdafx.h"
#include "MyApp.h"
#include "EditorScene3D.h"

wxIMPLEMENT_APP(MyApp);

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

MyApp& GetCurrentApp() {
	return wxGetApp();
}
MainFrameWrapper *frame;

bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	//needed on win32
	cocos2d::FileUtils::getInstance()->addSearchPath("Resources");

	frame = new MainFrameWrapper(false);
	frame->Show(true);
	return true;
}

int MyApp::OnExit()
{
	return wxApp::OnExit();
}

static int register_all_packages()
{
	return 0; //flag for packages manager
}

void MyApp::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}

bool MyApp::applicationDidFinishLaunching()
{
	register_all_packages();
	return true;
}

void MyApp::applicationDidEnterBackground()
{
	cocos2d::Director::getInstance()->stopAnimation();
}

void MyApp::applicationWillEnterForeground()
{
	cocos2d::Director::getInstance()->startAnimation();
}