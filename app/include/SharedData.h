#pragma once

namespace core
{

struct SharedData
{
    struct {
        bool dragging{false};
        int x0;
        int y0;
    } dragInfo;

    struct {
        int x;
        int y;
        int zoom;
    } imageInfo;

    struct {
        bool isAlive{false};
        int width;
        int height;
    } masterInfo;
};

}
