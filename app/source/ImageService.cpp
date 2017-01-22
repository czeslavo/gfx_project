#include "ImageService.h"

namespace core
{

void ImageService::loadImageFromFile(const std::string& path)
{
    originalImage = std::make_shared<wxImage>(path);

    isImageLoaded = originalImage->IsOk();
}

}
