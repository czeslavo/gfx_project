#pragma once

#include <memory>
#include <wx/wx.h>

namespace diff
{

wxImage getImagesDiff(wxImage firstImage, wxImage secondImage, int threshold,
                      const wxColour bg = *wxBLACK, const wxColour fg = *wxRED);


}
