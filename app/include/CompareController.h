#pragma once

#include <utility>
#include <memory>
#include <wx/filepicker.h>

#include "SharedData.h"
#include "ImageComparePanel.h"
#include "ImageService.h"
#include "ImageInfoPanel.h"

/*
 * Enum identifying which image we're considering. In the application we use term "left" and "right" or
 * "first" and "second"
 */
enum class ImageIdentity { LEFT, RIGHT, NONE };

namespace core
{
/*
 * Controller class. It has access to all GUI components and directs data flow between them.
 */
class CompareController
{
public:
    /*
     * Registers image services.
     * \sa ImageService
     */
    void registerImageServices(std::shared_ptr<ImageService> first, std::shared_ptr<ImageService> second);

    /*
     * Registers image panels.
     * \sa gui::ImageComparePanel
     */
    void registerImagePanels(gui::ImageComparePanel* first, gui::ImageComparePanel* second);

    /*
     * Registers shared data.
     * \sa SharedData
     */
    void registerSharedData(std::shared_ptr<SharedData> data);

    /*
     * Registers info panels.
     * \sa gui::ImageInfoPanel
     */
    void registerInfoPanels(gui::ImageInfoPanel* first, gui::ImageInfoPanel* second);

    /*
     * Registers file pickers.
     * \sa wxFilePickerCtrl
     */
    void registerFilePickers(wxFilePickerCtrl* first, wxFilePickerCtrl* second);

    /*
     * Loads file with a given identity. It's used in ImageComparerFrame's event handler to load images.
     * \sa ImageComparerFrame
     * \param filename Full path to image file
     * \param imageIdentity should the image be loaded as left or right one
     */
    void handleLoadingFile(const std::string& filename, ImageIdentity imageIdentity);

    /*
     * Redraws all the GUI panels it posses: info panels and compare panels.
     */
    void redrawAllPanels();

    /*
     * Event handler for "start new comparison" button.
     */
    void startNewComparison(wxCommandEvent& e);

    /*
     * Event handler for "open diff generator" button.
     */
    void openDiffGenerator(wxCommandEvent& e);

    /*
     * Event handler for "start cropping" button.
     */
    void startCropping(wxCommandEvent& e);

    /*
     * Event handler for starting dragging with a mouse. Inside it we start dragging the image, to change it position,
     * or (in crop mode) start drawing a rectangle of selection.
     */
    void handleMouseOnStartDragging(wxMouseEvent& e);

    /*
     * Event handler for mouse movement during its left button press. It updates crop rectangle or image position.
     */
    void handleMouseOnDrag(wxMouseEvent& e);

    /*
     * Event handler for drag ending. Stops drawing selection rectangle in crop mode and initializes the cropping result
     * saving, or stops updating image position.
     */
    void handleMouseOnEndDragging(wxMouseEvent& e);

    /*
     * Event handler for mouse scroll change. It's used for zooming images.
     */
    void handleMouseOnScroll(wxMouseEvent& e);

private:

    /*
     * Part of handleMouseOnStartDragging which is called only in crop mode.
     */
    void handleMouseOnStartDraggingCrop(wxMouseEvent& e);

    /*
     * Part of handleMouseOnDrag which is called only in crop mode.
     */
    void handleMouseOnDragCrop(wxMouseEvent& e);

    /*
     * Part of handleMouseOnEndDragging which is called only in crop mode.
     */
    void handleMouseOnEndDraggingCrop(wxMouseEvent& e);

    /*
     * Handles loading image file using a given ImageService and wxFilePickerCtrl.
     */
    void handleLoadingFile(const std::string& filename, std::shared_ptr<ImageService> service, wxFilePickerCtrl* picker);

    /*
     * Handles loading file when it's the first one in the current comparison. Loaded image becomes a "master", so
     * the second one will have to have the same aspect ratio as master to be loaded.
     */
    void handleLoadingFileAsMaster(const std::string& filename, std::shared_ptr<ImageService> service, wxFilePickerCtrl* picker);

    /*
     * Handles loading file when it's the second one in the comparison. Loaded
     */
    void handleLoadingFileAsSlave(const std::string& filename, std::shared_ptr<ImageService> service, wxFilePickerCtrl* picker);

    /*
     * Checks if both images are already loaded. Used in some cases where we need them both, i.e. generating diff
     * or cropping.
     */
    bool areBothImagesLoaded() const;

    /*
     * Saves two recently loaded images together in the file (shows the file dialog to the user). The images are
     * located beside each other in horizontal order.
     */
    void saveCroppedToFile();

    /*
     * Used by saveCroppedToFile method to draw images on a given drawing context.
     * \sa wxDC
     */
    void drawCropped(wxDC& dc);

    /*
     * Gets current cropping rectangle.
     */
    wxRect getCropRectangle();

    /*
     * Checks if a crop rectangle is in images borders. If not, it fits the rectangle to them.
     */
    wxRect fitRectangleToSize(const wxRect& rect, const wxSize& size);

    /*
     * Helper method which saves a given bitmap to the file.
     */
    void saveBitmapToFile(const wxString& path, wxBitmap bitmap);

    std::shared_ptr<SharedData> sharedData;
    std::pair<std::shared_ptr<ImageService>, std::shared_ptr<ImageService>> imageServices;
    std::pair<gui::ImageComparePanel*, gui::ImageComparePanel*> imagePanels;
    std::pair<gui::ImageInfoPanel*, gui::ImageInfoPanel*> imageInfoPanels;
    std::pair<wxFilePickerCtrl*, wxFilePickerCtrl*> filePickers;
};

}