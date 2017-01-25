#pragma once

#include <wx/wx.h>

namespace helpers
{

/*
 * Fits the image to a given size and returns a bitmap of that fit.
 */
wxBitmap getFittedBitmap(const wxImage& image, wxSize size);

/*
 * Calculates the position in which the image should be drawn to be placed in the panel center.
 */
wxPoint getCenterPosition(wxSize size, wxSize bitmapSize);

}
