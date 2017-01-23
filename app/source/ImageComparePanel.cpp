#include <wx/dcbuffer.h>

#include "ImageComparePanel.h"
#include <iostream>

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

    Bind(wxEVT_MOUSEWHEEL, &ImageComparePanel::onMouseScroll, this);
}

void ImageComparePanel::registerImageService(std::shared_ptr<core::ImageService> service)
{
    imageService = service;
}

void ImageComparePanel::registerSharedData(std::shared_ptr<core::SharedData> data)
{
    sharedData = data;
}

void ImageComparePanel::registerSecondPanel(wxWindow* panel)
{
    secondPanel = panel;
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

    dc.DrawBitmap(bitmap, sharedData->imageInfo.x, sharedData->imageInfo.y);
}

void ImageComparePanel::onStartDragging(wxMouseEvent& event)
{
    if (not sharedData->dragInfo.dragging)
    {
        sharedData->dragInfo.dragging = true;
        sharedData->dragInfo.x0 = sharedData->imageInfo.x + event.GetX();
        sharedData->dragInfo.y0 = sharedData->imageInfo.y + event.GetY();
    }
}

void ImageComparePanel::onDrag(wxMouseEvent& event)
{
    if (not (event.LeftIsDown() and sharedData->dragInfo.dragging))
        return;

    sharedData->imageInfo.x = sharedData->dragInfo.x0 - event.GetX();
    sharedData->imageInfo.y = sharedData->dragInfo.y0 - event.GetY();

    paintNow();
    sendPaintEventToSecondPanel();
}

void ImageComparePanel::sendPaintEventToSecondPanel()
{
    wxPaintEvent event;
    wxPostEvent(secondPanel, event);
}

void ImageComparePanel::onEndDragging(wxMouseEvent& event)
{
    sharedData->dragInfo.dragging = false;
}

void ImageComparePanel::onMouseScroll(wxMouseEvent& event)
{
    const int imageZoom = imageService->getZoom() + 1;
    sharedData->imageInfo.zoom = imageZoom;

    imageService->setZoom(imageZoom);
    paintNow();
}

}
