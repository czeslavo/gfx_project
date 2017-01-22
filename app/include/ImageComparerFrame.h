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
    std::unique_ptr<core::CompareController> compareController{nullptr};

};

}
