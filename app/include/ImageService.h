#pragma once

#include <memory>
#include <wx/wx.h>

namespace core
{

enum class ImageFileType
{
    PNG,
    JPEG,
    TIFF,
    BMP
};

class ImageService
{
public:
    void loadImageFromFile(const std::string& path, ImageFileType fileType);

private:
    bool isImageLoaded{false};

    std::shared_ptr<wxImage> originalImage{nullptr};
    std::shared_ptr<wxImage> processedImage{nullptr};
};

}
