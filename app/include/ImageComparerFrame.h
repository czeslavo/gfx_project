#pragma once

#include <memory>

#include "CompareController.h"
#include "GuiBaseComponents.h"

namespace gui
{

/*
 * Main window of the application. It has all the other controls. They are created in its constructor.
 */
class ImageComparerFrame : public ImagesComparerFrameBase
{
public:
    ImageComparerFrame(wxWindow* parent);

private:
    /*
     * Registers all the event handlers of the frame.
     */
    void registerEventHandlers();

    /*
     * Registers file pickers' event handlers.
     */
    void registerFilePickersEventHandlers();

    /*
     * Registers image panels' event handlers.
     */
    void registerImagePanelsHandlers();

    /*
     * Registers menu's event handlers.
     */
    void registerMenuHandlers();

    /*
     * Event handler for left file picker change.
     */
    void handleLeftFilePickerChange(wxFileDirPickerEvent& event);

    /*
     * Event handler for right file picker change.
     */
    void handleRightFilePickerChange(wxFileDirPickerEvent& event);

    /*
     * Event handler for "help" button press. Opens the help window.
     */
    void openHelp(wxCommandEvent& event);

    std::unique_ptr<core::CompareController> compareController{nullptr};
};

}
