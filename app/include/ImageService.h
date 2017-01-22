#pragma once

#include <memory>
#include <wx/wx.h>

namespace core
{

class ImageService
{
public:
    void loadImageFromFile(const std::string& path);

private:
    bool isImageLoaded{false};

    std::shared_ptr<wxImage> originalImage{nullptr};
    std::shared_ptr<wxImage> processedImage{nullptr};
};

}
