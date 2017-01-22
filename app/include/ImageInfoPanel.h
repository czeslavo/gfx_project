#pragma once

#include <memory>

#include "ImageService.h"
#include "ImageInfoPanelBase.h"

namespace gui
{

class ImageInfoPanel : public ImageInfoPanelBase
{
public:
    ImageInfoPanel(wxWindow* parent);

    void registerImageService(std::shared_ptr<core::ImageService> service);

private:
    std::shared_ptr<core::ImageService> imageService;

};

}
