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
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Window example"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 18, 74, 90, 90, false, wxT("Sans") ) );
	
	bSizer1->Add( m_staticText1, 0, wxALL, 5 );
	
	m_button1 = new wxButton( this, wxID_ANY, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button1, 1, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::onExitButtonClick ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::onExitButtonClick ), NULL, this );
	
}
