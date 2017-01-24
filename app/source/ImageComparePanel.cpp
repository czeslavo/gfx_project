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
}

void ImageComparePanel::registerImageService(std::shared_ptr<core::ImageService> service)
{
    imageService = service;
}

void ImageComparePanel::registerSharedData(std::shared_ptr<core::SharedData> data)
{
    sharedData = data;
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

    if (sharedData->cropData.cropMode)
        drawCropRectangle(dc);
}

void ImageComparePanel::drawCropRectangle(wxDC& dc)
{
    wxColour filling(0, 0, 0, 128);
    wxColour outline(0, 0, 0, 180);

    wxBrush brush(filling);
    wxPen pen(outline);

    dc.SetBrush(brush);
    dc.SetPen(pen);

    dc.DrawRectangle(sharedData->cropData.x0, sharedData->cropData.y0,
                     sharedData->cropData.x - sharedData->cropData.x0,
                     sharedData->cropData.y - sharedData->cropData.y0);
}

}
