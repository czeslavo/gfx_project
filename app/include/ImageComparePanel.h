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

    void onStartDragging(wxMouseEvent& event);
    void onDrag(wxMouseEvent& event);
    void onEndDragging(wxMouseEvent& event);

    void registerImageService(std::shared_ptr<core::ImageService> service);

private:
    void registerEventHandlers();

    struct {
        bool dragging{false};
        int x0;
        int y0;
    } dragInfo;

    struct {
        int x;
        int y;
    } imagePosition;

    std::shared_ptr<core::ImageService> imageService;
};

}
