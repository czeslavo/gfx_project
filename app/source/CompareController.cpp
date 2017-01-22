#include "CompareController.h"

namespace core
{

void CompareController::registerImageServices(std::shared_ptr<ImageService> first,
                                              std::shared_ptr<ImageService> second)
{
    imageServices = std::make_pair(first, second);
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

}
