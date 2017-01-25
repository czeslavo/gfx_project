#include "DiffFrameBase.h"

DiffFrameBase::DiffFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 800,600 ), wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	panel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );

	bSizer16->Add( panel, 1, wxEXPAND | wxALL, 5 );


	bSizer12->Add( bSizer16, 5, wxEXPAND, 5 );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );


	bSizer12->Add( bSizer17, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 5, 0, 15 );
	fgSizer1->AddGrowableCol( 3 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxBoxSizer* bSizer251;
	bSizer251 = new wxBoxSizer( wxVERTICAL );

	m_staticText91 = new wxStaticText( this, wxID_ANY, wxT("Difference threshold"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText91->Wrap( -1 );
	bSizer251->Add( m_staticText91, 0, wxALL, 5 );

	thresholdText = new wxTextCtrl( this, wxID_ANY, "100", wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !thresholdText->HasFlag( wxTE_MULTILINE ) )
	{
	thresholdText->SetMaxLength(6);
	}
	#else
	thresholdText->SetMaxLength(6);
	#endif
	bSizer251->Add( thresholdText, 0, wxALL|wxEXPAND, 5 );


	fgSizer1->Add( bSizer251, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer261;
	bSizer261 = new wxBoxSizer( wxVERTICAL );

	m_staticText111 = new wxStaticText( this, wxID_ANY, wxT("Difference color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	bSizer261->Add( m_staticText111, 0, wxALL, 5 );

	fgColorPicker = new wxButton( this, wxID_ANY, wxT("Change diff color"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer261->Add( fgColorPicker, 0, wxALL|wxEXPAND, 5 );


	fgSizer1->Add( bSizer261, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer291;
	bSizer291 = new wxBoxSizer( wxVERTICAL );

	m_staticText121 = new wxStaticText( this, wxID_ANY, wxT("Background color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText121->Wrap( -1 );
	bSizer291->Add( m_staticText121, 0, wxALL, 5 );

	bgColorPicker = new wxButton( this, wxID_ANY, wxT("Change background color"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer291->Add( bgColorPicker, 0, wxALL|wxEXPAND, 5 );


	fgSizer1->Add( bSizer291, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer301;
	bSizer301 = new wxBoxSizer( wxVERTICAL );

	drawImageCheckBox = new wxCheckBox( this, wxID_ANY, wxT("Draw image as background"), wxDefaultPosition, wxDefaultSize, 0 );
	drawImageCheckBox->SetValue(true);
	bSizer301->Add( drawImageCheckBox, 0, wxALL, 5 );

	drawFirstRadioButton = new wxRadioButton( this, wxID_ANY, wxT("First image"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer301->Add( drawFirstRadioButton, 0, wxLEFT, 15 );

	drawSecondRadioButton = new wxRadioButton( this, wxID_ANY, wxT("Second image"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer301->Add( drawSecondRadioButton, 0, wxLEFT, 15 );


	fgSizer1->Add( bSizer301, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );

	generateButton = new wxButton( this, wxID_ANY, wxT("Generate"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( generateButton, 0, wxALL, 5 );

	saveButton = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	saveButton->Enable( false );

	bSizer19->Add( saveButton, 0, wxALL, 5 );


	fgSizer1->Add( bSizer19, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT, 5 );


	bSizer12->Add( fgSizer1, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer12 );
	this->Layout();
	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );
}

DiffFrameBase::~DiffFrameBase()
{
}
