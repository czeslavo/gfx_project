#pragma once

#include <wx/wx.h>

#include "ImageService.h"

namespace gui
{

class ImageComparePanel : public wxPanel
{
public:
    ImageComparePanel(wxWindow* parent);

    void onPaint(wxPaintEvent& event);
    void paintNow();
    void draw(wxDC& dc);

    void registerImageService(std::shared_ptr<core::ImageService> service);

private:
    void registerEventHandlers();

    std::shared_ptr<core::ImageService> imageService;
};

}
