#pragma once

#include <memory>
#include <wx/wx.h>

namespace core
{

    /*
     * Class which manages a single image. It has stored the original image, its intial size and also stores
     * a processed image, which is used for drawing it on the panel.
     */
class ImageService
{
public:
    /*
     * Loads the image as a master.
     */
    void loadImageFromFileAsMaster(const std::string& path);

    /*
     * Loads image as a slave, which means that it has to has the same aspect ratio as the master, and if it has,
     * it's scaled to be the same size.
     */
    void loadImageFromFileAsSlave(const std::string& path, const std::pair<int, int> masterSize);

    /*
     * Gets the current processed bitmap.
     */
    wxBitmap getProcessedBitmap() const;

    /*
     * Gets the original bitmap.
     */
    wxBitmap getOriginalBitmap() const;

    /*
     * Gets the original image copy.
     */
    wxImage getOriginalImage() const;

    /*
     * Gets original image size.
     */
    std::pair<int, int> getOriginalSize() const;

    /*
     * Gets initial image size (it differs from original since an image which is slave can have other initial size,
     * and then it's scaled to the master and it becomes its "original size").
     */
    std::pair<int, int> getInitialSize() const;

    /*
     * Gets the current zoom of the image.
     */
    int getZoom() const;

    /*
     * Gets initial zoom of the image.
     */
    int getInitialZoom() const;

    /*
     * Sets zoom to a given value.
     */
    void setZoom(int zoom);

    /*
     * Resets the processed image. It's replaced with original image copy.
     */
    void resetProcessed();

    /*
     * Reset the whole image. It means that the original and processed images are assigned to the empty wxImages.
     */
    void reset();

    /*
     * Make the image master.
     */
    void makeMaster();

    /*
     * Scale image to a given zoom.
     */
    void scale(int zoom);

    /*
     * Check if the image is properly loaded.
     */
    bool isLoaded() const;

private:
    /*
     * Checks if the image has the same aspect ratio a given size.
     */
    bool hasTheSameAspectRatio(const std::pair<int, int> size);

    /*
     * Scales the image to fit the given size - used for scaling slaves.
     */
    void scaleToSize(const std::pair<int, int> size);


    /*
     * Gets bitmap of the image.
     */
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
