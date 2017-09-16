#pragma once
#include "stdafx.h"
#include "MainFrameWrapper.h"
#include "CocosGLCanvas.h"

// Define a new application type
class MyApp : public wxApp, private cocos2d::Application
{
public:
	MyApp() {}

	// virtual wxApp methods
	virtual bool OnInit() override;
	virtual int OnExit() override;


	/**
	@brief    Implement Director and Scene init code here.
	@return true    Initialize success, app continue.
	@return false   Initialize failed, app terminate.
	*/
	virtual bool applicationDidFinishLaunching();

	/**
	@brief  Called when the application moves to the background
	@param  the pointer of the application
	*/
	virtual void applicationDidEnterBackground();

	/**
	@brief  Called when the application reenters the foreground
	@param  the pointer of the application
	*/
	virtual void applicationWillEnterForeground();
};

MyApp& GetCurrentApp();
