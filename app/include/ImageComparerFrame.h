#pragma once

#include <memory>

#include "CompareController.h"
#include "GuiBaseComponents.h"

namespace gui
{

class ImageComparerFrame : public ImagesComparerFrameBase
{
public:
    ImageComparerFrame(wxWindow* parent);

private:
    void registerEventHandlers();
    void registerFilePickersEventHandlers();
    void registerImagePanelsHandlers();

    void handleLeftFilePickerChange(wxFileDirPickerEvent& event);
    void handleRightFilePickerChange(wxFileDirPickerEvent& event);

    std::unique_ptr<core::CompareController> compareController{nullptr};

};

}
