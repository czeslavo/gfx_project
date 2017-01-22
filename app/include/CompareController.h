#pragma once

#include <utility>
#include <memory>

#include "ImageService.h"

namespace core
{

class CompareController
{
public:
    void registerImageServices(std::shared_ptr<ImageService> first, std::shared_ptr<ImageService> second);

private:
    std::pair<std::shared_ptr<ImageService>, std::shared_ptr<ImageService>> imageServices;


};

}
