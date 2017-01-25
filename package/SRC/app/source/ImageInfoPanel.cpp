#include "ImageInfoPanel.h"
#include "WindowPatch.h"

namespace gui
{

ImageInfoPanel::ImageInfoPanel(wxWindow* parent)
    : ImageInfoPanelBase(parent)
{
    registerEventHandlers();
}

void ImageInfoPanel::registerEventHandlers()
{
    Bind(wxEVT_PAINT, &ImageInfoPanel::onPaint, this);
}

void ImageInfoPanel::registerImageService(std::shared_ptr<core::ImageService> service)
{
    imageService = service;
}

void ImageInfoPanel::paintNow()
{
    wxWindow::Refresh();
}

void ImageInfoPanel::onPaint(wxPaintEvent& event)
{
    updateInfo();
}

void ImageInfoPanel::updateInfo()
{
    setSizeText();
    setZoomText();
}

void ImageInfoPanel::setSizeText()
{
    const auto size = imageService->getInitialSize();
    const std::string sizeString = std::to_string(size.first) + " x " + std::to_string(size.second) + " px";

    sizeText->SetLabelText(sizeString);
}

void ImageInfoPanel::setZoomText()
{
    const auto zoom = std::to_string(imageService->getInitialZoom());
    zoomText->SetLabelText(zoom);
}


}
