#include "ImageComparePanel.h"

namespace gui
{

ImageComparePanel::ImageComparePanel(wxWindow* parent)
    : wxPanel(parent)
{

}

void ImageComparePanel::registerImageService(std::shared_ptr<core::ImageService> service)
{
    imageService = service;
}


}
