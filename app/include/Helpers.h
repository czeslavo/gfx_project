#pragma once

#include <wx/wx.h>

namespace helpers
{

wxBitmap getFittedBitmap(const wxImage& image, wxSize size);

wxPoint getCenterPosition(wxSize size, wxSize bitmapSize);

}
