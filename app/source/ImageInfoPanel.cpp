#include "ImageInfoPanel.h"

namespace gui
{

ImageInfoPanel::ImageInfoPanel(wxWindow* parent)
    : ImageInfoPanelBase(parent)
{
}

void ImageInfoPanel::registerImageService(std::shared_ptr<core::ImageService> service)
{
    imageService = service;
}

}
