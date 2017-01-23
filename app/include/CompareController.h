#pragma once

#include <utility>
#include <memory>

#include "SharedData.h"
#include "ImageComparePanel.h"
#include "ImageService.h"
#include "ImageInfoPanel.h"

enum class ImageIdentity { LEFT, RIGHT };

namespace core
{

class CompareController
{
public:
    void registerImageServices(std::shared_ptr<ImageService> first, std::shared_ptr<ImageService> second);
    void registerImagePanels(gui::ImageComparePanel* first, gui::ImageComparePanel* second);
    void registerSharedData(std::shared_ptr<SharedData> data);
    void registerInfoPanels(gui::ImageInfoPanel* first, gui::ImageInfoPanel* second);

    void startNewComparison(wxCommandEvent& e);
    void handleLoadingFile(const std::string& filename, ImageIdentity imageIdentity);

    void handleMouseOnStartDragging(wxMouseEvent& e);
    void handleMouseOnDrag(wxMouseEvent& e);
    void handleMouseOnEndDragging(wxMouseEvent& e);
    void handleMouseOnScroll(wxMouseEvent& e);

private:
    std::shared_ptr<SharedData> sharedData;
    std::pair<std::shared_ptr<ImageService>, std::shared_ptr<ImageService>> imageServices;
    std::pair<gui::ImageComparePanel*, gui::ImageComparePanel*> imagePanels;
    std::pair<gui::ImageInfoPanel*, gui::ImageInfoPanel*> imageInfoPanels;

};

}
