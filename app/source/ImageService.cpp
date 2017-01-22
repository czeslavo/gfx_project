#include "ImageService.h"

namespace core
{

void ImageService::loadImageFromFile(const std::string& path)
{
    try
    {
        originalImage = std::make_shared<wxImage>(path);
    }
    catch (const std::exception& e)
    {

    }
    isImageLoaded = originalImage->IsOk();

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

wxBitmap ImageService::getBitmap(std::shared_ptr<wxImage> image) const
{
    if (not isImageLoaded)
        return wxBitmap();

    return wxBitmap(*image);
}


std::pair<int, int> ImageService::getOriginalSize() const
{
    if (not isImageLoaded)
        return {0, 0};

    return {
        originalImage->GetWidth(),
        originalImage->GetHeight()
    };
}

int ImageService::getZoom() const
{
    if (not isImageLoaded)
        return 0;

    return originalImage->GetWidth() / processedImage->GetWidth();
}

void ImageService::resetProcessed()
{
    if (not isImageLoaded)
    {
        processedImage = std::make_shared<wxImage>();
        return;
    }

    processedImage = std::make_shared<wxImage>(originalImage->Copy());
}

}
