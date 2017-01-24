#pragma once

#include <memory>
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
    void handleOnPaint(wxPaintEvent& event);

    void paintNow();
    void draw(wxDC& dc);

    bool isDiffReady() const;
    bool areImagesOk() const;

    wxImage getDiff();
    int tryGetThreshold(int defaultThreshold = 100) const;


    wxImage firstImage;
    wxImage secondImage;
};

}
