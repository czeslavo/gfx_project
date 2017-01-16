///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	toolBar->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	newComparisonButton = toolBar->AddTool( wxID_ANY, wxT("New comparison"), wxBitmap( wxT("icons/new.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Start new comparison"), wxEmptyString, NULL ); 
	
	toolBar->AddSeparator(); 
	
	diffButton = toolBar->AddTool( wxID_ANY, wxT("New comparison"), wxBitmap( wxT("icons/diff.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Generate diff"), wxEmptyString, NULL ); 
	
	cropButton = toolBar->AddTool( wxID_ANY, wxT("New comparison"), wxBitmap( wxT("icons/crop.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Crop and save"), wxEmptyString, NULL ); 
	
	toolBar->AddSeparator(); 
	
	batchButton = toolBar->AddTool( wxID_ANY, wxT("New comparison"), wxBitmap( wxT("icons/batch.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Batch diff generator"), wxEmptyString, NULL ); 
	
	toolBar->Realize(); 
	
	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_filePicker2 = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select an image"), wxT("*.*"), wxDefaultPosition, wxSize( 300,-1 ), wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL );
	m_filePicker2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	bSizer8->Add( m_filePicker2, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( bSizer8, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_filePicker21 = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select an image"), wxT("*.*"), wxDefaultPosition, wxSize( 300,-1 ), wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL );
	m_filePicker21->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	bSizer11->Add( m_filePicker21, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( bSizer11, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer4->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	m_scrolledWindow1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
	
	bSizer5->Add( m_scrolledWindow1, 1, wxALL|wxEXPAND, 5 );
	
	m_scrolledWindow2 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	m_scrolledWindow2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_GRAYTEXT ) );
	
	bSizer5->Add( m_scrolledWindow2, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer4->Add( bSizer5, 5, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel7 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer6->Add( m_panel7, 1, wxEXPAND | wxALL, 5 );
	
	m_panel8 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer6->Add( m_panel8, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer4->Add( bSizer6, 2, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer4 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}
