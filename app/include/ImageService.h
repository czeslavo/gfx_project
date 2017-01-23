#pragma once

#include <memory>
#include <wx/wx.h>

namespace core
{

class ImageService
{
public:
    void loadImageFromFileAsMaster(const std::string& path);
    void loadImageFromFileAsSlave(const std::string& path, const std::pair<int, int> masterSize);

    wxBitmap getProcessedBitmap() const;
    wxBitmap getOriginalBitmap() const;
    std::pair<int, int> getOriginalSize() const;

    int getZoom() const;
    void setZoom(int zoom);
    void resetProcessed();
    void reset();
    void makeMaster();

    void scale(int zoom);

private:
    bool hasTheSameAspectRatio(const std::pair<int, int> size);
    void scaleToSize(const std::pair<int, int> size);

    wxBitmap getBitmap(const wxImage& image) const;

    bool isImageLoaded{false};
    int zoom{100};

    bool isMaster{false};

    wxImage originalImage{};
    wxImage processedImage{};
};

}
