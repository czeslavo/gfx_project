#pragma once

#include <memory>
#include "CompareController.h"
#include "DiffFrameBase.h"

namespace diff
{

class DiffFrame : public DiffFrameBase
{
public:
    DiffFrame(wxWindow* parent, wxImage firstImage, wxImage secondImage);

private:
    void registerEventHandlers();

    void handleGenerateButtonClick(wxCommandEvent& event);
    void handleSaveButtonClick(wxCommandEvent& event);
    void handleUpdateUi(wxUpdateUIEvent& event);
    void handleOnPaint(wxPaintEvent& event);


    void paintNow();
    void draw(wxDC& dc);

    void updateUi();
    void enableRadioButtons();
    void disableRadioButtons();

    bool isDiffReady() const;
    bool areImagesOk() const;

    void generateDiff();

    int tryGetThreshold(int defaultThreshold = 100) const;
    bool shouldUseImage() const;
    ImageIdentity whichImageShouldUse() const;

    void saveDiffToFile(const wxString& path) const;

    wxImage firstImage;
    wxImage secondImage;
    wxImage diff;
};

}
