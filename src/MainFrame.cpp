///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MainFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	splitPanleContainer = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
	splitPanleContainer->Connect(wxEVT_IDLE, wxIdleEventHandler(MainFrame::splitPanleContainerOnIdle), NULL, this);
	splitPanleContainer->SetMinimumPaneSize(50);

	splitPanleContainer->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTIONTEXT));

	m_panel3 = new wxPanel(splitPanleContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	m_splitter4 = new wxSplitterWindow(m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
	m_splitter4->Connect(wxEVT_IDLE, wxIdleEventHandler(MainFrame::m_splitter4OnIdle), NULL, this);
	m_splitter4->SetMinimumPaneSize(100);

	m_splitter4->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTIONTEXT));

	m_scrolledWindow3 = new wxScrolledWindow(m_splitter4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_scrolledWindow3->SetScrollRate(5, 5);
	m_scrolledWindow3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer(wxVERTICAL);

	m_panel5 = new wxPanel(m_scrolledWindow3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer(0, 2, 0, 0);

	m_bpButton1 = new wxBitmapButton(m_panel5, wxID_ANY, wxBitmap(cocos2d::FileUtils::getInstance()->fullPathForFilename("wxWidgetsResources/button_place_holder.bmp"), wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);

	m_bpButton1->SetBitmapDisabled(wxBitmap(cocos2d::FileUtils::getInstance()->fullPathForFilename("wxWidgetsResources/button_place_holder.bmp"), wxBITMAP_TYPE_ANY));
	m_bpButton1->SetBitmapSelected(wxBitmap(cocos2d::FileUtils::getInstance()->fullPathForFilename("wxWidgetsResources/button_place_holder.bmp"), wxBITMAP_TYPE_ANY));
	gSizer1->Add(m_bpButton1, 0, wxALL, 5);

	m_panel5->SetSizer(gSizer1);
	m_panel5->Layout();
	gSizer1->Fit(m_panel5);
	bSizer51->Add(m_panel5, 1, wxALL | wxEXPAND, 5);

	m_scrolledWindow3->SetSizer(bSizer51);
	m_scrolledWindow3->Layout();
	bSizer51->Fit(m_scrolledWindow3);
	m_panel6 = new wxPanel(m_splitter4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel6->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	m_panel6->SetSizer(bSizer5);
	m_panel6->Layout();
	bSizer5->Fit(m_panel6);
	m_splitter4->SplitHorizontally(m_scrolledWindow3, m_panel6, 251);
	bSizer4->Add(m_splitter4, 1, wxEXPAND, 5);

	m_panel3->SetSizer(bSizer4);
	m_panel3->Layout();
	bSizer4->Fit(m_panel3);
	m_panel4 = new wxPanel(splitPanleContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel4->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	m_panel4->SetMinSize(wxSize(50, 50));

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer(wxVERTICAL);

	m_splitter3 = new wxSplitterWindow(m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
	m_splitter3->Connect(wxEVT_IDLE, wxIdleEventHandler(MainFrame::m_splitter3OnIdle), NULL, this);
	m_splitter3->SetMinimumPaneSize(100);

	m_splitter3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTIONTEXT));

	openGLContainer = new wxPanel(m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	openGLContainer->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));

	wxBoxSizer* glSizer;
	glSizer = new wxBoxSizer(wxVERTICAL);

	openGLContainer->SetSizer(glSizer);
	openGLContainer->Layout();
	glSizer->Fit(openGLContainer);
	m_scrolledWindow2 = new wxScrolledWindow(m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_scrolledWindow2->SetScrollRate(5, 5);
	m_scrolledWindow2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));

	m_splitter3->SplitVertically(openGLContainer, m_scrolledWindow2, 337);
	bSizer41->Add(m_splitter3, 1, wxEXPAND, 5);

	m_panel4->SetSizer(bSizer41);
	m_panel4->Layout();
	bSizer41->Fit(m_panel4);
	splitPanleContainer->SplitVertically(m_panel3, m_panel4, 165);
	bSizer1->Add(splitPanleContainer, 1, wxEXPAND, 5);

	this->SetSizer(bSizer1);
	this->Layout();
	m_menubar1 = new wxMenuBar(0);
	m_menubar1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
	m_menubar1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));

	m_menu1 = new wxMenu();
	m_menu11 = new wxMenu();
	wxMenuItem* m_menu11Item = new wxMenuItem(m_menu1, wxID_ANY, wxT("MyMenu"), wxEmptyString, wxITEM_NORMAL, m_menu11);
	m_menu1->Append(m_menu11Item);

	m_menubar1->Append(m_menu1, wxT("MyMenu"));

	this->SetMenuBar(m_menubar1);

	this->Centre(wxBOTH);
}

MainFrame::~MainFrame()
{
}