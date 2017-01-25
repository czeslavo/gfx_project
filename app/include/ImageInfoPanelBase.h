#pragma once

#include <wx/wx.h>

namespace gui
{

/**
 * Base class for ImageInfoPanel. Creates controls in its constructor.
 */
class ImageInfoPanelBase : public wxPanel
{
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
