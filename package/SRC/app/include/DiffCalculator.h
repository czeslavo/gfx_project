#pragma once

#include <memory>
#include <wx/wx.h>
#include "CompareController.h"

namespace diff
{

/**
 * Helper function for generating images diff image. It calculates RGB differences per each pixel and if the sum of
 * them is higher than the threshold, the pixel is marked as the difference.
 *
 * \param firstImage
 * \param secondImage
 * \param threshold if RGB difference will be higher than it, it will be considered as real difference
 * \param useImageAsBg flag telling if we should draw an image as a diff background
 * \param whichImage tells which image should be drawn as a background (left or right)
 * \param bg background color
 * \param fg foreground color (diff)
 */
wxImage getImagesDiff(wxImage firstImage, wxImage secondImage, int threshold, bool useImageAsBg,
                      ImageIdentity whichImage, const wxColour bg = *wxBLACK, const wxColour fg = *wxRED);


}
