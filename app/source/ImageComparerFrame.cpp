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

    leftImagePanel->registerImageService(firstImageService);
    rightImagePanel->registerImageService(secondImageService);

    leftImagePanel->registerSharedData(sharedData);
    rightImagePanel->registerSharedData(sharedData);

    leftPanel->registerImageService(firstImageService);
    rightPanel->registerImageService(secondImageService);

    compareController = std::unique_ptr<core::CompareController>(new core::CompareController);
    compareController->registerImageServices(firstImageService, secondImageService);
    compareController->registerImagePanels(leftImagePanel, rightImagePanel);
    compareController->registerSharedData(sharedData);


    wxInitAllImageHandlers();
    registerEventHandlers();
}

void ImageComparerFrame::registerEventHandlers()
{
    registerFilePickersEventHandlers();
    registerImagePanelsHandlers();
}

void ImageComparerFrame::registerFilePickersEventHandlers()
{
    leftFilePicker->Bind(wxEVT_FILEPICKER_CHANGED, &ImageComparerFrame::handleLeftFilePickerChange, this);
    rightFilePicker->Bind(wxEVT_FILEPICKER_CHANGED, &ImageComparerFrame::handleRightFilePickerChange, this);
}

void ImageComparerFrame::registerImagePanelsHandlers()
{
    using namespace core;

    leftImagePanel->Bind(wxEVT_LEFT_DOWN, &CompareController::handleMouseOnStartDragging, compareController.get());
    leftImagePanel->Bind(wxEVT_MOTION, &CompareController::handleMouseOnDrag, compareController.get());
    leftImagePanel->Bind(wxEVT_LEFT_UP, &CompareController::handleMouseOnEndDragging, compareController.get());
    leftImagePanel->Bind(wxEVT_MOUSEWHEEL, &CompareController::handleMouseOnScroll, compareController.get());

    rightImagePanel->Bind(wxEVT_LEFT_DOWN, &CompareController::handleMouseOnStartDragging, compareController.get());
    rightImagePanel->Bind(wxEVT_MOTION, &CompareController::handleMouseOnDrag, compareController.get());
    rightImagePanel->Bind(wxEVT_LEFT_UP, &CompareController::handleMouseOnEndDragging, compareController.get());
    rightImagePanel->Bind(wxEVT_MOUSEWHEEL, &CompareController::handleMouseOnScroll, compareController.get());
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
