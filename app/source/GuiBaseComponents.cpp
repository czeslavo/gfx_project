///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ImageComparePanel.h"
#include "ImageInfoPanel.h"

#include "GuiBaseComponents.h"

///////////////////////////////////////////////////////////////////////////
namespace gui
{

ImagesComparerFrameBase::ImagesComparerFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	toolBar->SetBackgroundColour( wxColour( 240, 240, 240 ) );

	newComparisonButton = toolBar->AddTool( wxID_ANY, wxT("New comparison"), wxBitmap( wxT("icons/new.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Start new comparison"), wxEmptyString, NULL );

	toolBar->AddSeparator();

	diffButton = toolBar->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("icons/diff.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Generate diff"), wxEmptyString, NULL );

	cropButton = toolBar->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("icons/crop.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Crop and save"), wxEmptyString, NULL );

	toolBar->AddSeparator();

	batchButton = toolBar->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("icons/batch.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Batch diff generator"), wxEmptyString, NULL );

	toolBar->Realize();

	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	leftFilePicker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select an image"), wxT("*.*"), wxDefaultPosition, wxSize( 300,-1 ), wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL );
	leftFilePicker->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	bSizer8->Add( leftFilePicker, 0, wxALL|wxEXPAND, 5 );


	bSizer3->Add( bSizer8, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	rightFilePicker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select an image"), wxT("*.*"), wxDefaultPosition, wxSize( 300,-1 ), wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL );
	rightFilePicker->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	bSizer11->Add( rightFilePicker, 0, wxALL|wxEXPAND, 5 );


	bSizer3->Add( bSizer11, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer4->Add( bSizer3, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	leftImagePanel = new ImageComparePanel( this);
	bSizer5->Add( leftImagePanel, 1, wxEXPAND | wxALL, 5 );

	rightImagePanel = new ImageComparePanel( this);
	bSizer5->Add( rightImagePanel, 1, wxEXPAND | wxALL, 5 );


	bSizer4->Add( bSizer5, 5, wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	leftPanel = new ImageInfoPanel( this);
	bSizer6->Add( leftPanel, 1, wxEXPAND | wxALL, 5 );

	rightPanel = new ImageInfoPanel( this);
	bSizer6->Add( rightPanel, 1, wxEXPAND | wxALL, 5 );


	bSizer4->Add( bSizer6, 2, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();

	this->Centre( wxBOTH );
}

ImagesComparerFrameBase::~ImagesComparerFrameBase()
{
}

ImageInfoPanelBase::ImageInfoPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );

	zoomLabel = new wxStaticText( this, wxID_ANY, wxT("Zoom:"), wxDefaultPosition, wxDefaultSize, 0 );
	zoomLabel->Wrap( -1 );
	bSizer14->Add( zoomLabel, 0, wxALL, 5 );

	zoomText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !zoomText->HasFlag( wxTE_MULTILINE ) )
	{
	zoomText->SetMaxLength( 6 );
	}
	#else
	zoomText->SetMaxLength( 6 );
	#endif
	bSizer14->Add( zoomText, 0, 0, 5 );


	bSizer13->Add( bSizer14, 1, wxALIGN_LEFT|wxALL, 5 );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );

	sizeLabel = new wxStaticText( this, wxID_ANY, wxT("Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	sizeLabel->Wrap( -1 );
	bSizer17->Add( sizeLabel, 0, wxALL, 5 );

	sizeText = new wxStaticText( this, wxID_ANY, wxT("100 x 100 px"), wxDefaultPosition, wxDefaultSize, 0 );
	sizeText->Wrap( -1 );
	bSizer17->Add( sizeText, 0, wxALL, 5 );


	bSizer13->Add( bSizer17, 1, wxALL, 5 );


	this->SetSizer( bSizer13 );
	this->Layout();
	bSizer13->Fit( this );
}

ImageInfoPanelBase::~ImageInfoPanelBase()
{
}

}
