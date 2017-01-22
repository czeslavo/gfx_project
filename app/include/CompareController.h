#pragma once

#include <utility>
#include <memory>

#include "ImageService.h"

enum class ImageIdentity { LEFT, RIGHT };

namespace core
{

class CompareController
{
public:
    void registerImageServices(std::shared_ptr<ImageService> first, std::shared_ptr<ImageService> second);

    void handleLoadingFile(const std::string& filename, ImageIdentity imageIdentity);


private:
    std::pair<std::shared_ptr<ImageService>, std::shared_ptr<ImageService>> imageServices;


};

}
