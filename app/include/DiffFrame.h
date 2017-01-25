#pragma once

#include <memory>
#include "CompareController.h"
#include "DiffFrameBase.h"

namespace diff
{

/*
 * Frame in which user can generate a diff image of the loaded ones.
 */
class DiffFrame : public DiffFrameBase
{
public:
    /*
     * Constructor takes two images loaded by a user.
     */
    DiffFrame(wxWindow* parent, wxImage firstImage, wxImage secondImage);

private:
    /*
     * Registers all the event handlers of the frame.
     */
    void registerEventHandlers();

    /*
     * Event handler for "generate" button. Generates a diff image basing on user input and draws it.
     */
    void handleGenerateButtonClick(wxCommandEvent& event);

    /*
     * Event handler for "save" button. Allows user to save the diff image.
     */
    void handleSaveButtonClick(wxCommandEvent& event);

    /*
     * Event handler for "pick background colour" button.
     */
    void pickBgColor(wxCommandEvent& event);

    /*
     * Event handler for "pick foreground colour" button.
     */
    void pickFgColor(wxCommandEvent& event);

    /*
     * Event handler for updating UI of the frame. Refreshes the controls.
     */
    void handleUpdateUi(wxUpdateUIEvent& event);

    /*
     * Event handler for "onPaint" event. Redraws the panel on which we draw the diff image.
     */
    void handleOnPaint(wxPaintEvent& event);

    /*
     * Event handler for resizing the window. It allows to resize the diff image accordingly to the window size.
     */
    void handleResize(wxSizeEvent& event);

    /*
     * Draws the diff immediately.
     */
    void paintNow();

    /*
     * Draws the diff image on a drawing context.
     */
    void draw(wxDC& dc);


    /*
     * Updates the whole user interface.
     */
    void updateUi();

    /*
     * Enables radio buttons. They should be enabled only when check box is checked.
     */
    void enableRadioButtons();

    /*
     * Disables radio buttons. They should be enabled only when check box is checked.
     */
    void disableRadioButtons();

    /*
     * Check if the diff is already calculated and ready to draw.
     */
    bool isDiffReady() const;

    /*
     * Check if the passed images are proper.
     */
    bool areImagesOk() const;

    /*
     * Generates the diff image and draws it.
     */
    void generateDiff();

    /*
     * Gets the threshold from the control.
     */
    int tryGetThreshold(int defaultThreshold = 100) const;

    /*
     * Gets boolean value from checkbox, tells us if we should draw the image as a background.
     */
    bool shouldUseImage() const;

    /*
     * Tells us which image we should draw as a background.
     */
    ImageIdentity whichImageShouldUse() const;

    /*
     * Saves the generated diff image to file.
     */
    void saveDiffToFile(const wxString& path) const;

    /*
     * Struct handling background and foreground colors.
     */
    struct {
        wxColour bg{*wxBLACK};
        wxColour fg{*wxRED};
    } colors;

    wxImage firstImage;
    wxImage secondImage;
    wxImage diff;
};

}
