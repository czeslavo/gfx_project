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
    void setZoom(int zoom);
    void resetProcessed();
    void reset();

    void scale(int zoom);

private:
    wxBitmap getBitmap(const wxImage& image) const;

    bool isImageLoaded{false};
    int zoom{100};

    wxImage originalImage{};
    wxImage processedImage{};
};

}
