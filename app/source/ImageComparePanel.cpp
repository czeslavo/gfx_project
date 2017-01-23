#include <wx/dcbuffer.h>

#include "ImageComparePanel.h"

namespace gui
{

ImageComparePanel::ImageComparePanel(wxWindow* parent)
    : wxPanel(parent)
{
    registerEventHandlers();
}

void ImageComparePanel::registerEventHandlers()
{
    Bind(wxEVT_PAINT, &ImageComparePanel::onPaint, this);

    Bind(wxEVT_LEFT_DOWN, &ImageComparePanel::onStartDragging, this);
    Bind(wxEVT_MOTION, &ImageComparePanel::onDrag, this);
    Bind(wxEVT_LEFT_UP, &ImageComparePanel::onEndDragging, this);
}

void ImageComparePanel::onPaint(wxPaintEvent& event)
{
    paintNow();
}

void ImageComparePanel::paintNow()
{
    wxClientDC clientDC{this};
    wxBufferedDC dc{&clientDC};

    draw(dc);
}

void ImageComparePanel::draw(wxDC& dc)
{
    dc.Clear();

    auto bitmap = imageService->getProcessedBitmap();
    if (not bitmap.IsOk())
        return;

    dc.DrawBitmap(bitmap, imagePosition.x, imagePosition.y);
}

void ImageComparePanel::onStartDragging(wxMouseEvent& event)
{
    if (not dragInfo.dragging)
    {
        dragInfo.dragging = true;
        dragInfo.x0 = imagePosition.x + event.GetX();
        dragInfo.y0 = imagePosition.y + event.GetY();
    }
}

void ImageComparePanel::onDrag(wxMouseEvent& event)
{
    if (not (event.LeftIsDown() and dragInfo.dragging))
        return;

    imagePosition.x = dragInfo.x0 - event.GetX();
    imagePosition.y = dragInfo.y0 - event.GetY();

    paintNow();
}

void ImageComparePanel::onEndDragging(wxMouseEvent& event)
{
    dragInfo.dragging = false;

}

void ImageComparePanel::registerImageService(std::shared_ptr<core::ImageService> service)
{
    imageService = service;
}



}
