#include "ImageService.h"

namespace core
{

void ImageService::loadImageFromFileAsMaster(const std::string& path)
{
    originalImage.LoadFile(path);
    initialSize.width = originalImage.GetWidth();
    initialSize.height = originalImage.GetHeight();

    isImageLoaded = originalImage.IsOk();

    resetProcessed();
}

void ImageService::loadImageFromFileAsSlave(const std::string& path,
                                            const std::pair<int, int> masterSize)
{
    originalImage.LoadFile(path);
    initialSize.width = originalImage.GetWidth();
    initialSize.height = originalImage.GetHeight();

    if (not hasTheSameAspectRatio(masterSize))
    {
        originalImage = wxImage();
        return;
    }

    scaleToSize(masterSize);

    isImageLoaded = originalImage.IsOk();
    resetProcessed();
}

bool ImageService::hasTheSameAspectRatio(const std::pair<int, int> size)
{
    const float width = originalImage.GetWidth();
    const float height = originalImage.GetHeight();

    constexpr float epsilon{0.001};
    return static_cast<float>(size.first) / static_cast<float>(size.second) -
           width / height <= epsilon;
}

void ImageService::scaleToSize(const std::pair<int, int> size)
{
    originalImage.Rescale(size.first, size.second);
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

std::pair<int, int> ImageService::getInitialSize() const
{
    return std::make_pair(initialSize.width, initialSize.height);
}

int ImageService::getZoom() const
{
    if (not isImageLoaded)
        return 0;

    return zoom;
}

int ImageService::getInitialZoom() const
{
    if (not isImageLoaded)
        return 0;

    constexpr float percent{100.f};
    return static_cast<float>(processedImage.GetWidth()) / static_cast<float>(initialSize.width) * percent;
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
    if (not isImageLoaded)
        return;

    this->zoom = zoom;
    scale(zoom);
}

void ImageService::makeMaster()
{
    isMaster = true;
}

}
