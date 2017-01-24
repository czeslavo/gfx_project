#include <wx/dcbuffer.h>

#include "DiffFrame.h"
#include "DiffCalculator.h"

namespace diff
{

DiffFrame::DiffFrame(wxWindow* parent, wxImage firstImage, wxImage secondImage)
    : DiffFrameBase(parent),
      firstImage(firstImage),
      secondImage(secondImage)
{
    registerEventHandlers();
}

void DiffFrame::registerEventHandlers()
{
    Bind(wxEVT_BUTTON, &DiffFrame::handleGenerateButtonClick, this);
    panel->Bind(wxEVT_PAINT, &DiffFrame::handleOnPaint, this);
}

void DiffFrame::handleGenerateButtonClick(wxCommandEvent& event)
{
    //generateDiff();
    paintNow();
}

void DiffFrame::handleOnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(panel);
    draw(dc);
}

void DiffFrame::paintNow()
{
    wxClientDC clientDC{panel};
    wxBufferedDC dc{&clientDC};

    draw(dc);
}

void DiffFrame::draw(wxDC& dc)
{
    auto diff = getDiff();
    auto bitmap = wxBitmap(diff);
    dc.Clear();

    if (not bitmap.IsOk())
        return;

    dc.DrawBitmap(bitmap, 0, 0);
}

bool DiffFrame::isDiffReady() const
{
   // return diff.IsOk();
}

bool DiffFrame::areImagesOk() const
{
    return firstImage.IsOk() and secondImage.IsOk();
}

wxImage DiffFrame::getDiff()
{
    if (not areImagesOk())
    {
        statusBar->PushStatusText("Images aren't loaded yet.");
        return wxImage();
    }

    int threshold = tryGetThreshold();

    return diff::getImagesDiff(firstImage, secondImage, threshold,
        bgColorPicker->GetColour(), fgColorPicker->GetColour());
}

int DiffFrame::tryGetThreshold(int threshold) const
{
    try {
        threshold = std::stoi(std::string(thresholdText->GetValue()));
    }
    catch (const std::exception& e) {
        statusBar->PushStatusText("Couldn't parse threshold input. It has to be integer number.");
    }

    return threshold;
}

}
