#include <wx/wx.h>

#include "ImageComparerFrame.h"

class App : public wxApp
{
    bool OnInit();

    gui::ImageComparerFrame* mainFrame;
};

IMPLEMENT_APP(App)

bool App::OnInit()
{
    mainFrame = new gui::ImageComparerFrame{nullptr};
    mainFrame->Show();

    return true;
}

