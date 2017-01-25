#include <wx/dcbuffer.h>
#include <wx/colordlg.h>

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
    generateButton->Bind(wxEVT_BUTTON, &DiffFrame::handleGenerateButtonClick, this);
    saveButton->Bind(wxEVT_BUTTON, &DiffFrame::handleSaveButtonClick, this);

    Bind(wxEVT_UPDATE_UI, &DiffFrame::handleUpdateUi, this);

    panel->Bind(wxEVT_SIZE, &DiffFrame::handleResize, this);
    panel->Bind(wxEVT_PAINT, &DiffFrame::handleOnPaint, this);

    bgColorPicker->Bind(wxEVT_BUTTON, &DiffFrame::pickBgColor, this);
    fgColorPicker->Bind(wxEVT_BUTTON, &DiffFrame::pickFgColor, this);

}

void DiffFrame::handleGenerateButtonClick(wxCommandEvent& event)
{
    generateDiff();
    paintNow();
}

void DiffFrame::handleSaveButtonClick(wxCommandEvent& event)
{
    const std::string filesWildcard{"PNG, JPEG, TIFF or BMP files \
        (*.png;*.PNG;*.jpeg;*.jpg;*.JPG;*.JPEG;*.tiff;*.TIFF;*.bmp;*.BMP)| \
        *.png;*.jpeg;*.tiff;*.bmp"};

    wxFileDialog fileDialog{
        this, "Save image", "", "", filesWildcard, wxFD_SAVE};

    if (fileDialog.ShowModal() == wxID_CANCEL)
        return;

    saveDiffToFile(fileDialog.GetPath());
}

void DiffFrame::handleOnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(panel);
    draw(dc);
}

void DiffFrame::handleResize(wxSizeEvent& event)
{
    wxWindow::Refresh();
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
        colors.bg, colors.fg);

    updateUi();
}

int DiffFrame::tryGetThreshold(int threshold) const
{
    try {
        long thresh{100};
        thresholdText->GetValue().ToLong(&thresh);
        threshold = thresh;
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

void DiffFrame::saveDiffToFile(const wxString& path) const
{
    if (not isDiffReady())
        return;

    const auto bitmap = wxBitmap(diff);

    if (path.Matches("*.png") or path.Matches(".PNG"))
    {
        bitmap.SaveFile(path, wxBITMAP_TYPE_PNG);
        return;
    }
    if (path.Matches("*.jpeg") or path.Matches("*.jpg") or path.Matches("*.JPEG") or
        path.Matches("*.JPG"))
    {
        bitmap.SaveFile(path, wxBITMAP_TYPE_JPEG);
        return;
    }
    if (path.Matches("*.tiff") or path.Matches("*.TIFF"))
    {
        bitmap.SaveFile(path, wxBITMAP_TYPE_TIFF);
        return;
    }
    if (path.Matches("*.bmp") or path.Matches("*.BMP"))
    {
        bitmap.SaveFile(path, wxBITMAP_TYPE_BMP);
        return;
    }

    statusBar->PushStatusText("Not supported file extension. Diff not saved.");
}

void DiffFrame::pickBgColor(wxCommandEvent& event)
{
    wxColourDialog* colourDialog = new wxColourDialog(this);

    if (colourDialog->ShowModal() == wxID_CANCEL)
        return;

    colors.bg = colourDialog->GetColourData().GetColour();
}

void DiffFrame::pickFgColor(wxCommandEvent& event)
{
    wxColourDialog* colourDialog = new wxColourDialog(this);

    if (colourDialog->ShowModal() == wxID_CANCEL)
        return;

    colors.fg = colourDialog->GetColourData().GetColour();
}

}
