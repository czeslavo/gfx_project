#include "CompareController.h"

namespace core
{

void CompareController::registerImageServices(std::shared_ptr<ImageService> first,
                                              std::shared_ptr<ImageService> second)
{
    imageServices = std::make_pair(first, second);
}

}
