#pragma once

#include <memory>
#include <wx/wx.h>
#include "CompareController.h"

namespace diff
{

wxImage getImagesDiff(wxImage firstImage, wxImage secondImage, int threshold, bool useImageAsBg,
                      ImageIdentity whichImage, const wxColour bg = *wxBLACK, const wxColour fg = *wxRED);


}
