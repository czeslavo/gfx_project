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

    void onPaint(wxPaintEvent& event);
    void paintNow();

    void registerImageService(std::shared_ptr<core::ImageService> service);

    void updateInfo();
    void setSizeText();
    void setZoomText();

private:
    void registerEventHandlers();

    std::shared_ptr<core::ImageService> imageService;

};

}
