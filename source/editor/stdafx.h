// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#if LINUX
	
	#include <functional>
	
	
	#include "cocos2d.h"
	#include <wx/aui/aui.h>
	#include <wx/grid.h>
	#include <wx/treectrl.h>
	#include <wx/stdpaths.h>
	#include <wx/artprov.h>
	#include <wx/xrc/xmlres.h>
	#include <wx/panel.h>
	#include <wx/gdicmn.h>
	#include <wx/font.h>
	#include <wx/colour.h>
	#include <wx/settings.h>
	#include <wx/string.h>
	#include <wx/sizer.h>
	#include <wx/scrolwin.h>
	#include <wx/splitter.h>
	#include <wx/bitmap.h>
	#include <wx/image.h>
	#include <wx/icon.h>
	#include <wx/menu.h>
	#include <wx/aui/auibook.h>
	#include <wx/frame.h>
	#include <wx/wx.h>
	#include <wx/glcanvas.h>
	#include <wx/timer.h>
	#include <wx/dcmemory.h>
	#include <wx/dcclient.h>
	#include <wx/statusbr.h>
	
#endif

#if WIN32
	#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
	
	// Windows Header Files:
	#include <windows.h>
	#include <tchar.h>
	//stl includes
	#include <functional>
	
	//cocos2d-x includes
	#define ssize_t SSIZE_T
		#include <WinSock2.h>
		#include <WS2tcpip.h>
		#include <Windows.h>
		#include "cocos2d.h"
	#undef ssize_t		
		//wxwidgets includes
	#define ssize_t wxInt32
		#include <wx/aui/aui.h>
		#include <wx/grid.h>
		#include <wx/treectrl.h>
		#include <wx/stdpaths.h>
		#include <wx/artprov.h>
		#include <wx/xrc/xmlres.h>
		#include <wx/panel.h>
		#include <wx/gdicmn.h>
		#include <wx/font.h>
		#include <wx/colour.h>
		#include <wx/settings.h>
		#include <wx/string.h>
		#include <wx/sizer.h>
		#include <wx/scrolwin.h>
		#include <wx/splitter.h>
		#include <wx/bitmap.h>
		#include <wx/image.h>
		#include <wx/icon.h>
		#include <wx/menu.h>
		#include <wx/aui/auibook.h>
		#include <wx/frame.h>
		#include <wx/wx.h>
		#include <wx/glcanvas.h>
		#include <wx/timer.h>
		#include <wx/dcmemory.h>
		#include <wx/dcclient.h>
		#include <wx/statusbr.h>
	#undef ssize_t
#endif



