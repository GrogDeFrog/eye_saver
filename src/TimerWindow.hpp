#ifndef __TIMER_WINDOW_HPP__
#define __TIMER_WINDOW_HPP__

enum
{
    ID_Hello = 1
};

class TimerWindow : public wxFrame
{
public:
    TimerWindow();
private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
};

#endif
