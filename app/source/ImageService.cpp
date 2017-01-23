#include "ImageService.h"

namespace core
{

void ImageService::loadImageFromFile(const std::string& path)
{
    originalImage.LoadFile(path);
    isImageLoaded = originalImage.IsOk();

    resetProcessed();
}

wxBitmap ImageService::getProcessedBitmap() const
{
    return getBitmap(processedImage);
}

wxBitmap ImageService::getOriginalBitmap() const
{
    return getBitmap(originalImage);
}

wxBitmap ImageService::getBitmap(const wxImage& image) const
{
    if (not isImageLoaded)
        return wxBitmap();

    return wxBitmap(image);
}


std::pair<int, int> ImageService::getOriginalSize() const
{
    if (not isImageLoaded)
        return {0, 0};

    return {
        originalImage.GetWidth(),
        originalImage.GetHeight()
    };
}

int ImageService::getZoom() const
{
    if (not isImageLoaded)
        return 0;

    return zoom;
}

void ImageService::resetProcessed()
{
    if (not isImageLoaded)
    {
        processedImage = wxImage();
        return;
    }

    processedImage = originalImage.Copy();
}

void ImageService::reset()
{
    originalImage = wxImage();
    processedImage = wxImage();
    isImageLoaded = false;
}

void ImageService::scale(int zoom)
{
    const auto size = originalImage.GetSize();

    constexpr float percent{100.f};
    const float factor = static_cast<float>(zoom) / percent;
    processedImage = originalImage.Scale(static_cast<float>(size.x) * factor, static_cast<float>(size.y) * factor);
}

void ImageService::setZoom(int zoom)
{
    this->zoom = zoom;
    scale(zoom);
}

}
