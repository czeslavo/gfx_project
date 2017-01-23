#pragma once

#include <wx/wx.h>

#include "ImageService.h"
#include "SharedData.h"

namespace gui
{

class ImageComparePanel : public wxPanel
{
public:
    ImageComparePanel(wxWindow* parent);

    void registerImageService(std::shared_ptr<core::ImageService> service);
    void registerSharedData(std::shared_ptr<core::SharedData> data);
    void registerSecondPanel(wxWindow* panel);

    void onPaint(wxPaintEvent& event);
    void paintNow();
    void draw(wxDC& dc);

    void onStartDragging(wxMouseEvent& event);
    void onDrag(wxMouseEvent& event);
    void onEndDragging(wxMouseEvent& event);

    void onMouseScroll(wxMouseEvent& event);

private:
    void registerEventHandlers();
    void sendPaintEventToSecondPanel();

    wxWindow* secondPanel;
    std::shared_ptr<core::SharedData> sharedData;
    std::shared_ptr<core::ImageService> imageService;
};

}
