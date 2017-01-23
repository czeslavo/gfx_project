#pragma once

namespace core
{

struct SharedData
{
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
        int width;
        int height;
    } masterInfo;
};

}
