///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/splitter.h>
#include <wx/menu.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxSplitterWindow* splitPanleContainer;
		wxPanel* m_panel3;
		wxSplitterWindow* m_splitter4;
		wxScrolledWindow* m_scrolledWindow3;
		wxPanel* m_panel5;
		wxBitmapButton* m_bpButton1;
		wxPanel* m_panel6;
		wxPanel* m_panel4;
		wxSplitterWindow* m_splitter3;
		wxPanel* openGLContainer;
		wxScrolledWindow* m_scrolledWindow2;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxMenu* m_menu11;
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 733,479 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainFrame();
		
		void splitPanleContainerOnIdle( wxIdleEvent& )
		{
			splitPanleContainer->SetSashPosition( 165 );
			splitPanleContainer->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::splitPanleContainerOnIdle ), NULL, this );
		}
		
		void m_splitter4OnIdle( wxIdleEvent& )
		{
			m_splitter4->SetSashPosition( 251 );
			m_splitter4->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter4OnIdle ), NULL, this );
		}
		
		void m_splitter3OnIdle( wxIdleEvent& )
		{
			m_splitter3->SetSashPosition( 337 );
			m_splitter3->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter3OnIdle ), NULL, this );
		}
	
};

#endif //__MAINFRAME_H__
