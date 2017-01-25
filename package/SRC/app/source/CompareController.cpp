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

void CompareController::registerFilePickers(wxFilePickerCtrl* first, wxFilePickerCtrl* second)
{
    filePickers = std::make_pair(first, second);
}

void CompareController::startNewComparison(wxCommandEvent& e)
{
    for (auto service : {imageServices.first, imageServices.second})
        service->reset();

    sharedData->reset();

    redrawAllPanels();

    for (auto filePicker : {filePickers.first, filePickers.second}) {
        filePicker->SetPath("");
        filePicker->Enable();
    }
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
    if (areBothImagesLoaded())
        sharedData->cropData.cropMode = true;
}

void CompareController::handleLoadingFile(const std::string& filename, ImageIdentity imageIdentity)
{
    switch (imageIdentity)
    {
        case ImageIdentity::LEFT:
            return handleLoadingFile(filename, imageServices.first, filePickers.first);
        case ImageIdentity::RIGHT:
            return handleLoadingFile(filename, imageServices.second, filePickers.second);
        default:
            return;
    }
}

void CompareController::handleLoadingFile(const std::string& filename, std::shared_ptr<ImageService> service,
                                          wxFilePickerCtrl* picker)
{
    return sharedData->masterInfo.isAlive ?
        handleLoadingFileAsSlave(filename, service, picker) :
        handleLoadingFileAsMaster(filename, service, picker);
}

void CompareController::handleLoadingFileAsMaster(const std::string& filename,
                                                  std::shared_ptr<ImageService> service,
                                                  wxFilePickerCtrl* picker)
{
    service->makeMaster();
    service->loadImageFromFileAsMaster(filename);

    const auto masterSize = service->getOriginalSize();

    sharedData->masterInfo.isAlive = true;
    sharedData->masterInfo.width = masterSize.first;
    sharedData->masterInfo.height = masterSize.second;

    picker->Disable();
    redrawAllPanels();
}

void CompareController::handleLoadingFileAsSlave(const std::string& filename,
                                                 std::shared_ptr<ImageService> service,
                                                 wxFilePickerCtrl* picker)
{
    const auto masterSize = std::make_pair(sharedData->masterInfo.width,
                                           sharedData->masterInfo.height);

    service->loadImageFromFileAsSlave(filename, masterSize);

    if (not areBothImagesLoaded())
    {
        wxMessageDialog dialog{imagePanels.first, "Images should have the same aspect ratio."};
        dialog.ShowModal();
        return;
    }

    picker->Disable();
    redrawAllPanels();
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

    redrawAllPanels();
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

    redrawAllPanels();
}

void CompareController::handleMouseOnStartDraggingCrop(wxMouseEvent& e)
{
    sharedData->cropData.startedCropping = true;
    sharedData->cropData.x0 = e.GetX();
    sharedData->cropData.y0 = e.GetY();
}

void CompareController::handleMouseOnDragCrop(wxMouseEvent& e)
{
    sharedData->cropData.x = e.GetX();
    sharedData->cropData.y = e.GetY();

    redrawAllPanels();
}

void CompareController::handleMouseOnEndDraggingCrop(wxMouseEvent& e)
{
    sharedData->cropData.startedCropping = false;
    sharedData->cropData.cropMode = false;

    redrawAllPanels();

    saveCroppedToFile();
}

void CompareController::saveCroppedToFile()
{
    const auto rect = fitRectangleToSize(getCropRectangle(), imageServices.first->getOriginalBitmap().GetSize());

    auto bitmap = wxBitmap(
        rect.GetWidth() * 2,
        rect.GetHeight()
    );

    wxMemoryDC memoryContext;

    memoryContext.SelectObject(bitmap);
    drawCropped(memoryContext);

    memoryContext.SelectObject(wxNullBitmap);


    const std::string filesWildcard{"PNG, JPEG, TIFF or BMP files \
        (*.png;*.jpeg;*.tiff;*.bmp)| \
        *.png;*.PNG;*.jpeg;*.jpg;*.JPG;*.JPEG;*.tiff;*.TIFF;*.bmp;*.BMP"};

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
    auto fittedRectangle = fitRectangleToSize(cropRectangle, first.GetSize());

    auto firstCropped = first.GetSubBitmap(fittedRectangle);
    auto secondCropped = second.GetSubBitmap(fittedRectangle);

    dc.DrawBitmap(firstCropped, 0, 0);
    dc.DrawBitmap(secondCropped, fittedRectangle.GetWidth(), 0);
}

wxRect CompareController::getCropRectangle()
{
    const float zoom = sharedData->imageInfo.zoom;
    const float coeff = 100.f / zoom;

    int x1 = sharedData->cropData.x;
    int x2 = sharedData->cropData.x0;
    int y1 = sharedData->cropData.y;
    int y2 = sharedData->cropData.y0;

    return {
        wxPoint{static_cast<int>(((x1 > x2 ? x2 : x1) - sharedData->imageInfo.x) * coeff),
                static_cast<int>(((y1 > y2 ? y2 : y1) - sharedData->imageInfo.y) * coeff)},
        wxPoint{static_cast<int>(((x1 > x2 ? x1 : x2) - sharedData->imageInfo.x) * coeff),
                static_cast<int>(((y1 > y2 ? y1 : y2) - sharedData->imageInfo.y) * coeff)}
    };

}

wxRect CompareController::fitRectangleToSize(const wxRect& rect, const wxSize& size)
{
    return wxRect{
        wxPoint{rect.GetLeft() < 0 ? 0 : rect.GetLeft(),
                rect.GetTop() < 0 ? 0 : rect.GetTop()},
        wxPoint{rect.GetRight() > size.GetWidth() ? size.GetWidth() - 1 : rect.GetRight(),
                rect.GetBottom() > size.GetHeight() ? size.GetHeight() - 1 : rect.GetBottom()}
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

void CompareController::redrawAllPanels()
{
    for (auto panel : {imagePanels.first, imagePanels.second})
        panel->paintNow();

    for (auto panel : {imageInfoPanels.first, imageInfoPanels.second})
        panel->paintNow();
}

}

