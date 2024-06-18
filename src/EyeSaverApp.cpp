#include "EyeSaverApp.hpp"

bool EyeSaverApp::OnInit()
{
    TimerWindow *window = new TimerWindow();
    window->Show(true);
    return true;
}
