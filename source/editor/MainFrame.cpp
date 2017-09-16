///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MainFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 64, 64, 64 ) );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_ALLOW_ACTIVE_PANE|wxAUI_MGR_DEFAULT|wxAUI_MGR_LIVE_RESIZE);
	
	m_panel_objects = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panel_objects, wxAuiPaneInfo() .Left() .PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).MinSize( wxSize( 200,200 ) ) );
	
	m_panel_resources = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panel_resources, wxAuiPaneInfo() .Left() .PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 50,67 ) ).MinSize( wxSize( 200,200 ) ) );
	
	m_notebook3 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_FIXEDWIDTH|wxNB_NOPAGETHEME|wxNO_BORDER );
	m_notebook3->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_notebook3->SetBackgroundColour( wxColour( 64, 64, 64 ) );
	
	m_mgr.AddPane( m_notebook3, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).CentrePane() );
	
	openGLContainer = new wxPanel( m_notebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	openGLContainer->SetBackgroundColour( wxColour( 64, 64, 64 ) );
	openGLContainer->SetMinSize( wxSize( 800,800 ) );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	
	openGLContainer->SetSizer( bSizer10 );
	openGLContainer->Layout();
	bSizer10->Fit( openGLContainer );
	m_notebook3->AddPage( openGLContainer, wxT("scene"), false );
	
	m_scrolledWindow_properties = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxNO_BORDER|wxVSCROLL );
	m_scrolledWindow_properties->SetScrollRate( 5, 5 );
	m_mgr.AddPane( m_scrolledWindow_properties, wxAuiPaneInfo() .Right() .PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).MinSize( wxSize( 200,200 ) ) );
	
	
	m_mgr.Update();
	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
	m_mgr.UnInit();
	
}
