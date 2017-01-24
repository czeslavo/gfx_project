#include "DiffCalculator.h"

namespace diff
{

wxImage getImagesDiff(wxImage firstImage, wxImage secondImage, int threshold,
                      const wxColour bg, const wxColour fg)
{
    wxImage diff = firstImage.Copy();

    for (std::size_t x = 0; x < firstImage.GetWidth(); ++x)
    for (std::size_t y = 0; y < firstImage.GetHeight(); ++y)
    {
        const int rDiff = std::abs(firstImage.GetRed(x, y) - secondImage.GetRed(x, y));
        const int gDiff = std::abs(firstImage.GetGreen(x, y) - secondImage.GetGreen(x, y));
        const int bDiff = std::abs(firstImage.GetBlue(x, y) - secondImage.GetBlue(x, y));

        const int totalDiff = rDiff + gDiff + bDiff;

        if (totalDiff > threshold)
            diff.SetRGB(x, y, fg.Red(), fg.Green(), fg.Blue());
    }

    return diff;
}

}
