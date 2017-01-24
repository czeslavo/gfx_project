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

void CompareController::startCropping(wxCommandEvent& e)
{
    sharedData->cropData.cropMode = true;
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
    if (sharedData->cropData.cropMode)
        return handleMouseOnStartDraggingCrop(e);

    if (not sharedData->dragInfo.dragging)
    {
        sharedData->dragInfo.dragging = true;
        sharedData->dragInfo.x0 = sharedData->imageInfo.x + e.GetX();
        sharedData->dragInfo.y0 = sharedData->imageInfo.y + e.GetY();
    }
}

void CompareController::handleMouseOnDrag(wxMouseEvent& e)
{
    if (e.LeftIsDown() and sharedData->cropData.startedCropping)
        return handleMouseOnDragCrop(e);

    if (not (e.LeftIsDown() and sharedData->dragInfo.dragging))
        return;

    sharedData->imageInfo.x = sharedData->dragInfo.x0 - e.GetX();
    sharedData->imageInfo.y = sharedData->dragInfo.y0 - e.GetY();

    for (auto panel : {imagePanels.first, imagePanels.second})
        panel->paintNow();
}

void CompareController::handleMouseOnEndDragging(wxMouseEvent& e)
{
    if (sharedData->cropData.startedCropping)
        return handleMouseOnEndDraggingCrop(e);

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

void CompareController::handleMouseOnStartDraggingCrop(wxMouseEvent& e)
{
    sharedData->cropData.startedCropping = true;
    sharedData->cropData.x0 = e.GetX();
    sharedData->cropData.y0 = e.GetY();
}

void CompareController::handleMouseOnDragCrop(wxMouseEvent& e)
{
    sharedData->cropData.x = e.GetX() - sharedData->cropData.x0;
    sharedData->cropData.y = e.GetY() - sharedData->cropData.y0;

    for (auto panel : {imagePanels.first, imagePanels.second})
        panel->paintNow();
}

void CompareController::handleMouseOnEndDraggingCrop(wxMouseEvent& e)
{
    sharedData->cropData.startedCropping = false;
    sharedData->cropData.cropMode = false;

    for (auto panel : {imagePanels.first, imagePanels.second})
        panel->paintNow();

    saveCroppedToFile();
}

void CompareController::saveCroppedToFile()
{
    auto bitmap = wxBitmap(
        std::abs(sharedData->cropData.x - sharedData->cropData.x0) * 2,
        std::abs(sharedData->cropData.y - sharedData->cropData.y0) * 2
    );

    wxMemoryDC memoryContext;

    memoryContext.SelectObject(bitmap);
    drawCropped(memoryContext);

    memoryContext.SelectObject(wxNullBitmap);


    const std::string filesWildcard{"PNG, JPEG, TIFF or BMP files \
        (*.png;*.PNG;*.jpeg;*.jpg;*.JPG;*.JPEG;*.tiff;*.TIFF;*.bmp;*.BMP)| \
        *.png;*.jpeg;*.tiff;*.bmp"};

    wxFileDialog fileDialog{
        imagePanels.first, "Save image", "", "", filesWildcard, wxFD_SAVE};

    if (fileDialog.ShowModal() == wxID_CANCEL)
        return;

    saveBitmapToFile(fileDialog.GetPath(), bitmap);
}

void CompareController::drawCropped(wxDC& dc)
{
    auto first = imageServices.first->getOriginalBitmap();
    auto second = imageServices.second->getOriginalBitmap();

    auto cropRectangle = getCropRectangle();

    auto firstCropped = first.GetSubBitmap(cropRectangle);
    auto secondCropped = second.GetSubBitmap(cropRectangle);

    dc.DrawBitmap(firstCropped, 0, 0);
    dc.DrawBitmap(secondCropped, first.GetWidth(), 0);
}

wxRect CompareController::getCropRectangle()
{
    const float zoom = sharedData->imageInfo.zoom;
    const float coeff = 100.f / zoom;

    return wxRect{
        wxPoint{static_cast<int>(sharedData->cropData.x * coeff),  static_cast<int>(sharedData->cropData.y * coeff)},
        wxPoint{static_cast<int>(sharedData->cropData.x0 * coeff), static_cast<int>(sharedData->cropData.y0 * coeff)}
    };

}

void CompareController::saveBitmapToFile(const wxString& path, wxBitmap bitmap)
{
    if (path.Matches("*.png") or path.Matches(".PNG"))
    {
        bitmap.SaveFile(path, wxBITMAP_TYPE_PNG);
        return;
    }
    if (path.Matches("*.jpeg") or path.Matches("*.jpg") or path.Matches("*.JPEG") or
        path.Matches("*.JPG"))
    {
        bitmap.SaveFile(path, wxBITMAP_TYPE_JPEG);
        return;
    }
    if (path.Matches("*.tiff") or path.Matches("*.TIFF"))
    {
        bitmap.SaveFile(path, wxBITMAP_TYPE_TIFF);
        return;
    }
    if (path.Matches("*.bmp") or path.Matches("*.BMP"))
    {
        bitmap.SaveFile(path, wxBITMAP_TYPE_BMP);
        return;
    }
}

bool CompareController::areBothImagesLoaded() const
{
    return imageServices.first->isLoaded() and imageServices.second->isLoaded();
}

}
