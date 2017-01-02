#include "wx/wx.h"
#include <memory>

#include "MainFrame.h"

class App : public wxApp
{
    bool OnInit();

    MainFrame* mainFrame;
};

IMPLEMENT_APP(App)


bool App::OnInit()
{
    mainFrame = new MainFrame{nullptr};
    mainFrame->Show();

    return true;
}

