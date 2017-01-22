///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIBASECOMPONENTS_H__
#define __GUIBASECOMPONENTS_H__

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
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

///////////////////////////////////////////////////////////////////////////

namespace gui
{
    class ImageComparePanel;
    class ImageInfoPanel;

	///////////////////////////////////////////////////////////////////////////////
	/// Class ImagesComparerFrameBase
	///////////////////////////////////////////////////////////////////////////////
	class ImagesComparerFrameBase : public wxFrame
	{
		private:

		protected:
			wxToolBar* toolBar;
			wxToolBarToolBase* newComparisonButton;
			wxToolBarToolBase* diffButton;
			wxToolBarToolBase* cropButton;
			wxToolBarToolBase* batchButton;
			wxStatusBar* statusBar;
			wxFilePickerCtrl* leftFilePicker;
			wxFilePickerCtrl* rightFilePicker;
			ImageComparePanel* leftImagePanel;
			ImageComparePanel* rightImagePanel;
			ImageInfoPanel* leftPanel;
			ImageInfoPanel* rightPanel;

		public:

			ImagesComparerFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Images comparer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 814,583 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );

			~ImagesComparerFrameBase();

	};

	///////////////////////////////////////////////////////////////////////////////
	/// Class ImageInfoPanelBase
	///////////////////////////////////////////////////////////////////////////////
	class ImageInfoPanelBase : public wxPanel
	{
		private:

		protected:
			wxStaticText* zoomLabel;
			wxTextCtrl* zoomText;
			wxStaticText* sizeLabel;
			wxStaticText* sizeText;

		public:

			ImageInfoPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
			~ImageInfoPanelBase();

	};

} // namespace gui

#endif //__GUIBASECOMPONENTS_H__