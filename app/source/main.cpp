#include "wx/wx.h"
#include <memory>

#include "GuiBaseComponents.h"

class App : public wxApp
{
    bool OnInit();

    gui::ImagesComparerFrameBase* mainFrame;
};

IMPLEMENT_APP(App)


bool App::OnInit()
{
    mainFrame = new gui::ImagesComparerFrameBase{nullptr};
    mainFrame->Show();

    return true;
}

