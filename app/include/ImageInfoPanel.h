#pragma once

#include <memory>

#include "ImageService.h"
#include "ImageInfoPanelBase.h"

namespace gui
{

/*
 * Panels on which we show the image's zoom and size.
 */
class ImageInfoPanel : public ImageInfoPanelBase
{
public:
    ImageInfoPanel(wxWindow* parent);

    /*
     * Event handler for onPaint event. Draws the controls.
     */
    void onPaint(wxPaintEvent& event);

    /*
     * Draws the controls immediately.
     */
    void paintNow();

    /*
     * Registers image service of the given image.
     */
    void registerImageService(std::shared_ptr<core::ImageService> service);

    /*
     * Updates info for controls to display.
     */
    void updateInfo();

    /*
     * Sets size text value basing on image service.
     */
    void setSizeText();

    /*
     * Sets zoom value basing on image service.
     */
    void setZoomText();

private:
    /*
     * Registers all the event handlers of the panel.
     */
    void registerEventHandlers();

    std::shared_ptr<core::ImageService> imageService;
};

}
