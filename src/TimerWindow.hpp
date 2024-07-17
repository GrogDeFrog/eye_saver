#ifndef __TIMER_WINDOW_HPP__
#define __TIMER_WINDOW_HPP__

class TimerWindow : public wxFrame
{
public:
    TimerWindow();

    enum
    {
        ID_Hello = 1
    };

private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
};

#endif
