#include "ImageService.h"

#include "ImageComparerFrame.h"

namespace gui
{

ImageComparerFrame::ImageComparerFrame(wxWindow* parent)
    : ImagesComparerFrameBase(parent)
{
    auto firstImageService = std::make_shared<core::ImageService>();
    auto secondImageService = std::make_shared<core::ImageService>();

    auto sharedData = std::make_shared<core::SharedData>();

    leftImagePanel->registerSecondPanel(rightImagePanel);
    rightImagePanel->registerSecondPanel(leftImagePanel);

    leftImagePanel->registerImageService(firstImageService);
    rightImagePanel->registerImageService(secondImageService);

    leftImagePanel->registerSharedData(sharedData);
    rightImagePanel->registerSharedData(sharedData);

    leftPanel->registerImageService(firstImageService);
    rightPanel->registerImageService(secondImageService);

    compareController = std::unique_ptr<core::CompareController>(new core::CompareController);
    compareController->registerImageServices(firstImageService, secondImageService);

    wxInitAllImageHandlers();
    registerEventHandlers();
}

void ImageComparerFrame::registerEventHandlers()
{
    registerFilePickersEventHandlers();

}

void ImageComparerFrame::registerFilePickersEventHandlers()
{
    leftFilePicker->Bind(wxEVT_FILEPICKER_CHANGED, &ImageComparerFrame::handleLeftFilePickerChange, this);
    rightFilePicker->Bind(wxEVT_FILEPICKER_CHANGED, &ImageComparerFrame::handleRightFilePickerChange, this);
}

void ImageComparerFrame::handleLeftFilePickerChange(wxFileDirPickerEvent& event)
{
    using namespace core;
    compareController->handleLoadingFile(event.GetPath().ToStdString(), ImageIdentity::LEFT);
}

void ImageComparerFrame::handleRightFilePickerChange(wxFileDirPickerEvent& event)
{
    using namespace core;
    compareController->handleLoadingFile(event.GetPath().ToStdString(), ImageIdentity::RIGHT);
}



}
