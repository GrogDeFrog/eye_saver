#ifndef __EYE_SAVER_APP_HPP__
#define __EYE_SAVER_APP_HPP__

#include <wx/wx.h>

#include "TimerWindow.hpp"

class EyeSaverApp : public wxApp
{
public:
    bool OnInit() override;
};

#endif
