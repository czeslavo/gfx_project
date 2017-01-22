#pragma once

#include <wx/wx.h>

#include "ImageService.h"

namespace gui
{

class ImageComparePanel : public wxPanel
{
public:
    ImageComparePanel(wxWindow* parent);

    void registerImageService(std::shared_ptr<core::ImageService> service);

private:
    void registerEventHandlers();

    std::shared_ptr<core::ImageService> imageService;
};

}
