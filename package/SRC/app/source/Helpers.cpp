#include "Helpers.h"

namespace helpers
{

wxBitmap getFittedBitmap(const wxImage& image, wxSize size)
{
    const float imageAspectRatio = static_cast<float>(image.GetWidth()) / static_cast<float>(image.GetHeight());
    const float aspectRatio = static_cast<float>(size.x) / static_cast<float>(size.y);

    const int width = aspectRatio > imageAspectRatio ?
        image.GetWidth() * static_cast<float>(size.y) / image.GetHeight() :
        size.x;

    const int height = aspectRatio < imageAspectRatio ?
        image.GetHeight() * static_cast<float>(size.x) / image.GetWidth() :
        size.y;

    return wxBitmap(image.Scale(width, height));
}

wxPoint getCenterPosition(wxSize size, wxSize bitmapSize)
{
    return {
        (size.GetWidth() - bitmapSize.GetWidth()) / 2,
        (size.GetHeight() - bitmapSize.GetHeight()) / 2
    };
}

}
