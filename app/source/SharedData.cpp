#include "SharedData.h"

namespace core
{

void SharedData::reset()
{
    dragInfo.dragging = false;
    dragInfo.x0 = 0;
    dragInfo.y0 = 0;

    imageInfo.x = 0;
    imageInfo.y = 0;
    imageInfo.zoom = 100;

    masterInfo.isAlive = false;
    masterInfo.width = 0;
    masterInfo.height = 0;

    cropData.cropMode = false;
    cropData.startedCropping = false;
    cropData.x0 = 0;
    cropData.y0 = 0;
    cropData.y = 0;
    cropData.x = 0;
}

}
