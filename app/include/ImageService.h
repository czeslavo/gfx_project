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

    wxImage getOriginalImage() const;

    std::pair<int, int> getOriginalSize() const;
    std::pair<int, int> getInitialSize() const;

    int getZoom() const;
    int getInitialZoom() const;
    void setZoom(int zoom);
    void resetProcessed();
    void reset();
    void makeMaster();

    void scale(int zoom);

    bool isLoaded() const;

private:
    bool hasTheSameAspectRatio(const std::pair<int, int> size);
    void scaleToSize(const std::pair<int, int> size);

    wxBitmap getBitmap(const wxImage& image) const;

    bool isImageLoaded{false};
    int zoom{100};

    struct {
        int width;
        int height;
    } initialSize;

    bool isMaster{false};

    wxImage originalImage{};
    wxImage processedImage{};
};

}
