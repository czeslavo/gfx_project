#include "CompareController.h"
#include "DiffFrame.h"

namespace core
{

void CompareController::registerImageServices(std::shared_ptr<ImageService> first,
                                              std::shared_ptr<ImageService> second)
{
    imageServices = std::make_pair(first, second);
}

void CompareController::registerImagePanels(gui::ImageComparePanel* first, gui::ImageComparePanel* second)
{
    imagePanels = std::make_pair(first, second);
}

void CompareController::registerInfoPanels(gui::ImageInfoPanel* first, gui::ImageInfoPanel* second)
{
    imageInfoPanels = std::make_pair(first, second);
}

void CompareController::registerSharedData(std::shared_ptr<SharedData> data)
{
    sharedData = data;
}

void CompareController::startNewComparison(wxCommandEvent& e)
{
    for (auto service : {imageServices.first, imageServices.second})
        service->reset();

    sharedData->reset();

    for (auto panel : {imagePanels.first, imagePanels.second})
        panel->paintNow();
}

void CompareController::openDiffGenerator(wxCommandEvent& e)
{
    using namespace diff;

    if (not areBothImagesLoaded())
    {
        wxMessageDialog dialog{imagePanels.first, "Both images have to be loaded in order to generate a diff image."};
        dialog.ShowModal();
        return;
    }

    DiffFrame* diffFrame = new DiffFrame(imagePanels.first, imageServices.first->getOriginalImage(),
                                         imageServices.second->getOriginalImage());

    diffFrame->Show();
}

void CompareController::handleLoadingFile(const std::string& filename, ImageIdentity imageIdentity)
{
    switch (imageIdentity)
    {
        case ImageIdentity::LEFT:
            return handleLoadingFile(filename, imageServices.first);
        case ImageIdentity::RIGHT:
            return handleLoadingFile(filename, imageServices.second);
        default:
            return;
    }
}

void CompareController::handleLoadingFile(const std::string& filename, std::shared_ptr<ImageService> service)
{
    return sharedData->masterInfo.isAlive ?
        handleLoadingFileAsSlave(filename, service) :
        handleLoadingFileAsMaster(filename, service);
}

void CompareController::handleLoadingFileAsMaster(const std::string& filename,
                                                  std::shared_ptr<ImageService> service)
{
    service->makeMaster();
    service->loadImageFromFileAsMaster(filename);

    const auto masterSize = service->getOriginalSize();

    sharedData->masterInfo.isAlive = true;
    sharedData->masterInfo.width = masterSize.first;
    sharedData->masterInfo.height = masterSize.second;
}

void CompareController::handleLoadingFileAsSlave(const std::string& filename,
                                                 std::shared_ptr<ImageService> service)
{
    const auto masterSize = std::make_pair(sharedData->masterInfo.width,
                                           sharedData->masterInfo.height);

    service->loadImageFromFileAsSlave(filename, masterSize);
}

void CompareController::handleMouseOnStartDragging(wxMouseEvent& e)
{
    if (not sharedData->dragInfo.dragging)
    {
        sharedData->dragInfo.dragging = true;
        sharedData->dragInfo.x0 = sharedData->imageInfo.x + e.GetX();
        sharedData->dragInfo.y0 = sharedData->imageInfo.y + e.GetY();
    }
}

void CompareController::handleMouseOnDrag(wxMouseEvent& e)
{
    if (not (e.LeftIsDown() and sharedData->dragInfo.dragging))
        return;

    sharedData->imageInfo.x = sharedData->dragInfo.x0 - e.GetX();
    sharedData->imageInfo.y = sharedData->dragInfo.y0 - e.GetY();

    for (auto panel : {imagePanels.first, imagePanels.second})
        panel->paintNow();
}

void CompareController::handleMouseOnEndDragging(wxMouseEvent& e)
{
    sharedData->dragInfo.dragging = false;
}

void CompareController::handleMouseOnScroll(wxMouseEvent& e)
{
    sharedData->imageInfo.zoom += e.GetWheelRotation() > 0 ? 1 : -1;

    for (auto service : {imageServices.first, imageServices.second})
        service->setZoom(sharedData->imageInfo.zoom);

    for (auto panel : {imagePanels.first, imagePanels.second})
        panel->paintNow();
}

bool CompareController::areBothImagesLoaded() const
{
    return imageServices.first->isLoaded() and imageServices.second->isLoaded();
}

}
