#include "CompareController.h"

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


void CompareController::registerSharedData(std::shared_ptr<SharedData> data)
{
    sharedData = data;
}

void CompareController::handleLoadingFile(const std::string& filename, ImageIdentity imageIdentity)
{
    switch (imageIdentity)
    {
        case ImageIdentity::LEFT:
            imageServices.first->loadImageFromFile(filename);
            return;

        case ImageIdentity::RIGHT:
            imageServices.second->loadImageFromFile(filename);
            return;

        default:
            return;
    }
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

}
