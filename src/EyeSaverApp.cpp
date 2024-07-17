#include <typeinfo>
#include <wx/wx.h>
#include <wx/display.h>

#include "EyeSaverApp.hpp"

bool EyeSaverApp::OnInit()
{
    // I don't know if this is a static function
    unsigned int numDisplays = wxDisplay::GetCount();

    for (unsigned int i = 0; i < numDisplays; ++i) {
        wxDisplay display(i);
        if (display.IsOk()) {
            wxRect screenRect = display.GetGeometry();
            MyFrame* frame = new MyFrame(wxString::Format("Fullscreen Window on Monitor %u", i + 1), screenRect);
            frame->ShowFullScreen(true);
        }
    }

    //TimerWindow *window = new TimerWindow();
    //window->ShowFullScreen(true);
    //window->Show(true);
    return true;
}
