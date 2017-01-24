#include <wx/dcbuffer.h>

#include "DiffFrame.h"
#include "DiffCalculator.h"
#include "Helpers.h"

namespace diff
{

DiffFrame::DiffFrame(wxWindow* parent, wxImage firstImage, wxImage secondImage)
    : DiffFrameBase(parent),
      firstImage(firstImage),
      secondImage(secondImage)
{
    registerEventHandlers();
    generateDiff();
}

void DiffFrame::registerEventHandlers()
{
    Bind(wxEVT_BUTTON, &DiffFrame::handleGenerateButtonClick, this);
    Bind(wxEVT_UPDATE_UI, &DiffFrame::handleUpdateUi, this);

    panel->Bind(wxEVT_PAINT, &DiffFrame::handleOnPaint, this);
}

void DiffFrame::handleGenerateButtonClick(wxCommandEvent& event)
{
    generateDiff();
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
    dc.Clear();

    if (not isDiffReady())
        return;

    auto size = dc.GetSize();
    auto bitmap = helpers::getFittedBitmap(diff, size);
    auto centerPosition = helpers::getCenterPosition(size, bitmap.GetSize());

    dc.DrawBitmap(bitmap, centerPosition);
}

void DiffFrame::handleUpdateUi(wxUpdateUIEvent& event)
{
    updateUi();
}

void DiffFrame::updateUi()
{
    if (isDiffReady())
        saveButton->Enable();
    else
        saveButton->Disable();

    if (drawImageCheckBox->GetValue())
        enableRadioButtons();
    else
        disableRadioButtons();
}

void DiffFrame::enableRadioButtons()
{
    drawFirstRadioButton->Enable();
    drawSecondRadioButton->Enable();
}

void DiffFrame::disableRadioButtons()
{
    drawFirstRadioButton->Disable();
    drawSecondRadioButton->Disable();
}

bool DiffFrame::isDiffReady() const
{
    return diff.IsOk();
}

bool DiffFrame::areImagesOk() const
{
    return firstImage.IsOk() and secondImage.IsOk();
}

void DiffFrame::generateDiff()
{
    if (not areImagesOk())
    {
        statusBar->PushStatusText("Images aren't loaded yet.");
        return;
    }

    int threshold = tryGetThreshold();
    const auto useImage = shouldUseImage();
    const auto whichImage = whichImageShouldUse();

    diff = diff::getImagesDiff(firstImage, secondImage, threshold, useImage, whichImage,
        bgColorPicker->GetColour(), fgColorPicker->GetColour());

    updateUi();
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

bool DiffFrame::shouldUseImage() const
{
    return drawImageCheckBox->GetValue();
}

ImageIdentity DiffFrame::whichImageShouldUse() const
{
    if (drawFirstRadioButton->GetValue())
        return ImageIdentity::LEFT;
    if (drawSecondRadioButton->GetValue())
        return ImageIdentity::RIGHT;

    return ImageIdentity::NONE;
}

}
