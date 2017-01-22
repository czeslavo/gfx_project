#include "ImageService.h"

#include "ImageComparerFrame.h"

namespace gui
{

ImageComparerFrame::ImageComparerFrame(wxWindow* parent)
    : ImagesComparerFrameBase(parent)
{
    auto firstImageService = std::make_shared<core::ImageService>();
    auto secondImageService = std::make_shared<core::ImageService>();

    leftImagePanel->registerImageService(firstImageService);
    rightImagePanel->registerImageService(secondImageService);

    leftPanel->registerImageService(firstImageService);
    rightPanel->registerImageService(secondImageService);

    compareController = std::unique_ptr<core::CompareController>(new core::CompareController);
    compareController->registerImageServices(firstImageService, secondImageService);
}


}
