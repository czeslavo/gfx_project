///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/toolbar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/filepicker.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxToolBar* toolBar;
		wxToolBarToolBase* newComparisonButton; 
		wxToolBarToolBase* diffButton; 
		wxToolBarToolBase* cropButton; 
		wxToolBarToolBase* batchButton; 
		wxStatusBar* statusBar;
		wxFilePickerCtrl* m_filePicker2;
		wxFilePickerCtrl* m_filePicker21;
		wxScrolledWindow* m_scrolledWindow1;
		wxScrolledWindow* m_scrolledWindow2;
		wxPanel* m_panel7;
		wxPanel* m_panel8;
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Images comparer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 814,583 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~MainFrame();
	
};

#endif //__MAINFRAME_H__
