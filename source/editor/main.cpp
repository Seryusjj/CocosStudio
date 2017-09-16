// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include "stdafx.h"
#include "MyApp.h"
#include "EditorScene3D.h"


#if WIN32
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

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

	//change application working dir or current dir to make relative paths to images work
	wxString fileLocation = wxStandardPaths::Get().GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath();
	wxSetWorkingDirectory(fileLocation);

	//wxInitAllImageHandlers();
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