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
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	splitPanleContainer = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE|wxSP_NOBORDER );
	splitPanleContainer->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::splitPanleContainerOnIdle ), NULL, this );
	splitPanleContainer->SetMinimumPaneSize( 50 );
	
	splitPanleContainer->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTIONTEXT ) );
	
	m_panel3 = new wxPanel( splitPanleContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel3->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOBK ) );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter4 = new wxSplitterWindow( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE );
	m_splitter4->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter4OnIdle ), NULL, this );
	m_splitter4->SetMinimumPaneSize( 100 );
	
	m_splitter4->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INACTIVECAPTIONTEXT ) );
	
	m_scrolledWindow3 = new wxScrolledWindow( m_splitter4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow3->SetScrollRate( 5, 5 );
	m_scrolledWindow3->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOBK ) );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );
	
	m_panel5 = new wxPanel( m_scrolledWindow3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_bpButton5 = new wxBitmapButton( m_panel5, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxBU_LEFT );
	m_bpButton5->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_SCROLLBAR ) );
	
	gSizer1->Add( m_bpButton5, 0, wxALL, 5 );
	
	
	m_panel5->SetSizer( gSizer1 );
	m_panel5->Layout();
	gSizer1->Fit( m_panel5 );
	bSizer51->Add( m_panel5, 1, wxALL|wxEXPAND, 0 );
	
	
	m_scrolledWindow3->SetSizer( bSizer51 );
	m_scrolledWindow3->Layout();
	bSizer51->Fit( m_scrolledWindow3 );
	m_panel6 = new wxPanel( m_splitter4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel6->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	
	m_panel6->SetSizer( bSizer5 );
	m_panel6->Layout();
	bSizer5->Fit( m_panel6 );
	m_splitter4->SplitHorizontally( m_scrolledWindow3, m_panel6, 183 );
	bSizer4->Add( m_splitter4, 1, wxEXPAND, 5 );
	
	
	m_panel3->SetSizer( bSizer4 );
	m_panel3->Layout();
	bSizer4->Fit( m_panel3 );
	m_panel4 = new wxPanel( splitPanleContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel4->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
	m_panel4->SetMinSize( wxSize( 50,50 ) );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	splitterEngineView = new wxSplitterWindow( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxSP_NOBORDER );
	splitterEngineView->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::splitterEngineViewOnIdle ), NULL, this );
	splitterEngineView->SetMinimumPaneSize( 50 );
	
	splitterEngineView->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	openGLContainer = new wxPanel( splitterEngineView, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_auiToolBar14 = new wxAuiToolBar( openGLContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT|wxAUI_TB_TEXT ); 
	m_auiToolBar14->SetBackgroundColour( wxColour( 192, 192, 192 ) );
	
	m_tool49 = m_auiToolBar14->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	m_tool50 = m_auiToolBar14->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	m_tool51 = m_auiToolBar14->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	m_tool52 = m_auiToolBar14->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	m_auiToolBar14->Realize(); 
	
	bSizer6->Add( m_auiToolBar14, 0, wxALL, 5 );
	
	
	openGLContainer->SetSizer( bSizer6 );
	openGLContainer->Layout();
	bSizer6->Fit( openGLContainer );
	m_panel7 = new wxPanel( splitterEngineView, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel7->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_auinotebook1 = new wxAuiNotebook( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_TAB_FIXED_WIDTH|wxAUI_NB_TAB_SPLIT );
	m_panel71 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_auinotebook1->AddPage( m_panel71, wxT("Scene"), true, wxNullBitmap );
	m_panel8 = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_auinotebook1->AddPage( m_panel8, wxT("Properties"), false, wxNullBitmap );
	
	bSizer8->Add( m_auinotebook1, 1, wxEXPAND | wxALL, 0 );
	
	
	m_panel7->SetSizer( bSizer8 );
	m_panel7->Layout();
	bSizer8->Fit( m_panel7 );
	splitterEngineView->SplitVertically( openGLContainer, m_panel7, 418 );
	bSizer41->Add( splitterEngineView, 1, wxEXPAND, 5 );
	
	
	m_panel4->SetSizer( bSizer41 );
	m_panel4->Layout();
	bSizer41->Fit( m_panel4 );
	splitPanleContainer->SplitVertically( m_panel3, m_panel4, 165 );
	bSizer1->Add( splitPanleContainer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar2 = new wxMenuBar( 0 );
	m_menu5 = new wxMenu();
	m_menu51 = new wxMenu();
	wxMenuItem* m_menu51Item = new wxMenuItem( m_menu5, wxID_ANY, wxT("MyMenu"), wxEmptyString, wxITEM_NORMAL, m_menu51 );
	m_menu5->Append( m_menu51Item );
	
	m_menubar2->Append( m_menu5, wxT("MyMenu") ); 
	
	m_menu6 = new wxMenu();
	m_menu61 = new wxMenu();
	wxMenuItem* m_menu61Item = new wxMenuItem( m_menu6, wxID_ANY, wxT("MyMenu"), wxEmptyString, wxITEM_NORMAL, m_menu61 );
	m_menu6->Append( m_menu61Item );
	
	m_menubar2->Append( m_menu6, wxT("MyMenu") ); 
	
	this->SetMenuBar( m_menubar2 );
	
	
	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}
