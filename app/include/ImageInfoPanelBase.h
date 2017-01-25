#pragma once

#include <wx/wx.h>

namespace gui
{

class ImageInfoPanelBase : public wxPanel
{
    private:

    protected:
        wxStaticText* zoomLabel;
        wxStaticText* zoomText;
        wxStaticText* sizeLabel;
        wxStaticText* sizeText;

    public:

        ImageInfoPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
        ~ImageInfoPanelBase();

};

}
