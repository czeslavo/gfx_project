#pragma once

#include <wx/wx.h>

#include "ImageService.h"
#include "SharedData.h"

namespace gui
{

/**
 * Panel in which we draw the images. There are two of them in the main window of the application.
 */
class ImageComparePanel : public wxPanel
{
public:
    ImageComparePanel(wxWindow* parent);

    /**
     * Registers image services.
     */
    void registerImageService(std::shared_ptr<core::ImageService> service);

    /**
     * Registers shared data.
     */
    void registerSharedData(std::shared_ptr<core::SharedData> data);

    /**
     * Registers second panel.
     */
    void registerSecondPanel(wxWindow* panel);

    /**
     * Event handler for onPaint event. Draws the image on the panel.
     */
    void onPaint(wxPaintEvent& event);

    /**
     * Draws the image on the panel immediately.
     */
    void paintNow();

    /**
     * Draws the image on a given drawing context.
     */
    void draw(wxDC& dc);

private:
    /**
     * Registers all the event handlers of the panel.
     */
    void registerEventHandlers();

    /**
     * Draws a crop rectangle in crop mode.
     */
    void drawCropRectangle(wxDC& dc);

    std::shared_ptr<core::SharedData> sharedData;
    std::shared_ptr<core::ImageService> imageService;
};

}
