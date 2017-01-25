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
    compareController->registerInfoPanels(leftPanel, rightPanel);
    compareController->registerFilePickers(leftFilePicker, rightFilePicker);

    registerEventHandlers();
}

void ImageComparerFrame::registerEventHandlers()
{
    registerFilePickersEventHandlers();
    registerImagePanelsHandlers();
    registerMenuHandlers();
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

void ImageComparerFrame::registerMenuHandlers()
{
    using namespace core;
    toolBar->Bind(wxEVT_COMMAND_TOOL_CLICKED, &CompareController::startNewComparison, compareController.get(),
        NEW_COMPARISON_ID);

    toolBar->Bind(wxEVT_COMMAND_TOOL_CLICKED, &CompareController::openDiffGenerator, compareController.get(),
       DIFF_ID);

    toolBar->Bind(wxEVT_COMMAND_TOOL_CLICKED, &CompareController::startCropping, compareController.get(),
       CROP_ID);
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
