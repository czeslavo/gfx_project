#pragma once

#include <wx/wx.h>
#include <wx/colour.h>
#include <wx/clrpicker.h>

class DiffFrameBase : public wxFrame
{
    private:

    protected:
        wxPanel* panel;
        wxStaticText* m_staticText91;
        wxTextCtrl* thresholdText;
        wxStaticText* m_staticText111;
        wxButton* fgColorPicker;
        wxStaticText* m_staticText121;
        wxButton* bgColorPicker;
        wxCheckBox* drawImageCheckBox;
        wxRadioButton* drawFirstRadioButton;
        wxRadioButton* drawSecondRadioButton;
        wxButton* generateButton;
        wxButton* saveButton;
        wxStatusBar* statusBar;

    public:

        DiffFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Generate images diff"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

        ~DiffFrameBase();

};

