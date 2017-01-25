#pragma once

namespace core
{

/*
 * It's data used to communicate between the application components.
 * - dragInfo is used for dragging the image - it's changed by CompareController and used by ImageComparePanel to draw
 * the images
 * - imageInfo is used for storing the images position and zoom - it's changed by CompareController and used by
 * ImageComparePanel to draw the images
 * - masterInfo is used to store data about the master image (if it's present and its size)
 * - cropData is used to store the cropping rectangle coords and flags telling us if the cropping mode is turned on
 */
struct SharedData
{
    void reset();

    struct {
        bool dragging{false};
        int x0{0};
        int y0{0};
    } dragInfo;

    struct {
        int x{0};
        int y{0};
        int zoom{100};
    } imageInfo;

    struct {
        bool isAlive{false};
        int width{0};
        int height{0};
    } masterInfo;

    struct {
        bool cropMode{false};
        bool startedCropping{false};
        int x0;
        int y0;
        int x;
        int y;
    } cropData;
};

}
