#pragma once

#include <memory>
#include <wx/wx.h>

namespace core
{

class ImageService
{
public:
    void loadImageFromFile(const std::string& path);

    wxBitmap getProcessedBitmap() const;
    wxBitmap getOriginalBitmap() const;

    std::pair<int, int> getOriginalSize() const;
    int getZoom() const;
    void resetProcessed();


private:
    wxBitmap getBitmap(std::shared_ptr<wxImage> image) const;

    bool isImageLoaded{false};

    std::shared_ptr<wxImage> originalImage{nullptr};
    std::shared_ptr<wxImage> processedImage{nullptr};
};

}
